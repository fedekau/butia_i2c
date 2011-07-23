/* Author                                   Date        Comment            Versión
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Santiago Reyes Gonzalez                10/07/09   Original.                     0.02    
 * Andrés Aguirre Dorelo                  21/12/09   Cambios al open y al close    0.04
 *********************************************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h> 
#include <delays.h>
#include <stdio.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "usr_display.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user\handlerManager.h"
#include "user\dynamicPolling.h"         
#include "user\topList.h"
#include "usb4all\proxys\T0Service.h"                      

#define FALSE 0
#define TRUE  1
#define BUSY  0x01
#define NO_BUSY 0x00
#define TICKS_INICIAL 40
//#define DISP_TIME_UNIT 2000
#define DISP_TIME_UNIT 1000
/** V A R I A B L E S ********************************************************/
#pragma udata 
byte  usrDisplayHandler;     /* Handler number asigned to the module */
byte* sendBufferUsrDisplay;  /* buffer to send data */
char msg_string[17];          /* caracteres a en una linea del display */
topList list;
byte mensaje_agendar[32];            /* 32 es los bytes necesarios para representar una pantalla */
byte mensaje_agendar_iterator = 0;   /* iterator for mensaje agendar */  
unsigned char display_init = FALSE;
byte  needRegisterDisp = 1;
byte startMsg = 1;
byte borrar = 0;
byte cantTicksDisp  = TICKS_INICIAL;
byte timeOutTicksDisp = TICKS_INICIAL;
byte init=0;
byte isEnd = 0;
int contBusy = 0;
int maxContBusy = 500;
//int maxContBusy = 1000;
/** P R I V A T E  P R O T O T Y P E S ************* *************************/
void UserDisplayProcessIO(void);
void UserDisplayInit(byte i);
void UserDisplayReceived(byte*, byte);
void UserDisplayRelease(byte i);
void UserDisplayConfigure(void);
 
// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userDisplayModuleTable = {&UserDisplayInit,&UserDisplayRelease,&UserDisplayConfigure,"display"}; //modName must be less or equal 8 characters
//#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

void DelayFor18TCY( void ){
Nop(); Nop(); Nop(); 
Nop(); Nop(); Nop(); 
Nop(); Nop(); Nop(); 
Nop(); Nop(); Nop();
Nop(); Nop(); Nop(); 
Nop(); Nop(); Nop();
}

void DelayPORXLCD( void ){
    Delay10KTCYx(30); //Delay of 15ms
    Delay10KTCYx(30); //Delay of 15ms nuevo
    Delay10KTCYx(30); //Delay of 15ms nuevo
    Delay10KTCYx(30); //Delay of 15ms nuevo
    return;
}

void DelayXLCD( void ){
    Delay10KTCYx(10); //Delay of 5ms
    Delay10KTCYx(10); //Delay of 5ms nuevo
    Delay10KTCYx(10); //Delay of 5ms nuevo
    Delay10KTCYx(10); //Delay of 5ms nuevo
    return;
}

/********************************************************************
*       Function Name:  BusyXLCD                                    *
*       Return Value:   char: busy status of LCD controller         *
*       Parameters:     void                                        *
*       Description:    This routine reads the busy status of the   *
*                       Hitachi HD44780 LCD controller.             *
********************************************************************/
unsigned char BusyXLCD(void){
    RW_PIN = 1;                     // Set the control bits for read
    RS_PIN = 0;
    DelayFor18TCY();
    E_PIN = 1;                      // Clock in the command
    while (contBusy < maxContBusy){
    DelayFor18TCY();
    #ifdef BIT8                             // 8-bit interface
        if(DATA_PORT&0x80){         // Read bit 7 (busy bit)
                                    // If high
            E_PIN = 0;              // Reset clock line
            RW_PIN = 0;             // Reset control line
            contBusy++;
            return 1;               // Return TRUE
        }else{                      // Bit 7 low
            E_PIN = 0;              // Reset clock line
            RW_PIN = 0;             // Reset control line
            contBusy = 0 ;
            return 0;               // Return FALSE
        }
    #else                                   // 4-bit interface
    #ifdef UPPER                            // Upper nibble interface
        if(DATA_PORT&0x80)
    #else                                   // Lower nibble interface
        if(DATA_PORT&0x08){
    #endif
            E_PIN = 0;              // Reset clock line
            DelayFor18TCY();
            E_PIN = 1;              // Clock out other nibble
            DelayFor18TCY();
            E_PIN = 0;
            RW_PIN = 0;             // Reset control line
            contBusy++;
            return 1;               // Return TRUE
        }
        else{                       // Busy bit is low
            E_PIN = 0;              // Reset clock line
            DelayFor18TCY();
            E_PIN = 1;              // Clock out other nibble
            DelayFor18TCY();
            E_PIN = 0;
            RW_PIN = 0;             // Reset control line
            contBusy = 0 ;
            return 0;               // Return FALSE
        }
#endif
    }
return 0;
}


