/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alan Aguiar                                      04/09/123   Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_modAct.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "user/usb4butia.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
byte* sendBufferUsrModAct; /* buffer to send data*/

#define ACT_ON    (byte) 1
#define ACT_OFF   (byte) 0

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserModActInit(byte handler);
void UserModActReceived(byte*, byte, byte);
void UserModActRelease(byte handler);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userModActATable = {&UserModActInit, &UserModActRelease, "modActA"};
const uTab userModActBTable = {&UserModActInit, &UserModActRelease, "modActB"};
const uTab userModActCTable = {&UserModActInit, &UserModActRelease, "modActC"};
const uTab userRelayModTable = {&UserModActInit, &UserModActRelease, "relay"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserModActInit(void)
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
void UserModActInit(byte handler) {
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(handler, &UserModActReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrModAct = getSharedBuffer(handler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(handler)->change_port_direction(OUT);
}/*end UserModActInit*/


/******************************************************************************
 * Function:        UserModActRelease(byte i)
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
void UserModActRelease(byte handler) {
    getPortDescriptor(handler)->set_data(ACT_OFF);
    getPortDescriptor(handler)->change_port_direction(IN);
    unsetHandlerReceiveBuffer(handler);
    unsetHandlerReceiveFunction(handler);
}/*end UserModActRelease*/

/******************************************************************************
 * Function:        UserModActReceived(byte* recBuffPtr, byte len)
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
void UserModActReceived(byte* recBuffPtr, byte len, byte handler) {
    byte userModActCounter = 0;
    switch (((MODACT_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((MODACT_DATA_PACKET*) sendBufferUsrModAct)->_byte[0] = ((MODACT_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((MODACT_DATA_PACKET*) sendBufferUsrModAct)->_byte[1] = MODACT_MINOR_VERSION;
            ((MODACT_DATA_PACKET*) sendBufferUsrModAct)->_byte[2] = MODACT_MAJOR_VERSION;
            userModActCounter = 0x03;
            break;

        case TURN:
            ((MODACT_DATA_PACKET*) sendBufferUsrModAct)->_byte[0] = ((MODACT_DATA_PACKET*) recBuffPtr)->_byte[0];
            if (((MODACT_DATA_PACKET*)recBuffPtr)->_byte[1] == ACT_ON) {
                getPortDescriptor(handler)->set_data(ACT_ON);
            } else {
                getPortDescriptor(handler)->set_data(ACT_OFF);
            }
            userModActCounter = 0x01;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    USBGenWrite2(handler, userModActCounter);

}/*end UserModActReceived*/

/** EOF usr_modAct.c ***************************************************************/
