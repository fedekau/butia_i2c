/* Includes */
#include "newax12.h"

#pragma code module

void ax12InitSerial(void) {
    TXSTA = 0; // configuracion del registro TXSTA
    TXSTAbits.TX9 = 0; // transmision de 8 bits
    TXSTAbits.TXEN = 0; // transmision deshabilitada
    TXSTAbits.SYNC = 0; // modo asincronico
    TXSTAbits.SENDB = 0; // Break Character Send Sync Break on next transmission
    TXSTAbits.BRGH = 1; // High Speed

    RCSTA = 0; // configuracion del registro RCSTA
    RCSTAbits.SPEN = 1; // pins RX y TX para comunicaci?n serial
    RCSTAbits.RX9 = 0; // recepcion de 8 bits
    RCSTAbits.CREN = 0; // recepcion deshabilitada*

    BAUDCON = 0; // configuracion del registro BAUDCON
    BAUDCONbits.BRG16 = 1; // Generador de BAUD RATE de 16 bits
    SPBRG = 0x04; // BRGH=BRG16 = 1 | OSC = 20MHZ => 1 Mbps
    // configuracion de interrupciones
    INTCONbits.GIE = 1; // habilito interrupciones globales
    INTCONbits.PEIE = 1; // habilito interrupciones de perifericos

    TRISCbits.TRISC7 = 1; // PORTC<7> como entrada
}

void setTX(void) { // Modo TX
    //PIE1bits.RCIE = 0;              // deshabilita la interrupci?n de recepci?n
    RCSTAbits.CREN = 0; // deshabilita la recepci?n
    // Configuro la transmisi?n
    TRISCbits.TRISC6 = 0; // PORTC<6> como salida
    TXSTAbits.TXEN = 1; // habilita la transmisi?n

}

void setRX(void) { /* RX mode */
    // Desconfiguro la transmisi?n
    TRISCbits.TRISC6 = 1; // PORTC<6> como entrada
    TXSTAbits.TXEN = 0; // deshabilita la transmisi?n

    PIR1bits.RCIF = 0;
    RCSTAbits.CREN = 1; // habilita la recepci?n
    //PIE1bits.RCIE = 1; // habilita la interrupci?n de recepci?n
}

void setNone(void) { /* RESET mode */
    RCSTAbits.CREN = 0; /* unable reception */
    TXSTAbits.TXEN = 0; /* unable transmition */
}

byte ax12writeB(byte data) {
    while (!TXSTAbits.TRMT); /* wait until ready to send */
    TXREG = data;
    return data;
}

byte ReadSerial() {
    int timeout = TIMEOUT;
    while (!PIR1bits.RCIF && timeout--); /* wait until timeout or ax12 read */
    PIR1bits.RCIF = 0; /* put the flag down to continue reading */
    return RCREG; /* consume a new byte */
}

void ax12SendRawPacket(byte* packet, byte len) {
    byte pos = 2;
    setTX(); /* Mode = TX */
    while (pos < len) { /* send the complete packet */
        ax12writeB((byte) (packet[pos++])); /* write a byte */
    }
    while (!TXSTAbits.TRMT); /* wait for transmision complete */
    setRX(); /* Mode = RX */
}

byte ax12ReceiveRawPacket2(byte* len, byte* pack) {
    byte pos = 0, pos2 = 0, lenght = 0;

    T0CONbits.TMR0ON = FALSE; /* disable timer 0 */
    INTCONbits.GIE = 0; /* disable interrupts */

    while (pos < LEN_PRE_PACK) { /* reads sync bytes, id and lenght */
        pack[pos++] = (byte) ReadSerial();
    }

    lenght = (byte)pack[pos-1];
    if ((lenght > MAX_PACKET_SIZE) || (lenght == 0x00)){ /* something is wrong */
        *len = 0;
        return 1;
    }

    while (pos2 < lenght) { /* reads error, data and checksum */
        pack[pos+pos2++ ] = (byte) ReadSerial();
    }

    /* enable interrupts and set reset mode */
    T0CONbits.TMR0ON = TRUE;
    INTCONbits.GIE = 1;
    setNone();

    *len = pos + pos2; /* returns the lenght of the packet read */
    return 0;
}

byte ax12ReceiveRawPacket1(byte* len, byte* pack) {
    byte pos = 0, pos2 = 0, lenght = 0;
    BOOL error = FALSE, termine = FALSE;

    T0CONbits.TMR0ON = FALSE; /* disable timer 0 */
    INTCONbits.GIE = 0; /* disable interrupts */

    while ((!termine) && (!error)) { /* reads the whole message*/
        switch (pos) {
            case 0:
            case 1:
                pack[pos] = (byte) ReadSerial(); /* consume sync bytes */
                if (pack[pos] != FF) {
                    error = TRUE;
                }
                pos++;
                break;
            case 2:
                pack[pos] = (byte) ReadSerial(); /* consume id byte */
                if (pack[pos] > MAX_MOTOR_ID) {
                    error = TRUE;
                }
                pos++;
                break;
            case 3:
                pack[pos] = (byte) ReadSerial(); /* consume lenght byte */
                lenght = (byte) (pack[pos]); /* indicates the lenght of the rest of the message*/
                if (lenght > MAX_PACKET_SIZE) {
                    error = TRUE;
                }
                pos++;
                break;
            case 4: /* read error data & checksum */
                if (pos2 < lenght) {
                    pack[pos + pos2] = (byte) ReadSerial(); /* no checks */
                    pos2++;
                } else {
                    termine = TRUE;
                }
                break;
            default: /* never reaches here */
                error = TRUE;
                break;
        }
    }
    *len = pos + pos2; /* returns the lenght of the packet read */

    /* enable interrupts and set reset mode */
    T0CONbits.TMR0ON = TRUE;
    INTCONbits.GIE = 1;
    setNone();

    return (byte) error;
}