/********************************************************************
*       Function Name:  WriteCmdXLCD                                *
*       Return Value:   void                                        *
*       Parameters:     cmd: command to send to LCD                 *
*       Description:    This routine writes a command to the Hitachi*
*                       HD44780 LCD controller. The user must check *
*                       to see if the LCD controller is busy before *
*                       calling this routine.                       *
********************************************************************/
void WriteCmdXLCD(unsigned char cmd){
#ifdef BIT8                             // 8-bit interface
        TRIS_DATA_PORT = 0;             // Data port output
        DATA_PORT = cmd;                // Write command to data port
        RW_PIN = 0;                     // Set the control signals
        RS_PIN = 0;                     // for sending a command
        DelayFor18TCY();
        E_PIN = 1;                      // Clock the command in
        DelayFor18TCY();
        E_PIN = 0;
        DelayFor18TCY();
        TRIS_DATA_PORT = 0xff;          // Data port input
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
        TRIS_DATA_PORT &= 0x0f;
        DATA_PORT &= 0x0f;
        DATA_PORT |= cmd&0xf0;
#else                                   // Lower nibble interface
        TRIS_DATA_PORT &= 0xf0;
        DATA_PORT &= 0xf0;
        DATA_PORT |= (cmd>>4)&0x0f;
#endif
        RW_PIN = 0;                     // Set control signals for command
        RS_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                      // Clock command in
        DelayFor18TCY();
        E_PIN = 0;
#ifdef UPPER                            // Upper nibble interface
        DATA_PORT &= 0x0f;
        DATA_PORT |= (cmd<<4)&0xf0;
#else                                   // Lower nibble interface
        DATA_PORT &= 0xf0;
        DATA_PORT |= cmd&0x0f;
#endif
        DelayFor18TCY();
        E_PIN = 1;                      // Clock command in
        DelayFor18TCY();
        E_PIN = 0;
#ifdef UPPER                            // Make data nibble input
        TRIS_DATA_PORT |= 0xf0;
#else
        TRIS_DATA_PORT |= 0x0f;
#endif
#endif
        return;
}

