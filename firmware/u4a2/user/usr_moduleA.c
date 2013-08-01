/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alan Aguiar                                      01/08/123   Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_moduleA.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "user/usb4butia.h"     /**/

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrModuleA; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserModuleAProcessIO(void);
void UserModuleAInit(byte i);
void UserModuleAReceived(byte*, byte, byte);
void UserModuleARelease(byte i);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userModuleAModuleTable = {&UserModuleAInit, &UserModuleARelease, "moduleA"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserModuleAInit(void)
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
void UserModuleAInit(byte usrModuleAHandler) {
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(usrModuleAHandler, &UserModuleAReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrModuleA = getSharedBuffer(usrModuleAHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(usrModuleAHandler)->change_port_direction(IN);
}/*end UserModuleAInit*/

/******************************************************************************
 * Function:        UserModuleAProcessIO(void)
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
void UserModuleAProcessIO(void) {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == (unsigned) 1)) return;
    /* here enter the code that want to be called periodically,
     * per example interaction with buttons and leds */
}/*end UserModuleAProcessIO*/

/******************************************************************************
 * Function:        UserModuleARelease(byte i)
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
void UserModuleARelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}/*end UserModuleARelease*/

/******************************************************************************
 * Function:        UserModuleAReceived(byte* recBuffPtr, byte len)
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
void UserModuleAReceived(byte* recBuffPtr, byte len, byte handler) {
    WORD data;
    byte userModuleACounter = 0;
    switch (((MODULEA_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((MODULEA_DATA_PACKET*) sendBufferUsrModuleA)->_byte[0] = ((MODULEA_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((MODULEA_DATA_PACKET*) sendBufferUsrModuleA)->_byte[1] = MODULEA_MINOR_VERSION;
            ((MODULEA_DATA_PACKET*) sendBufferUsrModuleA)->_byte[2] = MODULEA_MAJOR_VERSION;
            userModuleACounter = 0x03;
            break;

        case GET_VALUE:
            ((MODULEA_DATA_PACKET*) sendBufferUsrModuleA)->_byte[0] = ((MODULEA_DATA_PACKET*) recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((MODULEA_DATA_PACKET*) sendBufferUsrModuleA)->_byte[1] = LSB(data);
            ((MODULEA_DATA_PACKET*) sendBufferUsrModuleA)->_byte[2] = MSB(data);
            userModuleACounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    USBGenWrite2(handler, userModuleACounter);

}/*end UserModuleAReceived*/

/** EOF usr_moduleA.c ***************************************************************/
