/* Includes */
#include "newax12.h"

#pragma udata

void ax12InitSerial(void) {
    TXSTA = 0; // configuracion del registro TXSTA
    TXSTAbits.TX9 = 0; // transmision de 8 bits
    TXSTAbits.TXEN = 0; // transmision deshabilitada
    TXSTAbits.SYNC = 0; // modo asincronico
    TXSTAbits.SENDB = 0; // Break Character Send Sync Break on next transmission
    TXSTAbits.BRGH = 1; // High Speed

    RCSTA = 0; // configuracion del registro RCSTA
    RCSTAbits.SPEN = 1; // pins RX y TX para comunicaci�n serial
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
    //PIE1bits.RCIE = 0;              // deshabilita la interrupci�n de recepci�n
    RCSTAbits.CREN = 0; // deshabilita la recepci�n
    // Configuro la transmisi�n
    TRISCbits.TRISC6 = 0; // PORTC<6> como salida
    TXSTAbits.TXEN = 1; // habilita la transmisi�n

}

void setRX(void) { /* RX mode */
    // Desconfiguro la transmisi�n
    TRISCbits.TRISC6 = 1; // PORTC<6> como entrada
    TXSTAbits.TXEN = 0; // deshabilita la transmisi�n

    PIR1bits.RCIF = 0;
    RCSTAbits.CREN = 1; // habilita la recepci�n
    //PIE1bits.RCIE = 1; // habilita la interrupci�n de recepci�n
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

void ax12SendRawPacket(byte* packet, byte len) {
    byte pos = 2;
    setTX(); /* Mode = TX */
    while (pos < len) { /* send the complete packet */
        ax12writeB((byte) (packet[pos++])); /* write a byte */
    }
    while (!TXSTAbits.TRMT); /* wait for transmision complete */
    setRX(); /* Mode = RX */
}

byte ax12ReceiveRawPacket(byte* len, byte* pack) {
    byte pos = 0, pos2 = 0, done = 0xBB;
    int timeout = TIMEOUT;

    T0CONbits.TMR0ON = FALSE; /* disable timer 0 */
    INTCONbits.GIE = 0; /* disable interrupts */

    while (pos < LEN_PRE_PACK) { /* read from beginning to len */
        timeout = TIMEOUT;
        while (!PIR1bits.RCIF && timeout--); /* wait until timeout or ax12 read */
        pack[pos++] = RCREG; /* consume a new byte */
        PIR1bits.RCIF = 0; /* put the flag down to continue reading */
//        done = (byte)(timeout == 0);
    }

    while (pos2 < pack[3]) { /* read the rest of the status packet */
        timeout = TIMEOUT;
        while (!PIR1bits.RCIF && timeout--); /* wait until timeout or ax12 read */
        pack[pos + pos2++] = RCREG; /* consume a new byte */
        PIR1bits.RCIF = 0; /* put the flag down to continue reading */
//        done = (byte)(timeout == 0);
    }
    *len = (byte) (pos2 + pos); /* returns the lenght of the packet read */

    /* enable interrupts and set reset mode */
    T0CONbits.TMR0ON = TRUE;
    INTCONbits.GIE = 1;
    setNone();

    return timeout;
}