/********************************************************************
*       Function Name:  SetDDRamAddr                                *
*       Return Value:   void                                        *
*       Parameters:     CGaddr: display data address                *
*       Description:    This routine sets the display data address  *
*                       of the Hitachi HD44780 LCD controller. The  *
*                       user must check to see if the LCD controller*
*                       is busy before calling this routine.        *
********************************************************************/
void SetDDRamAddr(unsigned char DDaddr){
#ifdef BIT8                                     // 8-bit interface
        TRIS_DATA_PORT = 0;                     // Make port output
        DATA_PORT = DDaddr | 0b10000000;        // Write cmd and address to port
        RW_PIN = 0;                             // Set the control bits
        RS_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                              // Clock the cmd and address in
        DelayFor18TCY();
        E_PIN = 0;
        DelayFor18TCY();
        TRIS_DATA_PORT = 0xff;                  // Make port input
#else                                           // 4-bit interface
#ifdef UPPER                                    // Upper nibble  interface
        TRIS_DATA_PORT &= 0x0f;                 // Make port output
        DATA_PORT &= 0x0f;                      // and write upper nibble
        DATA_PORT |= ((DDaddr | 0b10000000) & 0xf0);
#else                                           // Lower nibble interface
        TRIS_DATA_PORT &= 0xf0;                 // Make port output
        DATA_PORT &= 0xf0;                      // and write upper nibble
        DATA_PORT |= (((DDaddr | 0b10000000)>>4) & 0x0f);
#endif
        RW_PIN = 0;                             // Set control bits
        RS_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                              // Clock the cmd and address in
        DelayFor18TCY();
        E_PIN = 0;
#ifdef UPPER                                    // Upper nibble interface
        DATA_PORT &= 0x0f;                      // Write lower nibble
        DATA_PORT |= ((DDaddr<<4)&0xf0);
#else                                           // Lower nibble interface
        DATA_PORT &= 0xf0;                      // Write lower nibble
        DATA_PORT |= (DDaddr&0x0f);
#endif
        DelayFor18TCY();
        E_PIN = 1;                              // Clock the cmd and address in
        DelayFor18TCY();
        E_PIN = 0;
#ifdef UPPER                                    // Upper nibble interface
        TRIS_DATA_PORT |= 0xf0;                 // Make port input
#else                                           // Lower nibble interface
        TRIS_DATA_PORT |= 0x0f;                 // Make port input
#endif
#endif
        //return; para que?
}

/********************************************************************
*       Function Name:  OpenXLCD                                    *
*       Return Value:   void                                        *
*       Parameters:     lcdtype: sets the type of LCD (lines)       *
*       Description:    This routine configures the LCD. Based on   *
*                       the Hitachi HD44780 LCD controller. The     *
*                       routine will configure the I/O pins of the  *
*                       microcontroller, setup the LCD for 4- or    *
*                       8-bit mode and clear the display. The user  *
*                       must provide three delay routines:          *
*                       DelayFor18TCY() provides a 18 Tcy delay     *
*                       DelayPORXLCD() provides at least 15ms delay *
*                       DelayXLCD() provides at least 5ms delay     *
********************************************************************/
void OpenXLCD(unsigned char lcdtype)
{
        // The data bits must be either a 8-bit port or the upper or
        // lower 4-bits of a port. These pins are made into inputs
#ifdef BIT8                             // 8-bit mode, use whole port
        DATA_PORT = 0;
        TRIS_DATA_PORT = 0xff;
#else                                   // 4-bit mode
#ifdef UPPER                            // Upper 4-bits of the port
        DATA_PORT &= 0x0f;
        TRIS_DATA_PORT |= 0xf0;
#else                                   // Lower 4-bits of the port
        DATA_PORT &= 0xf0;
        TRIS_DATA_PORT |= 0x0f;
#endif
#endif
        TRIS_RW = 0;                    // All control signals made outputs
        TRIS_RS = 0;
        TRIS_E = 0;
        RW_PIN = 0;                     // R/W pin made low
        RS_PIN = 0;                     // Register select pin made low
        E_PIN = 0;                      // Clock pin made low


        // Delay for 15ms to allow for LCD Power on reset
        DelayPORXLCD();
        
        // Setup interface to LCD
#ifdef BIT8                             // 8-bit mode interface
        TRIS_DATA_PORT = 0;             // Data port output
        DATA_PORT = 0b00110000;         // Function set cmd(8-bit interface)
#else                                   // 4-bit mode interface
#ifdef UPPER                            // Upper nibble interface
        TRIS_DATA_PORT &= 0x0f;
        DATA_PORT &= 0x0f;
        DATA_PORT |= 0b00100000;        // Function set cmd(4-bit interface)
#else                                   // Lower nibble interface
        TRIS_DATA_PORT &= 0xf0;
        DATA_PORT &= 0xf0;
        DATA_PORT |= 0b00000010;        // Function set cmd(4-bit interface)
#endif
#endif
        E_PIN = 1;                      // Clock the cmd in
        DelayFor18TCY();
        E_PIN = 0;
        
        // Delay for at least 4.1ms
        DelayXLCD();

        // Setup interface to LCD
#ifdef BIT8                             // 8-bit interface
        DATA_PORT = 0b00110000;         // Function set cmd(8-bit interface)
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
        DATA_PORT &= 0x0f;              // Function set cmd(4-bit interface)
        DATA_PORT |= 0b00100000;
#else                                   // Lower nibble interface
        DATA_PORT &= 0xf0;              // Function set cmd(4-bit interface)
        DATA_PORT |= 0b00000010;
#endif
#endif
        E_PIN = 1;                      // Clock the cmd in
        DelayFor18TCY();
        E_PIN = 0;

        // Delay for at least 100us
        DelayXLCD();

        // Setup interface to LCD
#ifdef BIT8                             // 8-bit interface
        DATA_PORT = 0b00110000;         // Function set cmd(8-bit interface)
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
        DATA_PORT &= 0x0f;              // Function set cmd(4-bit interface)
        DATA_PORT |= 0b00100000;
#else                                   // Lower nibble interface
        DATA_PORT &= 0xf0;              // Function set cmd(4-bit interface)
        DATA_PORT |= 0b00000010;
#endif
#endif
        E_PIN = 1;                      // Clock cmd in
        DelayFor18TCY();
        E_PIN = 0;

#ifdef BIT8                             // 8-bit interface
        TRIS_DATA_PORT = 0xff;          // Make data port input
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
        TRIS_DATA_PORT |= 0xf0;         // Make data nibble input
#else                                   // Lower nibble interface
        TRIS_DATA_PORT |= 0x0f;         // Make data nibble input
#endif
#endif

        // Set data interface width, # lines, font
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(lcdtype);          // Function set cmd

        // Turn the display on then off
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(DOFF&CURSOR_OFF&BLINK_OFF);        // Display OFF/Blink OFF
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(DON&CURSOR_ON&BLINK_ON);           // Display ON/Blink ON

        // Clear display
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(0x01);             // Clear display

        // Set entry mode inc, no shift
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(SHIFT_CUR_LEFT);   // Entry Mode

        // Set DD Ram address to 0
        while(BusyXLCD());              // Wait if LCD busy
        SetDDRamAddr(0);                // Set Display data ram address to 0

//         //return; porque?
}


