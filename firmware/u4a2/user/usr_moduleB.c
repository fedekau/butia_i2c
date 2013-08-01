/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alan Aguiar                                      01/08/123   Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_moduleB.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "user/usb4butia.h"     /**/

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrModuleB; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserModuleBProcessIO(void);
void UserModuleBInit(byte i);
void UserModuleBReceived(byte*, byte, byte);
void UserModuleBRelease(byte i);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userModuleBModuleTable = {&UserModuleBInit, &UserModuleBRelease, "moduleB"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserModuleBInit(void)
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
void UserModuleBInit(byte usrModuleBHandler) {
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(usrModuleBHandler, &UserModuleBReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrModuleB = getSharedBuffer(usrModuleBHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(usrModuleBHandler)->change_port_direction(IN);
}/*end UserModuleBInit*/

/******************************************************************************
 * Function:        UserModuleBProcessIO(void)
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
void UserModuleBProcessIO(void) {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == (unsigned) 1)) return;
    /* here enter the code that want to be called periodically,
     * per example interaction with buttons and leds */
}/*end UserModuleBProcessIO*/

/******************************************************************************
 * Function:        UserModuleBRelease(byte i)
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
void UserModuleBRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}/*end UserModuleBRelease*/

/******************************************************************************
 * Function:        UserModuleBReceived(byte* recBuffPtr, byte len)
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
void UserModuleBReceived(byte* recBuffPtr, byte len, byte handler) {
    WORD data;
    byte userModuleBCounter = 0;
    switch (((MODULEB_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((MODULEB_DATA_PACKET*) sendBufferUsrModuleB)->_byte[0] = ((MODULEB_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((MODULEB_DATA_PACKET*) sendBufferUsrModuleB)->_byte[1] = MODULEB_MINOR_VERSION;
            ((MODULEB_DATA_PACKET*) sendBufferUsrModuleB)->_byte[2] = MODULEB_MAJOR_VERSION;
            userModuleBCounter = 0x03;
            break;

        case GET_VALUE:
            ((MODULEB_DATA_PACKET*) sendBufferUsrModuleB)->_byte[0] = ((MODULEB_DATA_PACKET*) recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((MODULEB_DATA_PACKET*) sendBufferUsrModuleB)->_byte[1] = LSB(data);
            ((MODULEB_DATA_PACKET*) sendBufferUsrModuleB)->_byte[2] = MSB(data);
            userModuleBCounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    USBGenWrite2(handler, userModuleBCounter);

}/*end UserModuleBReceived*/

/** EOF usr_moduleB.c ***************************************************************/
