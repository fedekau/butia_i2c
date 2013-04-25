/****************************************************************************** 
 * Nombre: ax12.c
 * Tipo:   SOURCE FILE
 * Uso:    Funciones para el control de los servos Dynamixel AX-12.
 *******************************************************************************
 * Microcontrolador: 18f4550
 * Compildador:      C18
 *******************************************************************************
 * Observaciones:
 *         1)En este codigo se implementan las distintas funciones prototipos
 *           declaradas en ax12.h.
 *
 *         2)Los servos Ax-12 requieren una comunicaci?n serial del tipo
 *           HALF-DUPLEX la cual sera implementada por SOFTWARE. NOTA: No
 *           utilizaremos la libreria "usart.h" para tener mas control sobre
 *           nuestra USART.
 *
 *         3)este codigo puede ser modificado para ser utilizado por otro
 *           microcontrolador. Se debe modificar "#include <p18f4550.h>" por el
 *           nuevo HEADER. NOTA: El cambio de microcontrolador puede implicar
 *           modificaciones en funciones utilizadas en esta libreria.
 *
 *******************************************************************************
 * Creada por:           Andres Aguirre | Kenji Nakasone
 *                                PROYECTO BUTIA
 *                             Fac. de ING | UDELAR
 *******************************************************************************
 * Fecha: 09|06|2010
 * Version: 1.0
 * Errores y sugerencias:
 ******************************************************************************/

/* Includes */
#include "p18f4550.h"                                  
#include "ax12.h"

#define FF 0xFF
#define MAX_MOTOR_ID 0xFE
#define TIMEOUT 15000

#pragma udata

/*****************************************************************************/
/********************************   Variables   ******************************/
/*****************************************************************************/

int status_id; /* ID del paquete de retorno */
int status_error; /* error del paquete de retorno */
int status_data; /* data del paquete de */

static byte ax_rx_buffer[AX12_BUFFER_SIZE]; /* buffer de recepcion */
static volatile byte ax_rx_Pointer;

/*****************************************************************************/
/***************************   Funciones auxiliares   ************************/
/*****************************************************************************/

byte ax12writeB(byte);
byte readSerial(void);
int makeInt(byte, byte);

#pragma code module

//boolean sign2bin (int numero) {                        // numero > 0 --> true
//    return (numero > 0);                               //numero <= 0 --> false
//}

//char bin2sign (boolean var) {                         // var = 0 --> sign = -1
//    //return 2*var - 1;                                 // var = 1 --> sign = 1
//    if(var>0)
//        return 1;
//    else
//        return -1;
//}

int makeInt(byte l, byte h) {
    return (h * 256) +l;
}

//byte highByte(int value){
//    return (value >> 8);
//}

/*
#define sign2bin(numero) (numero > 0)
#char bin2sign (boolean var) {                         // var = 0 --> sign = -1
    return 2*var - 1;                                 // var = 1 --> sign = 1
}

int makeInt (byte l, byte h) {
    return (h << 8) | l;
}

byte highByte(int value){
    return (value >> 8);
}
 */

/*****************************************************************************/
/*************************    Vector de Interrupcion   ***********************/
/***************************************************************************** *
#pragma code vector =  0x08

void int_vector (void){
    _asm
        goto isr_RX
    _endasm
}

#pragma code

/*****************************************************************************/
/*************************    Rutina de Interrupcion   ***********************/
/***************************************************************************** *

#pragma interrupt isr_RX
void isr_RX(void){
    ax_rx_buffer[(ax_rx_Pointer++)] = RCREG;    //guarda el byte recibido en el 
                                                //en el buffer
}

/****************************************************************************/

/*****************************************************************************/
/**********************   Configuracion de la USART   ************************/
/***************   Asincronica | 8 bits | 1 stop | Sin paridad   *************/

/*****************************************************************************/
void ax12InitSerial(void) {
    TXSTA = 0; // configuraci?n del registro TXSTA
    TXSTAbits.TX9 = 0; // transmisi?n de 8 bits
    TXSTAbits.TXEN = 0; // transmisi?n deshabilitada*
    TXSTAbits.SYNC = 0; // modo asincr?nico
    TXSTAbits.SENDB = 0; // Break Character //Send Sync Break on next transmission
    TXSTAbits.BRGH = 1; // High Speed

    RCSTA = 0; // configuraci?n del registro RCSTA
    RCSTAbits.SPEN = 1; // pins RX y TX para comunicaci?n serial
    RCSTAbits.RX9 = 0; // recepci?n de 8 bits
    RCSTAbits.CREN = 0; // recepcion deshabilitada*

    BAUDCON = 0; // configuraci?n del registro BAUDCON
    BAUDCONbits.BRG16 = 1; // Generador de BAUD RATE de 16 bits
    SPBRG = 0x04; // BRGH=BRG16 = 1 | OSC = 20MHZ => 1 Mbps

    // configuraci?n de interrupciones
    INTCONbits.GIE = 1; // habilito interrupciones globales
    INTCONbits.PEIE = 1; // habilito interrupciones de perif?ricos

    TRISCbits.TRISC7 = 1; // PORTC<7> como entrada
    //setRX();                        // MODO RX
}