/********************************************************************
*       Function Name:  WriteDataXLCD                               *
*       Return Value:   void                                        *
*       Parameters:     data: data byte to be written to LCD        *
*       Description:    This routine writes a data byte to the      *
*                       Hitachi HD44780 LCD controller. The user    *
*                       must check to see if the LCD controller is  *
*                       busy before calling this routine. The data  *
*                       is written to the character generator RAM or*
*                       the display data RAM depending on what the  *
*                       previous SetxxRamAddr routine was called.   *
********************************************************************/
void WriteDataXLCD(char data){
#ifdef BIT8                             // 8-bit interface
        TRIS_DATA_PORT = 0;             // Make port output
        DATA_PORT = data;               // Write data to port
        RS_PIN = 1;                     // Set control bits
        RW_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                      // Clock data into LCD
        DelayFor18TCY();
        E_PIN = 0;
        RS_PIN = 0;                     // Reset control bits
        TRIS_DATA_PORT = 0xff;          // Make port input
#else                                   // 4-bit interface
#ifdef UPPER                            // Upper nibble interface
        TRIS_DATA_PORT &= 0x0f;
        DATA_PORT &= 0x0f;
        DATA_PORT |= data&0xf0;
#else                                   // Lower nibble interface
        TRIS_DATA_PORT &= 0xf0;
        DATA_PORT &= 0xf0;
        DATA_PORT |= ((data>>4)&0x0f);
#endif
        RS_PIN = 1;                     // Set control bits
        RW_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                      // Clock nibble into LCD
        DelayFor18TCY();
        E_PIN = 0;
#ifdef UPPER                            // Upper nibble interface
        DATA_PORT &= 0x0f;
        DATA_PORT |= ((data<<4)&0xf0);
#else                                   // Lower nibble interface
        DATA_PORT &= 0xf0;
        DATA_PORT |= (data&0x0f);
#endif
        DelayFor18TCY();
        E_PIN = 1;                      // Clock nibble into LCD
        DelayFor18TCY();
        E_PIN = 0;
#ifdef UPPER                            // Upper nibble interface
        TRIS_DATA_PORT |= 0xf0;
#else                                   // Lower nibble interface
        TRIS_DATA_PORT |= 0x0f;
#endif
#endif
        
}

