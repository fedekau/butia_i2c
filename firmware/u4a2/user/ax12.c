/****************************************************************************** 
* Nombre: ax12.c 
* Tipo:   SOURCE FILE
* Uso:    Funciones para el control de los servos Dynamixel AX-12.
******************************************************************************* 
* Microcontrolador: 18f4550
* Compildador:      C18
******************************************************************************* 
* Observaciones:
*         1)En éste código se implementan las distintas funciones prototipos
*           declaradas en ax12.h.
*
*         2)Los servos Ax-12 requieren una comunicación serial del tipo
*           HALF-DUPLEX la cual será implementada por SOFTWARE. NOTA: No 
*           utilizaremos la librería "usart.h" para tener mas control sobre
*           nuestra USART.
*
*         3)Éste código puede ser modificado para ser utilizado por otro
*           microcontrolador. Se debe modificar "#include <p18f4550.h>" por el 
*           nuevo HEADER. NOTA: El cambio de microcontrolador puede implicar
*           modificaciones en funciones utilizadas en ésta librería.
*
******************************************************************************* 
* Creada por:           Andrés Aguirre | Kenji Nakasone
*                                PROYECTO BUTÍA
*                             Fac. de ING | UDELAR
******************************************************************************* 
* Fecha: 09|06|2010
* Versión: 1.1
* 			Cambios en la carga del registro TXSTA y RCSTA
* Errores y sugerencias: 
******************************************************************************/ 
   
    //Includes
    #include "p18f4550.h"                                  
    #include "ax12.h"    
                                   
/*****************************************************************************/ 
/********************************   Variables   ******************************/
/*****************************************************************************/ 
    byte id;
    boolean inverse;
    int status_id;                              // ID del paquete de retorno
    int status_error;                           // error del paquete de retorno
    int status_data;                            // data del paquete de
                                                // retornostatic void setTX();

    static byte ax_rx_buffer[AX12_BUFFER_SIZE]; // buffer de recepción
    static volatile byte ax_rx_Pointer;             


/*****************************************************************************/ 
/***************************   Funciones auxiliares   ************************/
/*****************************************************************************/ 
boolean sign2bin (int numero) {                        // numero > 0 --> true
    return (numero > 0);                               //numero <= 0 --> false
}

char bin2sign (boolean var) {                         // var = 0 --> sign = -1
    return 2*var - 1;                                 // var = 1 --> sign = 1
}

int makeInt (byte l, byte h) {
    return (h << 8) | l;
}

byte highByte(int value){
    return (value >> 8);
}

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


/*****************************************************************************/ 
/*************************    Vector de Interrupción   ***********************/
/*****************************************************************************/ 
    #pragma code vector = 0x08
void int_vector (void){
    _asm 
        goto isr_RX
    _endasm
}
    #pragma code
/*****************************************************************************/ 
/*************************    Rutina de Interrupción   ***********************/
/*****************************************************************************/ 
     #pragma interrupt isr_RX
void isr_RX(void){
    ax_rx_buffer[(ax_rx_Pointer++)] = RCREG;    //guarda el byte recibido en el 
                                                //en el buffer
}      
/*****************************************************************************/ 
/**********************   Configuración de la USART   ************************/
/***************   Asincrónica | 8 bits | 1 stop | Sin paridad   *************/
/*****************************************************************************/ 
void init(void){
	TXSTA = 0b00000100;				// configuración del registro TXSTA
									// TXSTA:Transmit Status & Control Register
		   							// TX9 = 0; transmisión de 8 bits
									// TXEN = 0; transmisión deshabilitada*
									// SYNC = 0; modo asincrónico
									// SENDB = 0; Break Character
									// BRGH = 1; High Speed
    

	RCSTA = 0b10000000;             // configuración del registro RCSTA
								    // RCSTA:Receive Status & control Register
						 		    // SPEN = 1; pins RX y TX para comunicación serial
					                // RX9 = 0; recepción de 8 bits
					                // CREN = 0; recepcion deshabilitada*
    
	
    BAUDCON = 0b00001000;  		    // configuración del registro BAUDCON
									// BAUDCON:Baud Rate Control Register
									// BRG16 = 1; Generador de BAUD RATE de 16 bits             
             
    SPBRG = 0x04;                   // BRGH=BRG16 = 1 | OSC = 20MHZ => 1 Mbps

    INTCON = 0b11000000;        	// configuración de interrupciones
									// INTON:Interrupt Control Register
						            // GIE = 1; habilito interrupciones globales
						            // PEIE = 1; habilito interrupciones de periféricos

   								    // configuración del puerto C
    TRISC = 0b10000000;             // TRISC7 = 1; PORTC<7> como entrada
    
    ax_rx_Pointer = 0;                                    
    setRX();                        // MODO RX
}
   

