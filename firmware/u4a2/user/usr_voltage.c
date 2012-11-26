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
#include "user/usr_voltage.h"

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrVoltage; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserVoltageProcessIO(void);
void UserVoltageInit(byte i);
void UserVoltageReceived(byte*, byte, byte);
void UserVoltageRelease(byte i);
void UserVoltageConfigure(byte);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userVoltageModuleTable = {&UserVoltageInit,&UserVoltageRelease,&UserVoltageConfigure,"volt"}; /* modName must be less 8 characters */
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserVoltageInit(void)
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
void UserVoltageInit(byte usrVoltageHandler){
    /* add my receive function to the handler module, to be called automatically
     * when someone sends data to the user module */
    setHandlerReceiveFunction(usrVoltageHandler, &UserVoltageReceived);
    /* initialize the send buffer, used to send data */
    sendBufferUsrVoltage = getSharedBuffer(usrVoltageHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode
     * as an example, it is set to IN mode */
    getPortDescriptor(usrVoltageHandler)->change_port_direction(IN);
}/* end UserVoltageInit */

/******************************************************************************
 * Function:        UserVoltageConfigure(void)
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
void UserVoltageConfigure(byte handler){
    /* Do the configuration needed */
}/* end UserVoltageConfigure */

/******************************************************************************
 * Function:        UserVoltageProcessIO(void)
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
void UserVoltageProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    /* here enter the code that want to be called periodically,
     * per example interaction with buttons and leds */
}/* end UserVoltageProcessIO */

/******************************************************************************
 * Function:        UserVoltageRelease(byte i)
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
void UserVoltageRelease(byte usrVoltageHandler){
    unsetHandlerReceiveBuffer(usrVoltageHandler);
    unsetHandlerReceiveFunction(usrVoltageHandler);
}/* end UserVoltageRelease */

/******************************************************************************
 * Function:        UserVoltageReceived(byte* recBuffPtr, byte len)
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
void UserVoltageReceived(byte* recBuffPtr, byte len, byte handler){
    byte j;
    WORD data;
    byte userVoltageCounter = 0;
    switch(((VOLTAGE_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION:
            ((VOLTAGE_DATA_PACKET*)sendBufferUsrVoltage)->_byte[0] = ((VOLTAGE_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((VOLTAGE_DATA_PACKET*)sendBufferUsrVoltage)->_byte[1] = VOLTAGE_MINOR_VERSION;
            ((VOLTAGE_DATA_PACKET*)sendBufferUsrVoltage)->_byte[2] = VOLTAGE_MAJOR_VERSION;
            userVoltageCounter=0x03;   /* cant of bytes to be send */
            break;

        case GET_VALUE:
            ((VOLTAGE_DATA_PACKET*)sendBufferUsrVoltage)->_byte[0] = ((VOLTAGE_DATA_PACKET*)recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((VOLTAGE_DATA_PACKET*)sendBufferUsrVoltage)->_byte[1] = LSB(data);
            ((VOLTAGE_DATA_PACKET*)sendBufferUsrVoltage)->_byte[2] = MSB(data);
            userVoltageCounter=0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/* end switch(s)*/

    if(userVoltageCounter != 0)
    {
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); /* try at last 255 tries */
        if(!mUSBGenTxIsBusy())
            USBGenWrite2(handler, userVoltageCounter);
    }/* end if */
}/* end UserVoltageReceived */

/** EOF usr_voltage.c **************************************************/