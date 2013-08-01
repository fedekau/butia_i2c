/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alan Aguiar                                      01/08/123   Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_moduleC.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "user/usb4butia.h"     /**/

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrModuleC; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserModuleCProcessIO(void);
void UserModuleCInit(byte i);
void UserModuleCReceived(byte*, byte, byte);
void UserModuleCRelease(byte i);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userModuleCModuleTable = {&UserModuleCInit, &UserModuleCRelease, "moduleC"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserModuleCInit(void)
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
void UserModuleCInit(byte usrModuleCHandler) {
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(usrModuleCHandler, &UserModuleCReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrModuleC = getSharedBuffer(usrModuleCHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(usrModuleCHandler)->change_port_direction(IN);
}/*end UserModuleCInit*/

/******************************************************************************
 * Function:        UserModuleCProcessIO(void)
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
void UserModuleCProcessIO(void) {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == (unsigned) 1)) return;
    /* here enter the code that want to be called periodically,
     * per example interaction with buttons and leds */
}/*end UserModuleCProcessIO*/

/******************************************************************************
 * Function:        UserModuleCRelease(byte i)
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
void UserModuleCRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}/*end UserModuleCRelease*/

/******************************************************************************
 * Function:        UserModuleCReceived(byte* recBuffPtr, byte len)
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
void UserModuleCReceived(byte* recBuffPtr, byte len, byte handler) {
    WORD data;
    byte userModuleCCounter = 0;
    switch (((MODULEC_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((MODULEC_DATA_PACKET*) sendBufferUsrModuleC)->_byte[0] = ((MODULEC_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((MODULEC_DATA_PACKET*) sendBufferUsrModuleC)->_byte[1] = MODULEC_MINOR_VERSION;
            ((MODULEC_DATA_PACKET*) sendBufferUsrModuleC)->_byte[2] = MODULEC_MAJOR_VERSION;
            userModuleCCounter = 0x03;
            break;

        case GET_VALUE:
            ((MODULEC_DATA_PACKET*) sendBufferUsrModuleC)->_byte[0] = ((MODULEC_DATA_PACKET*) recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((MODULEC_DATA_PACKET*) sendBufferUsrModuleC)->_byte[1] = LSB(data);
            ((MODULEC_DATA_PACKET*) sendBufferUsrModuleC)->_byte[2] = MSB(data);
            userModuleCCounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    USBGenWrite2(handler, userModuleCCounter);

}/*end UserModuleCReceived*/

/** EOF usr_moduleC.c ***************************************************************/