/*****************************************************************************/ 
/*****   Funciones auxiliares para la implementación del HALF-DUPLEX   *******/
/***************************  Hardware Serial Level  *************************/
/*****************************************************************************/ 
void setTX(void){                   // Modo TX
    PIE1bits.RCIE = 0;              // deshabilita la interrupción de recepción
    RCSTAbits.CREN = 0;             // deshabilita la recepción
                                    // Configuro la transmisión
    TRISCbits.TRISC6 = 0;           // PORTC<6> como salida
    TXSTAbits.TXEN = 1;             // habilita la transmisión

}

void setRX(void){                   // Modo RX
                                    // Desconfiguro la transmisión
    TRISCbits.TRISC6 = 1;           // PORTC<6> como entrada
    TXSTAbits.TXEN = 0;             // deshabilita la transmisión

    RCSTAbits.CREN = 1;             // habilita la recepción
    PIE1bits.RCIE = 1;              // habilita la interrupción de recepción
    ax_rx_Pointer = 0;              // resetea el puntero del buffer
}

void setNone(void){                 // Modo RESET
    PIE1bits.RCIE = 0;              // deshabilita la interrupción de recepción
    RCSTAbits.CREN = 0;             // deshabilita la recepción
                                    // Desconfiguro la transmisión
    TXSTAbits.TXEN = 0;             // deshabilita la transmisión
}

byte ax12writeB(byte data){
    while (!TXSTAbits.TRMT);        // espera que el micro esté pronto para TX
    TXREG = data;                   // escribe el byte a trasmitir
    return data;
}
/*****************************************************************************/ 
/******************  Funciones de Transmisión y Recepción  *******************/
/******************************  Packet Level  *******************************/
/*****************************************************************************/ 
void ax12SendPacket (byte id, byte datalength, byte instruction, byte *data){
    byte f;
    byte checksum = 0;
    setTX();                                     // Modo TX
    ax12writeB(0xFF);                            // Requerido por Ax-12 
    ax12writeB(0xFF);                            // Requerido por Ax-12 
    checksum += ax12writeB(id);
    checksum += ax12writeB(datalength + 2);
    checksum += ax12writeB(instruction);
    for (f=0; f<datalength; f++) {              
      checksum += ax12writeB(data[f]);
    }
    ax12writeB(~checksum);                       // Espero que se complete
    while(!TXSTAbits.TRMT);                      // la transmisión
    setRX();                                     // Modo RX
}
                                 			     // Retorna el código