/********************************************************************
*       Function Name:  putsXLCD
*       Return Value:   void
*       Parameters:     buffer: pointer to string
*       Description:    This routine writes a string of bytes to the
*                       Hitachi HD44780 LCD controller. The user
*                       must check to see if the LCD controller is
*                       busy before calling this routine. The data
*                       is written to the character generator RAM or
*                       the display data RAM depending on what the
*                       previous SetxxRamAddr routine was called.
********************************************************************/

void putsXLCD(char *buffer)
{
        int i;
        //while(*buffer)                  // Write data to LCD up to null
        for(i=0;i<16;i++)
        {
                while(BusyXLCD());        // Wait while LCD is busy
                WriteDataXLCD(buffer[i]); // Write character to LCD
                //andrew
                //WriteDataXLCD(*buffer); // Write character to LCD                
                //buffer++;               // Increment buffer
        }
        return;
}


/******************************************************************************
 * Function:        commandXLCD(unsigned char a)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Esta funcion manda comandos al display y comprueba si esta  ocupado.
 *                        
 *
 * Note:            None
 *****************************************************************************/

void commandXLCD (unsigned char a) { // Envia comando al LCD
    while(BusyXLCD()); 
    WriteCmdXLCD(a);
}



/******************************************************************************
 * Function:        displayInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initialices the resources that the user module needs to work, it is called by the framework 
 *                    when the module is opened    
 *
 * Note:            None
 *****************************************************************************/

void displayInit(void){
    if (display_init) return;
    display_init = TRUE;
    DelayPORXLCD();            /* Espero 60ms @20MHz*/
    commandXLCD(COMANDO_1);        /* Primera palabara de inicializacion*/
    //Delay10KTCYx(8);         /* Espero 4ms @20MHz*/
    //Delay1KTCYx(2);         /* Espero 100us @20MHz*/
    DelayPORXLCD();            /* Espero 60ms @20MHz*/
    commandXLCD(COMANDO_1);        /* Primera palabara de inicializacion*/
    //Delay1KTCYx(2);         /* Espero 100us @20MHz*/
    DelayPORXLCD();            /* Espero 60ms @20MHz*/
    commandXLCD(COMANDO_1);        /* Primera palabara de inicializacion*/
    DelayPORXLCD();
    commandXLCD(COMANDO_2);        /* Segunda palabara de inicializacion*/
    DelayPORXLCD();
    commandXLCD(COMANDO_2);        /* Segunda palabara de inicializacion*/
    DelayPORXLCD();
    commandXLCD(FUNCION_INI);    /* Configuracion de funciones*/
    //commandXLCD(_displayfunction);
    DelayPORXLCD();
    commandXLCD(FUNCION_INI);    /* Configuracion de funciones*/
    DelayPORXLCD();
    //commandXLCD(COMANDO_3);        /* Tercera palabara de inicializacion*/
    commandXLCD(COMANDO_3);        /* Tercera palabara de inicializacion*/
    DelayPORXLCD();
    //commandXLCD(LIMPIAR);        /* Display On, Cursor On, Cursor Blink*/
    DelayPORXLCD();
    commandXLCD(LIMPIAR);        /* Display On, Cursor On, Cursor Blink*/
    //commandXLCD(MODO_ENT);        /* Modo de entrada*/
    DelayPORXLCD();
    commandXLCD(MODO_ENT);        /* Modo de entrada*/
    DelayPORXLCD();
    //commandXLCD(COMANDO_4);        /* Cuarta palabara de inicializacion*/
    commandXLCD(COMANDO_4);        /* Cuarta palabara de inicializacion*/
    DelayPORXLCD();
    //commandXLCD(DON);        /* Limpio el display*/
    commandXLCD(DON);        /* Limpio el display*/
    DelayPORXLCD();
    //commandXLCD(CASA);        /* Voy al inicio del display*/
    commandXLCD(CASA);        /* Voy al inicio del display*/
}//end displayInit
/******************************************************************************
 * Function:        UserDisplayInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initialices the resources that the user module needs to work, it is called by the framework 
 *                    when the module is opened    
 *
 * Note:            None
 *****************************************************************************/

