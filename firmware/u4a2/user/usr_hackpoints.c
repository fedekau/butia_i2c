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
    PORTD = ZERO;
    TRISD = INPUT;
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
    PORTD = ZERO;
    TRISD = INPUT;
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
    int pin;

    switch (((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->CMD) {
        case READ_VERSION:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = HACK_POINTS_MINOR_VERSION;
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[2] = HACK_POINTS_MAJOR_VERSION;
            HackPointsCounter = 0x03;
            break;

        case SET_MODE:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            pin = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            if (((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[2] == (byte) 1){
                //salida
                TRISD = TRISD & ~(byte) (MASK << pin);
            } else {
                //entrada
                TRISD = TRISD | (byte) (MASK << pin);
            }
            HackPointsCounter = 0x01;
            break;

        case WRITE:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            pin = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            if (((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[2] == (byte) 1){
                PORTD = PORTD | (byte) (MASK << pin);
            } else {
                PORTD = PORTD & ~(byte) (MASK << pin);
            }
            //seteo como salida siempre?
            TRISD = TRISD & ~(byte) (MASK << pin);
            HackPointsCounter = 0x01;
            break;

        case SET_PORT:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTD = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            TRISD = OUTPUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PORT_IN:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTD = ZERO;
            TRISD = INPUT;
            HackPointsCounter = 0x01;
            break;

        case SET_PORT_OUT:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            PORTD = ZERO;
            TRISD = OUTPUT;
            HackPointsCounter = 0x01;
            break;

        case READ:
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[0] = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[0];
            pin = ((HACK_POINTS_DATA_PACKET*) recBufferHackPoints)->_byte[1];
            ((HACK_POINTS_DATA_PACKET*) sendBufferHackPoints)->_byte[1] = (PORTD & (MASK<<pin))>>pin;
            TRISD = TRISD | (byte) (MASK << pin);
            HackPointsCounter = 0x02;
            break;

        default:
            break;
    }/*end switch(s) */
    if (HackPointsCounter != (byte) 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > (byte) 0);
            if (!mUSBGenTxIsBusy())
                USBGenWrite2(handler, HackPointsCounter);
    }/*end if*/
}/*end HACK_POINTSReceived*/

/** EOF HACK_POINTS.c ***************************************************************/
