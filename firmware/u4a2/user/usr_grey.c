/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca                                      19/04/12    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_grey.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "dynamicPolling.h"
#include "user/usb4butia.h"     /**/

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrGrey; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserGreyProcessIO(void);
void UserGreyInit(byte i);
void UserGreyReceived(byte*, byte, byte);
void UserGreyRelease(byte i);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userGreyModuleTable = {&UserGreyInit, &UserGreyRelease, "grey"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserGreyInit(void)
 *
 * PreCondition:    None
 *
 * Input:           module handler identifier
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initialices the resources that the user
 *                  module needs to work, it is called by the framework when
 *                  the module is opened.
 *
 * Note:            None
 *****************************************************************************/
void UserGreyInit(byte usrGreyHandler) {
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(usrGreyHandler, &UserGreyReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrGrey = getSharedBuffer(usrGreyHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(usrGreyHandler)->change_port_direction(IN);
}/*end UserGreyInit*/

/******************************************************************************
 * Function:        UserGreyProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is registered in the dinamic polling, who
 *                  calls it periodically to process the IO interaction in the
 *                  PIC, it also can comunicate things to the pc by the USB.
 *
 * Note:            None
 *****************************************************************************/
void UserGreyProcessIO(void) {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == (unsigned) 1)) return;
    /* here enter the code that want to be called periodically,
     * per example interaction with buttons and leds */
}/*end UserGreyProcessIO*/

/******************************************************************************
 * Function:        UserGreyRelease(byte i)
 *
 * PreCondition:    None
 *
 * Input:           module handler identifier
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function release all the resources that the user
 *                  module used, it is called by the framework
 *                  when the module is close.
 *
 * Note:            None
 *****************************************************************************/
void UserGreyRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}/*end UserGreyRelease*/

/******************************************************************************
 * Function:        UserGreyReceived(byte* recBuffPtr, byte len)
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
void UserGreyReceived(byte* recBuffPtr, byte len, byte handler) {
    WORD data;
    byte userGreyCounter = 0;
    switch (((GREY_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((GREY_DATA_PACKET*) sendBufferUsrGrey)->_byte[0] = ((GREY_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((GREY_DATA_PACKET*) sendBufferUsrGrey)->_byte[1] = GREY_MINOR_VERSION;
            ((GREY_DATA_PACKET*) sendBufferUsrGrey)->_byte[2] = GREY_MAJOR_VERSION;
            userGreyCounter = 0x03;
            break;

        case GET_VALUE:
            ((GREY_DATA_PACKET*) sendBufferUsrGrey)->_byte[0] = ((GREY_DATA_PACKET*) recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((GREY_DATA_PACKET*) sendBufferUsrGrey)->_byte[1] = LSB(data);
            ((GREY_DATA_PACKET*) sendBufferUsrGrey)->_byte[2] = MSB(data);
            userGreyCounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    USBGenWrite2(handler, userGreyCounter);

}/*end UserGreyReceived*/

/** EOF usr_grey.c ***************************************************************/
