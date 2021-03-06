/* Author                                                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * John, Aylen, Guille, Andrew
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/port.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
byte* sendBufferPort; // buffer to send data

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void PortInit(byte i);
void PortReceived(byte*, byte, byte);
void PortRelease(byte i);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab PortModuleTable = {&PortInit, &PortRelease, "port"};
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

void PortInit(byte i) {
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(i, &PortReceived);
    // initialize the send buffer, used to send data to the PC
    sendBufferPort = getSharedBuffer(i);
    //get port where sensor/actuator is connected and set to OUT mode
    getPortDescriptor(i)->change_port_direction(IN);
}//end PortInit


/******************************************************************************
 * Function:        PortRelease(byte i)
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

void PortRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}

/******************************************************************************
 * Function:        PortReceived(byte* recBuffPtr, byte len)
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

void PortReceived(byte* recBuffPtr, byte len, byte handler) {
    byte PortCounter = 0;

    switch (((PORT_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            //dataPacket._byte[1] is len
            ((PORT_DATA_PACKET*) sendBufferPort)->_byte[0] = ((PORT_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((PORT_DATA_PACKET*) sendBufferPort)->_byte[1] = PORT_MINOR_VERSION;
            ((PORT_DATA_PACKET*) sendBufferPort)->_byte[2] = PORT_MAJOR_VERSION;
            PortCounter = 0x03;
            break;

        case GET_RES:
            ((PORT_DATA_PACKET*) sendBufferPort)->_byte[0] = ((PORT_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((PORT_DATA_PACKET*) sendBufferPort)->_byte[1] = 255;
            PortCounter = 0x02;
            break;

        default:
            break;
    }//end switch(s)

    USBGenWrite2(handler, PortCounter);

}//end PortReceived

/** EOF port.c ***************************************************************/