/*****************************************************************************/
/*****   Funciones auxiliares para la implementacion del HALF-DUPLEX   *******/
/***************************  Hardware Serial Level  *************************/

/*****************************************************************************/

void setTX(void) { // Modo TX
    //PIE1bits.RCIE = 0;              // deshabilita la interrupci?n de recepci?n
    RCSTAbits.CREN = 0; // deshabilita la recepci?n
    // Configuro la transmisi?n
    TRISCbits.TRISC6 = 0; // PORTC<6> como salida
    TXSTAbits.TXEN = 1; // habilita la transmisi?n

}

void setRX(void) { // Modo RX
    // Desconfiguro la transmisi?n
    TRISCbits.TRISC6 = 1; // PORTC<6> como entrada
    TXSTAbits.TXEN = 0; // deshabilita la transmisi?n

    RCSTAbits.CREN = 1; // habilita la recepci?n
    //PIE1bits.RCIE = 1;              // habilita la interrupci?n de recepci?n
    ax_rx_Pointer = 0; // resetea el puntero del buffer
}

void setNone(void) { // Modo RESET
    RCSTAbits.CREN = 0; // deshabilita la recepci?n
    TXSTAbits.TXEN = 0; // deshabilita la transmisi?n
}

byte ax12writeB(byte data) {
    while (!TXSTAbits.TRMT); // wait until ready to send
    TXREG = data;
    return data;
}

byte readSerial(void) {
    int timeout = TIMEOUT;
    while (!PIR1bits.RCIF && timeout--); /* wait until timeout or ax12 read */
    PIR1bits.RCIF = 0; /* put the flag down to continue reading */
    return RCREG; /* consume a new byte */
}

/*****************************************************************************/
/******************  Funciones de Transmision y Recepcion  *******************/
/******************************  Packet Level  *******************************/

/*****************************************************************************/

void ax12SendPacket(byte id, byte datalength, byte instruction, byte *data) {
    byte f;
    byte checksum = 0;
    setTX(); // Modo TX
    ax12writeB(0xFF); // Requerido por Ax-12
    ax12writeB(0xFF); // Requerido por Ax-12
    checksum += ax12writeB(id);
    checksum += ax12writeB(datalength + 2);
    checksum += ax12writeB(instruction);
    for (f = 0; f < datalength; f++) { // data = par?metros
        checksum += ax12writeB(data[f]);
    }
    ax12writeB(~checksum); // Espero que se
    while (!TXSTAbits.TRMT); // complete la transmisi?n
    setRX(); // Modo RX
}

byte ax12ReadPacket(int* s_id, int* s_error, int* s_data) {

    byte error, status_length;
    //byte checksum, i;
    byte ready;
    byte estado = 1;

    *s_id = 0;
    *s_error = 0;
    *s_data = 0;
    ready = 0; // Not ready yet
    error = 0; // 0 mean not error
    ax_rx_Pointer = 0;
    // checksum = 0;
    while (!ready && !error) {
        switch (estado) {
            case 1: case 2:
            { //Syncronizaion bytes
                if (readSerial() == FF) {
                    estado++;
                } else
                    error++;
            }
                break;
            case 3:
            { // Motor ID
                *s_id = readSerial();
                //checksum += *status_id;
                if (*s_id <= MAX_MOTOR_ID)
                    estado++;
                else
                    error++;
            }
                break;

            case 4:
            { // Length of packet
                status_length = readSerial();
                //checksum += status_length;
                if (status_length < AX12_BUFFER_SIZE) //Check if the length is rigth
                    estado++;
                else
                    error++;
            }
                break;
            case 5:
            { // Error code, Parameters and check sum
                ax_rx_buffer[ax_rx_Pointer] = readSerial();
                //checksum += ax_rx_buffer[ax_rx_Pointer];
                ax_rx_Pointer++;
                if (ax_rx_Pointer >= status_length)
                    ready = 1; //The reading AX12 menssage is done
            }
                break;
            default: error = 1;
        }//switch
    }//while

    setNone();

    // for (i = 0; i < ax_rx_Pointer-1; i++)
    //      checksum += ax_rx_buffer[i];
    //checksum = checksum^0xff ;//~checksum;
    //if (checksum != ax_rx_buffer[ax_rx_Pointer-1]) error+=4;              // Test checksum
    //  if (~checksum !=checksum^0xff) error+=4;              // Test checksum
    if (error != 0) { //Falta verificar el checksum
        *s_id = -1;
        *s_error = -1;
        *s_data = -1;
    } else {
        *s_error = ax_rx_buffer[0];
        switch (status_length) { //TODO: Se esta asumiendo que no vienen mas de 2 parametros ...
            case 3: *s_data = ax_rx_buffer[1];
                break;
            case 4: *s_data = makeInt(ax_rx_buffer[1], ax_rx_buffer[2]);
                break;
            default: *s_data = -1; //No hay datos
        }
    }
    return error; //pos; // 1 mean all is ok
}

