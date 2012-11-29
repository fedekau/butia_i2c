/* Author                           Date                Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ayle                             08/11/2012
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_hackpoints.h"
#include "io_cfg.h"              /* I/O pin mapping */
#include "user/handlerManager.h"
#include "dynamicPolling.h"   
#include "usb4all/proxys/T0Proxy.h"


/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferHackPoints; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void HackPointsProcessIO(void);
void HackPointsInit(byte i);
void HackPointsReceived(byte*, byte, byte);
void HackPointsRelease(byte i);

/* Table used by te framework to get a fixed reference point
 * to the user module functions defined by the framework
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab HackPointsModuleTable = {&HackPointsInit, &HackPointsRelease, "hackp"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UseTestResInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *   
 * Overview:        This function is initialices the resources that the user module needs to work, it is called by the framework 
 *                    when the module is opened    
 *
 * Note:            None
 *****************************************************************************/

void HackPointsInit(byte handler) {
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(handler, &HackPointsReceived);

    /* initialize the send buffer, used to send data to the PC */
    sendBufferHackPoints = getSharedBuffer(handler);

    /* setting pins to IN mode*/
    PORTDbits.RD4 = OFF;
    PORTDbits.RD5 = OFF;
    PORTDbits.RD6 = OFF;
    PORTDbits.RD7 = OFF;
    TRISDbits.RD4 = IN;
    TRISDbits.RD5 = IN;
    TRISDbits.RD6 = IN;
    TRISDbits.RD7 = IN;
}/*end UserLedAmarilloInit*/

void HackPointsProcessIO(void) {
}/*end ProcessIO */

/******************************************************************************
 * Function:        HACK_POINTSRelease(byte i)
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

void HackPointsRelease(byte handler) {
    unsetHandlerReceiveBuffer(handler);
    unsetHandlerReceiveFunction(handler);
    PORTDbits.RD4 = OFF;
    PORTDbits.RD5 = OFF;
    PORTDbits.RD6 = OFF;
    PORTDbits.RD7 = OFF;
    TRISDbits.RD4 = IN;
    TRISDbits.RD5 = IN;
    TRISDbits.RD6 = IN;
    TRISDbits.RD7 = IN;
}

/******************************************************************************
 * Function:        HACK_POINTSReceived(byte* recBuffPtr, byte len)
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

void HackPointsReceived(byte* recBufferHackPoints, byte len, byte handler) {
    byte j;
    byte HackPointsCounter = 0;

    switch (((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->CMD) {
        case READ_VERSION:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = HACK_POINTS_MINOR_VERSION;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[2] = HACK_POINTS_MAJOR_VERSION;
            HackPointsCounter = 0x03;
            break;

        case WRITE:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            HackPointsCounter = 0x01;
            break;

        case SET_HIGH_PINS:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD6 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            PORTDbits.RD5 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[2];
            PORTDbits.RD4 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[3];
            PORTDbits.RD7 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[4];
            TRISDbits.RD6 = OUT;
            TRISDbits.RD5 = OUT;
            TRISDbits.RD4 = OUT;
            TRISDbits.RD7 = OUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PIN19:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD0 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISDbits.RD0 = OUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PIN20:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD1 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISDbits.RD1 = OUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PIN21:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD2 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISDbits.RD2 = OUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PIN22:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD3 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISDbits.RD3 = OUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PIN27:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD4 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISDbits.RD4 = OUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PIN28:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD5 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISDbits.RD5 = OUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PIN29:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD6 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISDbits.RD6 = OUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PIN30:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTDbits.RD7 = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISDbits.RD7 = OUT;
            HackPointsCounter = 0x01;
            break;

        case GET_PIN19:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            TRISDbits.RD0 = OUT;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = PORTDbits.RD0;
            HackPointsCounter = 0x02;
            break;

        case GET_PIN20:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            TRISDbits.RD1 = IN;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = PORTDbits.RD1;
            HackPointsCounter = 0x02;
            break;

        case GET_PIN21:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            TRISDbits.RD2 = IN;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = PORTDbits.RD2;
            HackPointsCounter = 0x02;
            break;

        case GET_PIN22:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            TRISDbits.RD3 = IN;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = PORTDbits.RD3;
            HackPointsCounter = 0x02;
            break;

        case GET_PIN27:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            TRISDbits.RD4 = OUT;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = PORTDbits.RD4;
            HackPointsCounter = 0x02;
            break;

        case GET_PIN28:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            TRISDbits.RD5 = IN;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = PORTDbits.RD5;
            HackPointsCounter = 0x02;
            break;

        case GET_PIN29:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            TRISDbits.RD6 = IN;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = PORTDbits.RD6;
            HackPointsCounter = 0x02;
            break;

        case GET_PIN30:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            TRISDbits.RD7 = IN;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = PORTDbits.RD7;
            HackPointsCounter = 0x02;
            break;

        default:
            break;
    }/*end switch(s) */
    if (HackPointsCounter != 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > 0);
        if (!mUSBGenTxIsBusy())
            USBGenWrite2(handler, HackPointsCounter);
    }/*end if*/
}/*end HACK_POINTSReceived*/

/** EOF HACK_POINTS.c ***************************************************************/