void UserDisplayInit(byte i) {
    usrDisplayHandler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrDisplayHandler,&UserDisplayReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically 
    // addPollingFunction(&UserDisplayProcessIO);
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrDisplay = getSharedBuffer(usrDisplayHandler);
    //inicializo lista de mensajes
    create(&list);
    //inicializo el servicio de eventos
    displayInit();
} //end UserDisplayInit

/******************************************************************************
 * Function:        UserDisplayConfigure(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the specific configuration for the user module, it is called by the framework 
 *                        
 *
 * Note:            None
 *****************************************************************************/
void UserDisplayConfigure(void) {
// Do the configuration
}

void printScreen(byte* msg){ 
    commandXLCD(LINEA_1);
    putsXLCD(msg);
    commandXLCD(LINEA_2); 
    putsXLCD(msg+16);

}

void printLine(byte* msg, byte line){ 
    if(line==0x01){
        commandXLCD(LINEA_1);
        putsXLCD(msg);
    }
    if(line==0x02){
        commandXLCD(LINEA_2); 
        putsXLCD(msg);
    }
}
/***********************************************************************
*
* Callback function to execute periodicaly by te Timmer interrupt ISR
*
************************************************************************/
void dispEvent(void) {    
    int i; byte 
    isEnd = 0;
    ///andres byte msg_string[33];
    byte msg_string[17]; //guardo las pantallas por lineas para ahorrar bytes
    timeOutTicksDisp --;
    if(timeOutTicksDisp <= 0){
        //andres getNextScreen(msg_string, &list, &isEnd);
        getNextLine(msg_string, &list, &isEnd);
/*
        // Esto es para debuggear los punteros
        for(i=16;i<32;i++) msg_string[i] = ' ';
        msg_string[16] = '0' + isEnd;
        msg_string[18] = '0' + list.full / 10;
        msg_string[19] = '0' + list.full % 10;
        msg_string[21] = '0' + list.empty / 10;
        msg_string[22] = '0' + list.empty % 10;
        msg_string[24] = '0' + list.space / 100;
        msg_string[25] = '0' + (list.space % 100) / 10;
        msg_string[26] = '0' + list.space % 10;
        msg_string[11] = ' ';
        msg_string[12] = ' ';
        msg_string[13] = '0' + list.space_mark / 100;
        msg_string[14] = '0' + (list.space_mark % 100) / 10;
        msg_string[15] = '0' + list.space_mark % 10;
        msg_string[28] = '0' + (list.mark % 100) / 10;
        msg_string[29] = '0' + list.mark % 10;
        msg_string[31] = '0' + list.temp % 10;
*/
        ///andres printScreen(msg_string);
        printLine(msg_string, 0x01); 
        getNextLine(msg_string, &list, &isEnd); 
        printLine(msg_string, 0x02); 
        timeOutTicksDisp = cantTicksDisp;
        //isEnd = 0;
    }            
    /*if(isEnd){
        mLED_1_On();
        mLED_2_On();
        mLED_3_On();
    }*/
       
    //if(!isEnd){
        registerT0eventInEvent(DISP_TIME_UNIT, &dispEvent); 
    //}else{
    //    needRegisterDisp = 0;
    //}
    return; //probando si elimina el stack overflow
}

/******************************************************************************
 * Function:        UserDisplayProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is registered in the dinamic polling, who call ir periodically to process the IO interaction
 *                    int the PIC, also it can comunicate things to the pc by the USB    
 *
 * Note:            None
 *****************************************************************************/
