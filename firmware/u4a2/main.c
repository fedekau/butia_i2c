/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.0
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the ?Company?) for its PICmicro? Microcontroller is intended and
 * supplied to you, the Company?s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04    Original.
 * Rafael Fernandez     10/03/07
 * Andres Aguirre	    27/03/07
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <delays.h>
#include "system/typedefs.h"                        // Required
#include "system/usb/usb.h"                         // Required
#include "io_cfg.h"                                 // Required

#include "system/usb/usb_compile_time_validation.h" // Optional
//#include "user/dynamicPolling.h"                    // Modifiable
#include "usb4all/dynamicISR/dynamicISR.h"          // Modifiable
#include "usb4all/proxys/T0Service.h"
//#include "usb4all/proxys/T1Service.h"

#include "user/handlerManager.h"                              // Modifiable
#include "user/ax12.h"

#include "user/usb4butia.h"

#pragma code sys

/** Fuses configurarion ******************************************************/

/* 96MHZ PLL Prescaler */
#pragma config PLLDIV = 5

/* CPU System Colock Postscaler */
#pragma config CPUDIV = OSC1_PLL2

/* Full-Speed USB Clock Source Selection */
#pragma config USBDIV = 2

/* Oscillator Selection bits */
#pragma config FOSC = HS       /*needed for reach 1MBps in serial */
//#pragma config FOSC = HSPLL_HS

/* Fail Safe Clock Monitor */
#pragma config FCMEN = OFF

/* Internel/External Switch Over */
#pragma config IESO = OFF

/* Power Up Timer*/
#pragma config PWRT = OFF

/* Brown Out Voltage */
#pragma config BOR  = ON
#pragma config BORV = 3

/* USB Voltage Regulatro Enable */
#pragma config VREGEN = ON

/* Watchdig Timer*/
#pragma config WDT = OFF

/* Watchdog Postscaler */
#pragma config WDTPS = 32768

/* MCLR Enable */
#pragma config MCLRE = ON

/* Low Power Timmer1 Oscillator Enable */
#pragma config LPT1OSC = OFF

/* Port B A/D Enable */
#pragma config PBADEN = ON

/* CCP2 Mux bit*/
#pragma config CCP2MX = ON

/* Stack Overflow Reset */
#pragma config STVREN = ON

/* Low Voltage ICSP */
#pragma config LVP = OFF

/* Dedicated In-Circuit Debug/Programming Enable */
#pragma config ICPRT = OFF

/* Extended Instruction Set Enable */
#pragma config XINST = OFF

/* Background Debbuger Enable */
#pragma config DEBUG = OFF

/* Code Protection Block 0 */
#pragma config CP0 = OFF

/* Code Protection Block 1 */
#pragma config CP1 = OFF

/* Code Protection Block 2 */
#pragma config CP2 = OFF

/* Code Protection Block 3 */
#pragma config CP3 = OFF

/* Boot Block Code Protection */
#pragma config CPB = OFF

/* Data EEPROM Code Protection */
#pragma config CPD = OFF

/* Write Protection Block 0 */
#pragma config WRT0 = OFF

/* Write Protection Block 1 */
#pragma config WRT1 = OFF

/* Write Protection Block 2 */
#pragma config WRT2 = OFF

/* Write Protection Block 3 */
#pragma config WRT3 = OFF

/* Boot Block Write Protection */
#pragma config WRTB = OFF

/* Configuration Register Write Protection */
#pragma config WRTC = OFF

/* Data EEPROM Write Protection */
#pragma config WRTD = OFF

/* Table Read Protection Block 0 */
#pragma config EBTR0 = OFF

/* Table Read Protection Block 1 */
#pragma config EBTR1 = OFF

/* Table Read Protection Block 2 */
#pragma config EBTR2 = OFF

/* Table Read Protection Block 3 */
#pragma config EBTR3 = OFF

/* Boot Block Table Read Protection */
#pragma config EBTRB = OFF

/** V A R I A B L E S ********************************************************/
#pragma udata

/** P R I V A T E  P R O T O T Y P E S ***************************************/
static void InitializeSystem(void);
void USBTasks(void);

/** V E C T O R  R E M A P P I N G *******************************************/

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x0008C0
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code sys

//#pragma interrupt interruption save=section(".tmpdata")
#pragma code _HIGH_INTERRUPT_VECTOR = 0x0008C8
void _high_ISR (void)
{
    _asm GOTO interruption _endasm //llamo a interruption() de dynamicISR
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x0008D8
void _low_ISR (void)
{
    //interruption();
}
//#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code sys

/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *****************************************************************************/

#define WAIT_SECONDS(s) {int i; for(i=0; i<10*(s); i++) Delay10KTCYx(250);}

void main(void) {
    InitializeSystem();
    while(1) {
        USBTasks();         // USB Tasks
        //polling();
        USBGenRead2();
    }//end while
}//end main

/******************************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization routine.
 *                  All required USB initialization routines are called from
 *                  here.
 *
 *                  User application initialization routine should also be
 *                  called from here.
 *
 * Note:            None
 *****************************************************************************/
static void InitializeSystem(void) {
    mInitPortA();mInitPortB();mInitPortC();mInitPortD();mInitPortE(); // set pins as input for safety and interference avoid
    ax12InitSerial();
    ADCON1 = ADCON1 & 0xF0;        /* Default all pins to analogic */
    ADCON0bits.ADON = 1;            /* Enable Analogic */

    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See io_cfg.h
    #endif

    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;
    #endif

    mInitializeUSBDriver();         // See usbdrv.h

    initISRFunctions();      // Initialize interrupt service routines mechanism of USB4all
    initT0Service();         // Inicializa servicio T0 para manejar recurso de timmer
    //initT1Service();         // Inicializa servicio T1 para manejar recurso de timmer
    //initPollingFunctions();  // inicializa el buffer con 0s (dynamicPolling.c)
    initHandlerManager();    // inicializa el map de enpoints y crea el enpoint 0 (adminModule.c)

}//end InitializeSystem

/******************************************************************************
 * Function:        void USBTasks(void)
 *
 * PreCondition:    InitializeSystem has been called.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Service loop for USB tasks.
 *
 * Note:            None
 *****************************************************************************/
void USBTasks(void) {
    /*
    * Servicing Hardware
    */
    USBCheckBusStatus();                    // Must use polling method
    if(UCFGbits.UTEYE!= (unsigned) 1)
        USBDriverService();                 // Interrupt or polling method

}// end USBTasks

#pragma code sys
/** EOF main.c ***************************************************************/
