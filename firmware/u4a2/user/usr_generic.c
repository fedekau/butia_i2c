/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alan Aguiar                                      01/08/123   Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_generic.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "user/usb4butia.h"

/** V A R I A B L E S ********************************************************/
#pragma udata

byte* sendBufferUsrGeneric; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserGenericInit(byte handler);
void UserGenericReceived(byte*, byte, byte);
void UserGenericRelease(byte handler);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userModuleATable = {&UserGenericInit, &UserGenericRelease, "moduleA"};
const uTab userModuleBTable = {&UserGenericInit, &UserGenericRelease, "moduleB"};
const uTab userModuleCTable = {&UserGenericInit, &UserGenericRelease, "moduleC"};
const uTab userGreyModuleTable = {&UserGenericInit, &UserGenericRelease, "grey"};
const uTab userLightModuleTable = {&UserGenericInit, &UserGenericRelease, "light"};
const uTab userResModuleTable = {&UserGenericInit, &UserGenericRelease, "res"};
const uTab userVoltModuleTable = {&UserGenericInit, &UserGenericRelease, "volt"};
const uTab userTempModuleTable = {&UserGenericInit, &UserGenericRelease, "temp"};
const uTab userDistModuleTable = {&UserGenericInit, &UserGenericRelease, "distanc"};

#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserGenericInit(void)
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
void UserGenericInit(byte handler) {
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(handler, &UserGenericReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrGeneric = getSharedBuffer(handler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(handler)->change_port_direction(IN);
}/*end UserModuleAInit*/


/******************************************************************************
 * Function:        UserGenericRelease(byte i)
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
void UserGenericRelease(byte handler) {
    unsetHandlerReceiveBuffer(handler);
    unsetHandlerReceiveFunction(handler);
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
void UserGenericReceived(byte* recBuffPtr, byte len, byte handler) {
    WORD data;
    byte userGenericCounter = 0;
    switch (((GENERIC_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((GENERIC_DATA_PACKET*) sendBufferUsrGeneric)->_byte[0] = ((GENERIC_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((GENERIC_DATA_PACKET*) sendBufferUsrGeneric)->_byte[1] = GENERIC_MINOR_VERSION;
            ((GENERIC_DATA_PACKET*) sendBufferUsrGeneric)->_byte[2] = GENERIC_MAJOR_VERSION;
            userGenericCounter = 0x03;
            break;

        case GET_VALUE:
            ((GENERIC_DATA_PACKET*) sendBufferUsrGeneric)->_byte[0] = ((GENERIC_DATA_PACKET*) recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((GENERIC_DATA_PACKET*) sendBufferUsrGeneric)->_byte[1] = LSB(data);
            ((GENERIC_DATA_PACKET*) sendBufferUsrGeneric)->_byte[2] = MSB(data);
            userGenericCounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    USBGenWrite2(handler, userGenericCounter);

}/*end UserGenericReceived*/

/** EOF usr_generic.c ***************************************************************/