/*****************************************************************************/
/**********************   Funciones de control del Ax-12   *******************/
/*******************************  Instruction Level  *************************/
/*****************************************************************************/

//byte writeData(byte id,byte regstart, byte reglength, byte *values){
//	byte f;
//    byte data [MAXPAQSIZE];
//    data [0] = regstart;
//	for (f=0; f<reglength; f++) {               // data = par?metros
//      data[f+1] = values[f];
//    }
//
//    ax12SendPacket (id, reglength+1, WRITE_DATA, data);
//    return ax12ReadPacket(&status_id, &status_error, &status_data);
//}

//byte readData(byte id, byte regstart, byte reglength){
//    byte data [2];
//    data [0] = regstart;
//    data [1] = reglength;
//    ax12SendPacket (id, 2, READ_DATA, data);
//    return ax12ReadPacket(&status_id, &status_error, &status_data);
//}

//byte reset (byte id){
////Changes the control table values of the Dynamixel actuator with id 'id' to the Factory Default Value settings
//   return writeInfo(id, RESET_AX12,  0);
//}

/*****************************************************************************/
/**********************   Funciones de control del Ax-12   *******************/
/*********************************  Register Level  **************************/

/*****************************************************************************/

byte writeInfo(byte id, byte regstart, int value) {
    byte reglength = 0;
    byte data [MAX_PACKET_SIZE];
    switch (regstart) {
        case 3: case 4: case 5: case 11: case 12:
        case 13: case 16: case 17: case 18: case 19:
        case 24: case 25: case 26: case 27: case 28:
        case 29: case 44: case 47: reglength = 1;
            break;
        case 6: case 8: case 14: case 30: case 32:
        case 34: case 48: reglength = 2;
            break;
    }

    data [0] = regstart;
    data [1] = value & 0xFF;
    if (reglength > 1) {
        data[2] = (value & 0xFF00) >> 8;
    }
    ax12SendPacket(id, reglength + 1, WRITE_DATA, data);

    return ax12ReadPacket(&status_id, &status_error, &status_data);
}

void setEndlessTurnMode (byte id,byte onoff) {
    writeInfo (id,CW_ANGLELIMIT_L , 0);
    if (onoff) {
        writeInfo (id,CCW_ANGLELIMIT_L, 0);
    } else {
        writeInfo (id,CCW_ANGLELIMIT_L, 1023);
    }
}

void endlessTurn (byte id,int velocidad, byte inverse) {
    //boolean direccion = sign2bin (velocidad);
    if(velocidad<0)
        inverse^=1; //Cambio inverse si velocidad<0
    velocidad=abs(velocidad);
    velocidad|=inverse*1024;
    writeInfo (id,MOVING_SPEED_L, velocidad);
}

//byte presentPSL (boolean inverse, byte id, int* PSL) {                     // lee posicion, velocidad
//    byte f;
//    byte err = readData (id, PRESENT_POSITION_L, 6);       // y lo carga
//    for (f=0; f<3; f++) {
//        PSL [f] = makeInt (ax_rx_buffer[status_data+2*f], ax_rx_buffer[status_data+1+2*f]);
//        if (f>0) {
//            PSL[f] = (PSL[f]&0x03FF) * bin2sign((PSL[f]>0x03FF)^inverse);
//        }
//    }
//    if (inverse) {PSL[0] = 1023-PSL[0];}
//    return err;
//}

byte ax12ReceiveRawPacket(byte* len, byte* pack) {
    byte pos = 0, pos2 = 0, lenght = 0;

    T0CONbits.TMR0ON = FALSE; /* disable timer 0 */
    INTCONbits.GIE = 0; /* disable interrupts */

    while (pos < LEN_PRE_PACK) { /* reads sync bytes, id and lenght */
        pack[pos++] = (byte) readSerial();
    }

    lenght = (byte) pack[pos - 1];
    if ((lenght > MAX_PACKET_SIZE) || (lenght == 0x00)) { /* something is wrong */
        *len = 0;
        return 1;
    }

    while (pos2 < lenght) { /* reads error, data and checksum */
        pack[pos + pos2] = (byte) readSerial();
        pos2++;
    }

    /* enable interrupts and set reset mode */
    T0CONbits.TMR0ON = TRUE;
    INTCONbits.GIE = 1;
    setNone();

    *len = (byte) (pos + pos2); /* returns the lenght of the packet read */
    return 0;
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