void UserDisplayProcessIO(void){  
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    /*if(!needRegisterDisp){
        unregisterT0event(&dispEvent);
        needRegisterDisp = 1;
    }*/
    // here enter the code that want to be called periodically, per example interaction with buttons and leds.    
} //end ProcessIO


/******************************************************************************
 * Function:        UserDesplayRelease(byte i)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function release all the resources that the user module used, it is called by the framework 
 *                    when the module is close    
 *
 * Note:            None
 *****************************************************************************/

void UserDisplayRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i); 
    ///commandXLCD(LIMPIAR);                /*Limpio el display*/ lo comento a ver si mejora que no se prenda el display cuando cierro y abro aplicacion
    //////commandXLCD(COMANDO_2);             /*Limpio la memoria DDRAM*/ /*OJO QUE AL PARECER ESTO ME CUELGA EL DISPLAY*/
    ///commandXLCD(DOFF);                 /* Apago el display*/ lo comento a ver si mejora que no se prenda el display cuando cierro y abro aplicacion
    unregisterT0event(&dispEvent);    
    //removePoolingFunction(&UserDisplayProcessIO);
}


/******************************************************************************
 * Function:        resetList()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Reset The pointers of the list structure so enqueued messages are lost
 *
 * Note:            None
 *****************************************************************************/

void resetList() {
    list.empty      = 0;
    list.full       = 0;
    list.mark       = 0;
    list.space      = LIST_SIZE;
    list.space_mark = 0;
}

/******************************************************************************
 * Function:        UserDisplayReceived(byte* recBuffPtr, byte len)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function manages the comunication with the pc
 *
 * Note:            None
 *****************************************************************************/

