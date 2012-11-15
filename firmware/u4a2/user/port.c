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
#include "dynamicPolling.h"   
#include "usb4all/proxys/T0Proxy.h"


/** V A R I A B L E S ********************************************************/
#pragma udata 


byte* sendBufferPort; // buffer to send data
/** P R I V A T E  P R O T O T Y P E S ***************************************/
void PortProcessIO(void);
void PortInit(byte i);
void PortReceived(byte*, byte, byte);
void PortRelease(byte i);
void PortConfigure(byte);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab PortModuleTable = {&PortInit, &PortRelease, &PortConfigure, "port"}; //modName must be less or equal 8 characters
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
    // add my receive pooling function to the dynamic pooling module, to be called periodically 
    /* andres res = addPollingFunction(&PortProcessIO);*/
    // initialize the send buffer, used to send data to the PC
    sendBufferPort = getSharedBuffer(i);
    board_ports[i - 1].change_port_direction(IN);

}//end UserLedAmarilloInit

/******************************************************************************
/* Function:        PortConfigure(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the specific configuration for the user module, it is called by the framework 
 *                        
 *
 * Note:            None
 *****************************************************************************/
void PortConfigure(byte handler) {
    // Do the configuration
}

void PortProcessIO(void) {

}//end ProcessIO

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
    byte j;
    byte PortCounter = 0;
    WORD aux;
    port_descriptor port;
    port = board_ports[0]; //it's harcode to port 1

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
            aux = port.get_val_detection_pin();
            ((PORT_DATA_PACKET*) sendBufferPort)->_byte[1] = LSB(aux);
            ((PORT_DATA_PACKET*) sendBufferPort)->_byte[2] = MSB(aux);
            PortCounter = 0x03;
            break;

        default:
            break;
    }//end switch(s)
    if (PortCounter != 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > 0); // pruebo un máximo de 255 veces
        if (!mUSBGenTxIsBusy())
            USBGenWrite2(handler, PortCounter);
    }//end if
}//end PortReceived

/** EOF port.c ***************************************************************/
