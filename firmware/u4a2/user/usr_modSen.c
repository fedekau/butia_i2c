/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alan Aguiar                                      04/09/123   Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_modSen.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "user/usb4butia.h"

/** V A R I A B L E S ********************************************************/
#pragma udata

byte* sendBufferUsrModSen; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserModSenInit(byte handler);
void UserModSenReceived(byte*, byte, byte);
void UserModSenRelease(byte handler);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userModSenATable = {&UserModSenInit, &UserModSenRelease, "modSenA"};
const uTab userModSenBTable = {&UserModSenInit, &UserModSenRelease, "modSenB"};
const uTab userModSenCTable = {&UserModSenInit, &UserModSenRelease, "modSenC"};
const uTab userGreyModuleTable = {&UserModSenInit, &UserModSenRelease, "grey"};
const uTab userLightModuleTable = {&UserModSenInit, &UserModSenRelease, "light"};
const uTab userResModuleTable = {&UserModSenInit, &UserModSenRelease, "res"};
const uTab userVoltModuleTable = {&UserModSenInit, &UserModSenRelease, "volt"};
const uTab userDistModuleTable = {&UserModSenInit, &UserModSenRelease, "distanc"};

#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserModSenInit(void)
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
void UserModSenInit(byte handler) {
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(handler, &UserModSenReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrModSen = getSharedBuffer(handler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(handler)->change_port_direction(IN);
}/*end UserModuleAInit*/


/******************************************************************************
 * Function:        UserModSenRelease(byte i)
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
void UserModSenRelease(byte handler) {
    unsetHandlerReceiveBuffer(handler);
    unsetHandlerReceiveFunction(handler);
}/*end UserModuleARelease*/

/******************************************************************************
 * Function:        UserModSenReceived(byte* recBuffPtr, byte len)
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
void UserModSenReceived(byte* recBuffPtr, byte len, byte handler) {
    WORD data;
    byte userModSenCounter = 0;
    switch (((MODSEN_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((MODSEN_DATA_PACKET*) sendBufferUsrModSen)->_byte[0] = ((MODSEN_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((MODSEN_DATA_PACKET*) sendBufferUsrModSen)->_byte[1] = MODSEN_MINOR_VERSION;
            ((MODSEN_DATA_PACKET*) sendBufferUsrModSen)->_byte[2] = MODSEN_MAJOR_VERSION;
            userModSenCounter = 0x03;
            break;

        case GET_VALUE:
            ((MODSEN_DATA_PACKET*) sendBufferUsrModSen)->_byte[0] = ((MODSEN_DATA_PACKET*) recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((MODSEN_DATA_PACKET*) sendBufferUsrModSen)->_byte[1] = LSB(data);
            ((MODSEN_DATA_PACKET*) sendBufferUsrModSen)->_byte[2] = MSB(data);
            userModSenCounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    USBGenWrite2(handler, userModSenCounter);

}/*end UserModSenReceived*/

/** EOF usr_ModSen.c ***************************************************************/
