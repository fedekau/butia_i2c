/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca                                      12/10/12    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "io_cfg.h"
#include "dynamicPolling.h"
#include "user/usb4butia.h"
#include "user/handlerManager.h"
#include "user/usr_resistance.h"

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrResistance; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserResistanceProcessIO(void);
void UserResistanceInit(byte i);
void UserResistanceReceived(byte*, byte, byte);
void UserResistanceRelease(byte i);
void UserResistanceConfigure(byte);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userResistanceModuleTable = {&UserResistanceInit,&UserResistanceRelease,&UserResistanceConfigure,"res"}; /* modName must be less 8 characters */
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserResistanceInit(void)
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
void UserResistanceInit(byte usrResistanceHandler){
    /* add my receive function to the handler module, to be called automatically
     * when someone sends data to the user module */
    setHandlerReceiveFunction(usrResistanceHandler, &UserResistanceReceived);
    /* initialize the send buffer, used to send data */
    sendBufferUsrResistance = getSharedBuffer(usrResistanceHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode
     * as an example, it is set to IN mode */
    getPortDescriptor(usrResistanceHandler)->change_port_direction(IN);
}/* end UserResistanceInit */

/******************************************************************************
 * Function:        UserResistanceConfigure(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the specific configuration for the user
 *                  module, it is called by the framework.
 *
 * Note:            None
 *****************************************************************************/
void UserResistanceConfigure(byte handler){
    /* Do the configuration needed */
}/* end UserResistanceConfigure */

/******************************************************************************
 * Function:        UserResistanceProcessIO(void)
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
void UserResistanceProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    /* here enter the code that want to be called periodically,
     * per example interaction with buttons and leds */
}/* end UserResistanceProcessIO */

/******************************************************************************
 * Function:        UserResistanceRelease(byte i)
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
void UserResistanceRelease(byte usrResistanceHandler){
    unsetHandlerReceiveBuffer(usrResistanceHandler);
    unsetHandlerReceiveFunction(usrResistanceHandler);
}/* end UserResistanceRelease */

/******************************************************************************
 * Function:        UserResistanceReceived(byte* recBuffPtr, byte len)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function manages the comunication with the other part
 *
 * Note:            None
 *****************************************************************************/
void UserResistanceReceived(byte* recBuffPtr, byte len, byte handler){
    byte j;
    WORD data;
    byte userResistanceCounter = 0;
    switch(((RESISTANCE_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION:
            ((RESISTANCE_DATA_PACKET*)sendBufferUsrResistance)->_byte[0] = ((RESISTANCE_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((RESISTANCE_DATA_PACKET*)sendBufferUsrResistance)->_byte[1] = RESISTANCE_MINOR_VERSION;
            ((RESISTANCE_DATA_PACKET*)sendBufferUsrResistance)->_byte[2] = RESISTANCE_MAJOR_VERSION;
            userResistanceCounter=0x03;   /* cant of bytes to be send */
            break;

        case GET_VALUE:
            ((RESISTANCE_DATA_PACKET*)sendBufferUsrResistance)->_byte[0] = ((RESISTANCE_DATA_PACKET*)recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((RESISTANCE_DATA_PACKET*)sendBufferUsrResistance)->_byte[1] = LSB(data);
            ((RESISTANCE_DATA_PACKET*)sendBufferUsrResistance)->_byte[2] = MSB(data);
            userResistanceCounter=0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/* end switch(s)*/

    if(userResistanceCounter != 0)
    {
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); /* try at last 255 tries */
        if(!mUSBGenTxIsBusy())
            USBGenWrite2(handler, userResistanceCounter);
    }/* end if */
}/* end UserResistanceReceived */

/** EOF usr_resistance.c **************************************************/