void UserDisplayReceived(byte* recBuffPtr, byte len){
    byte largo_msg_agendar, tmp, index, isCiclic, last_msg, j;
    char linea_display[17];     /* caracteres a mostrar en el display en la linea x*/
    int i=0;
    byte userDisplayCounter = 0;
    byte error = 0;
    char screen_msg[32];
    /*char msg_string1[] = "pase 1  ";    
    char msg_string2[] = "pase 2  ";*/
    last_msg = 0;  

      
    switch(((DISPLAY_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
            //dataPacket._byte[1] is len
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[1] = DISPLAY_MINOR_VERSION;
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[2] = DISPLAY_MAJOR_VERSION;
            userDisplayCounter=0x03;
            break;
        case ESCRIBIR:
            //displayInit();
            unregisterT0event(&dispEvent);
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            for(i=1;i<33;i++){
                if(i<17){
                    linea_display[i-1]= ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[i];
                    if (linea_display[i-1] == '_'){
                        linea_display[i-1] = ' ';
                    }
                }else{
                    if(i==17) printLine(linea_display, 0x01);
                    linea_display[i-17]= ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[i];
                    if (linea_display[i-17] == '_'){
                        linea_display[i-17] = ' ';
                    }
                }
            }
            printLine(linea_display, 0x02);
            /*commandXLCD(LIMPIAR);
            commandXLCD(CASA);*/        
            userDisplayCounter=0x02; 
            if(contBusy >= maxContBusy){
                ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[1] = BUSY;
            }else{
                ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[1] = NO_BUSY;
            }    
            break;  
        case SET_TICKS:
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0]; /* codigo de operacion */
            cantTicksDisp = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[1]; /* largo del mensaje */
            userDisplayCounter=0x01;
            break;
        case AGENDAR_MSG:
            if (!init) {
                resetList();
                init = 1;
            }
            /* Un problema que se prensenta es que los paquetes que se intercambian a nivel de USB son de 64bytes, por lo tanto la fragmentacion
            la vamos a realizar en el alto nivel, no en el firmware, pero se brindan primitivas para poder hacer agendado de eventos. 
            Si el 3er byte vale 1 indica el fin del mensaje, si es 0 indica que faltan caracteres para completar
            el mensaje*/
            timeOutTicksDisp = 1;
            mensaje_agendar_iterator = 0;
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0]; /* codigo de operacion */
            largo_msg_agendar = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[1]; /* largo del mensaje */
            last_msg          = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[2]; /* indica si es el fin de un mensaje */
            isCiclic          = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[3]; /* es un mensaje ciclico? */

            for(i=0;i<32;i++) screen_msg[i]=' ';
            if(startMsg) {
                startCommitiableInsert(&list);
                startMsg = 0;
                unregisterT0event(&dispEvent);
            }    
            for(i=4;i<largo_msg_agendar+5;i++){
                tmp = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[i];
                if (tmp == '_') {
                    tmp = ' ';
                }                                
                mensaje_agendar[mensaje_agendar_iterator] = tmp;
                mensaje_agendar_iterator ++;
            }
            error = insertCommitiable(mensaje_agendar, largo_msg_agendar, &list, isCiclic);
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[1] = error; /* error en caso de que no haya espacio libre en la estructura   */ 
            for(i=0;i<32;i++) screen_msg[i]=' ';
            /*if(error){
                screen_msg[0] = 'e';
                screen_msg[1] = 'r';
                screen_msg[2] = 'r';
                screen_msg[3] = 'o';
                screen_msg[4] = 'r';
            }else{
                screen_msg[0] = 'o';
                screen_msg[1] = 'k';         
            }*/
/*
            // Esto es para debuggear los punteros
            screen_msg[16] = '0' + last_msg;
            screen_msg[18] = '0' + list.full / 10;
            screen_msg[19] = '0' + list.full % 10;
            screen_msg[21] = '0' + list.empty / 10;
            screen_msg[22] = '0' + list.empty % 10;
            screen_msg[24] = '0' + list.space / 100;
            screen_msg[25] = '0' + (list.space % 100) / 10;
            screen_msg[26] = '0' + list.space % 10;
            screen_msg[11] = ' ';
            screen_msg[12] = ' ';
            screen_msg[13] = '0' + list.space_mark / 100;
            screen_msg[14] = '0' + (list.space_mark % 100) / 10;
            screen_msg[15] = '0' + list.space_mark % 10;
            screen_msg[28] = '0' + (list.mark % 100) / 10;
            screen_msg[29] = '0' + list.mark % 10;
*/
            // printScreen(screen_msg);
            if(last_msg == 1){ /* si llegue al final del mensaje */
                commit(&list);
                startMsg = 1;
                //printScreen(screen_msg);
                registerT0event(DISP_TIME_UNIT, &dispEvent);
            }            
            if(contBusy >= maxContBusy){
                ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[2] = BUSY;
            }else{
                ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[2] = NO_BUSY;
            }	
            userDisplayCounter=0x03;
            break;
        case PRUEBA:    
             /* lo pele en la version 2.4.20*/
             userDisplayCounter=0x01;
            break;
        case BORRAR: 
            ///andres commandXLCD(LIMPIAR);
            ///andres commandXLCD(COMANDO_2);     /*Limpio la memoria DDRAM*/
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0];
            // Ahora el borrado genera que se reseté la lista y se desencolen los mensajes viejos
            resetList();
            unregisterT0event(&dispEvent);
            // ------------------------------
            userDisplayCounter=0x01;
            break;
        case INICIAR:
            ///display_init = FALSE;
            displayInit();
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            userDisplayCounter=0x01;
            break;
        case PRENDER_BKL:
            BACK_LIGHT_ON();
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            userDisplayCounter=0x01;
            break;
        case APAGAR_BKL:
            BACK_LIGHT_OFF();
            ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            userDisplayCounter=0x01;
            break;
        case RESET:
            DelayPORXLCD();Reset(); /*invocar el reset en el admin */
            break;
    }//end switch(s)
    if(userDisplayCounter != 0){
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); // pruebo un máximo de 255 veces
            if(!mUSBGenTxIsBusy()){
                USBGenWrite2(usrDisplayHandler, userDisplayCounter);
            }
    }//end if          
} //end UserDisplayReceived


/** EOF usr_display.c ***************************************************************/