byte ax12ReadPacket(int* status_id, int* status_error, int* status_data){          
    unsigned long ulCounter;
    byte f;
    byte timeout, error, status_length;
    byte checksum, offset;
    byte volatile bcount;

    offset = 0;                                  // primero espera que 
    timeout = 0;                                 // llegue toda la data
    bcount = 0;
    while(bcount < 13){                          // 10 es el largo máximo 
        ulCounter = 0;                           // que puede tener un packet

        while((bcount + offset) == ax_rx_Pointer){
            if(ulCounter++ > 1000L){  // was 3000
                timeout = 1;
                break;
            }
        }
        if (timeout) break;
        if ((bcount == 0) && (ax_rx_buffer[offset] != 0xff)) offset++;
        else bcount++;
    }
    setNone();
                                                 // decodifica el packet
                                                 // corrección de cabecera
    error = 0;                                   // código interno de error
    do {
        error++;
        offset++;
        bcount--;
    } while (ax_rx_buffer[offset] == 255);
    if (error > 1) error =0;                     // prueba de cabecera


    // offset = primer byte del mensaje (sin cabecera)
    // bcount = largo del mensaje leido (sin cabecera)
    status_length = 2 + ax_rx_buffer[offset+1]; // largo del mensaje decodificado
    if (bcount != status_length) error+=2;      // prueba de coherencia de data
    checksum = 0;                               // cálculo de checksum
    for (f=0; f<status_length; f++)
        checksum += ax_rx_buffer[offset+f];
    if (checksum != 255) error+=4;              // prueba de checksum
    if (error == 0) {
        *status_id = ax_rx_buffer[offset];
        *status_error = ax_rx_buffer[offset+2];
        switch (status_length) {
            case 5: *status_data = ax_rx_buffer[offset+3]; break;
            case 6: *status_data = makeInt (ax_rx_buffer[offset+3], ax_rx_buffer[offset+4]); break;
            default: *status_data = offset+3;
        }
    } else {
        *status_id = -1;
        *status_error = -1;
        *status_data = -1;
    }
    return error;
}
/*****************************************************************************/ 
/**********************   Funciones de control del Ax-12   *******************/
/*******************************  Instruction Level  *************************/
/*****************************************************************************/ 
byte writeData(byte id,byte regstart, byte reglength, byte *values){
	byte f;
    byte data [MAXPAQSIZE];
    data [0] = regstart; 	
	for (f=0; f<reglength; f++) {               // data = parámetros
      data[f+1] = values[f];
    }

    ax12SendPacket (id, reglength+1, WRITE_DATA, data);
    return ax12ReadPacket(&status_id, &status_error, &status_data);
}


byte readData(byte regstart, byte reglength){
    byte data [2];
    data [0] = regstart;
    data [1] = reglength;
    ax12SendPacket (id, 2, READ_DATA, data);
    return ax12ReadPacket(&status_id, &status_error, &status_data);
}
/*****************************************************************************/ 
/**********************   Funciones de control del Ax-12   *******************/
/*********************************  Register Level  **************************/
/*****************************************************************************/ 


byte writeInfo (byte id,byte regstart, int value) {
    byte reglength = 0;
    byte data [MAXPAQSIZE];
    switch (regstart) {
      case 3: case 4: case 5: case 11: case 12:
      case 13: case 16: case 17: case 18: case 19:
      case 24: case 25: case 26: case 27: case 28:
      case 29: case 44: case 47: reglength = 1; break;
      case 6: case 8: case 14: case 30: case 32:
      case 34: case 48: reglength = 2; break;
    }
    // if (reglength==0) {return 255;}
   // if (regstart==30 && inverse) {               // este if se va a completar
   //   value = 1023-value;                        // con todo aquello que deba 
   // }                                            //ser invertido

    data [0] = regstart;
    data [1] = value&0xFF;
    if (reglength > 1) {data[2] = (value&0xFF00)>>8;}
    ax12SendPacket (id, reglength+1, WRITE_DATA, data);
    return ax12ReadPacket(&status_id, &status_error, &status_data);
}


void setEndlessTurnMode (byte id,boolean onoff) {
    writeInfo (id,CW_ANGLELIMIT_L , 0);
    if (onoff) {
        writeInfo (id,CCW_ANGLELIMIT_L, 0);
    } else {
        writeInfo (id,CCW_ANGLELIMIT_L, 1023);
    }
}
	
void endlessTurn (byte id,int velocidad,int giro) {
		int movimiento = ((velocidad)|((giro)<<10));
        writeInfo (id,MOVING_SPEED_L, movimiento);
}


byte presentPSL (int* PSL) {                     // lee posicion, velocidad 
    byte f;
    byte err = readData (PRESENT_POSITION_L, 6);       // y lo carga
    for (f=0; f<3; f++) {
        PSL [f] = makeInt (ax_rx_buffer[status_data+2*f], ax_rx_buffer[status_data+1+2*f]);
        if (f>0) {
            PSL[f] = (PSL[f]&0x03FF) * bin2sign((PSL[f]>0x03FF)^inverse);
        }
    }
    if (inverse) {PSL[0] = 1023-PSL[0];}
    return err;
}



