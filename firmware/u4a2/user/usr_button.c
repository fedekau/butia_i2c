/* Author ayle			  Date 10/03/2012       Comment
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_button.h"
#include "io_cfg.h"              /* I/O pin mapping */
#include "user/handlerManager.h"
#include "dynamicPolling.h"                              
#include "user/usb4butia.h"

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrButton; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserButtonProcessIO(void);
void UserButtonInit(byte i);
void UserButtonReceived(byte*, byte, byte);
void UserButtonRelease(byte i);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab userButtonModuleTable = {&UserButtonInit, &UserButtonRelease, "button"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserButtonInit(byte)
 *
 * PreCondition:    None
 *
 * Input:           handler
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initialices the resources that the user module needs to work,
 *                   it is called by the framework when the module is opened
 *
 * Note:            None
 *****************************************************************************/

void UserButtonInit(byte handler) {
    /* add my receive function to the handler module, to be called automatically when the pc sends data to the user module*/
    setHandlerReceiveFunction(handler, &UserButtonReceived);
    /* initialize the send buffer, used to send data to the PC*/
    sendBufferUsrButton = getSharedBuffer(handler);
    getPortDescriptor(handler)->change_port_direction(IN);
}/*end UserButtonInit*/

/******************************************************************************
 * Function:        UserButtonProcessIO(void)
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
 *					int the PIC, also it can comunicate things to the pc by the USB	
 *
 * Note:            None
 *****************************************************************************/

void UserButtonProcessIO(void) {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == 1)) return;
    /* here enter the code that want to be called periodically, per example interaction with buttons and leds*/

}/*end ProcessIO*/

/******************************************************************************
 * Function:        UserButtonRelease(byte i)
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
 *					when the module is close	
 *
 * Note:            None
 *****************************************************************************/

void UserButtonRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}

/******************************************************************************
 * Function:        UserButtonReceived(byte* recBuffPtr, byte len)
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

void UserButtonReceived(byte* recBuffPtr, byte len, byte handler) {
    byte j;
    byte userButtonCounter = 0;

    switch (((BUTTON_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((BUTTON_DATA_PACKET*) sendBufferUsrButton)->_byte[0] = ((BUTTON_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((BUTTON_DATA_PACKET*) sendBufferUsrButton)->_byte[1] = BUTTON_MINOR_VERSION;
            ((BUTTON_DATA_PACKET*) sendBufferUsrButton)->_byte[2] = BUTTON_MAJOR_VERSION;
            userButtonCounter = 0x03;
            break;

        case GET_VALUE:
            ((BUTTON_DATA_PACKET*) sendBufferUsrButton)->_byte[0] = ((BUTTON_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((BUTTON_DATA_PACKET*) sendBufferUsrButton)->_byte[1] = getPortDescriptor(handler)->get_data_digital();
            userButtonCounter = 0x02;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/
    if (userButtonCounter != 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > 0); /* pruebo un maximo de 255 veces */
            if (!mUSBGenTxIsBusy())
                USBGenWrite2(handler, userButtonCounter);
    }/*end if */

}/*end UserButtonReceived*/

/** EOF usr_button.c ***************************************************************/