/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andrés Aguirre, Rafael Fernandez, Carlos Grossy       16/10/07    Original.
 * Ayle 25/01/13
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/userLoopBack.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"                              


/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrLoopback; // buffer to send data

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserLoopBackProcessIO(void);
void UserLoopBackInit(byte i);
void UserLoopBackReceived(byte*, byte, byte);
void UserLoopBackRelease(byte i);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab UserLoopBackModuleTable = {&UserLoopBackInit, &UserLoopBackRelease, "lback"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserLoopBackInit(void)
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
 *					when the module is opened	
 *
 * Note:            None
 *****************************************************************************/

void UserLoopBackInit(byte usrLoopbackHandler) {
    BOOL res;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrLoopbackHandler, &UserLoopBackReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically
    res = addPollingFunction(&UserLoopBackProcessIO);
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrLoopback = getSharedBuffer(usrLoopbackHandler);
}//end UserLoopBackInit

/******************************************************************************
 * Function:        UserLoopBackProcessIO(void)
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

void UserLoopBackProcessIO(void) {

    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == (unsigned) 1)) return;
    // here enter the code that want to be called periodically, per example interaction with buttons and leds

}//end ProcessIO

/******************************************************************************
 * Function:        UserLoopBackRelease(byte i)
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

void UserLoopBackRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    removePoolingFunction(&UserLoopBackProcessIO);
}

/******************************************************************************
 * Function:        UserLoopBackReceived(byte* recBuffPtr, byte len)
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

void UserLoopBackReceived(byte* recBuffPtr, byte len, byte handler) {
    byte UserLoopBackCounter = 0;

    switch (((LOOPBACK_DATA_PACKET*) recBuffPtr)->CMD) {
        case LOOPBACK_VERSION:
            ((LOOPBACK_DATA_PACKET*) sendBufferUsrLoopback)->_byte[0] = ((LOOPBACK_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((LOOPBACK_DATA_PACKET*) sendBufferUsrLoopback)->_byte[1] = LOOPBACK_MINOR_VERSION;
            ((LOOPBACK_DATA_PACKET*) sendBufferUsrLoopback)->_byte[2] = LOOPBACK_MAJOR_VERSION;
            UserLoopBackCounter = 0x03;
            break;

        case SEND_DATA:
            // we must return all: opcode + data
            for (UserLoopBackCounter = 0; UserLoopBackCounter < len; UserLoopBackCounter++) {
                *(sendBufferUsrLoopback + UserLoopBackCounter) = *(recBuffPtr + UserLoopBackCounter); // TODO pensar algo mas eficiente
            }
            UserLoopBackCounter = len; //por las dudas
            break;
    }
    
    USBGenWrite2(handler, UserLoopBackCounter);

}//end UserLoopBackReceived

/** EOF usr_skeleton.c ***************************************************************/
