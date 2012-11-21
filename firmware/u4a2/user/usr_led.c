/* Author                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca              24/04/2012  Original.
 * John Pereira
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_led.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"

#define LED_ON 1
#define LED_OFF 0

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrLed; /* buffer to send data */

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserLedProcessIO(byte);
void UserLedInit(byte i);
void UserLedReceived(byte*, byte, byte);
void UserLedRelease(byte i);
void UserLedConfigure(byte);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userLedModuleTable = {&UserLedInit,&UserLedRelease,&UserLedConfigure,"led"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserLedInit(byte)
 *
 * PreCondition:    None
 *
 * Input:           handler
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initialices the resources that the user module needs to work,
 *                   it is called by the framework when the module is opened
 *
 * Note:            None
 *****************************************************************************/

void UserLedInit(byte usrLedHandler){
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(usrLedHandler,&UserLedReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrLed = getSharedBuffer(usrLedHandler);
    /* get port where sensor/actuator is connected and set to OUT mode*/
    //getPortDescriptor(usrLedHandler)->change_port_direction(OUT);
}/*end UserLedInit*/

/******************************************************************************
 * Function:        UserLedConfigure(void)
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
void UserLedConfigure(byte i){
    /*no configuration for led module*/
}

/******************************************************************************
 * Function:        UserLedProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is registered in the dinamic polling, who call ir periodically to process the IO interaction
 *					int the PIC, also it can comunicate things to the pc by the USB	
 *
 * Note:            None
 *****************************************************************************/

void UserLedProcessIO(byte i){

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
	/* here enter the code that want to be called periodically,
         * per example interaction with buttons and leds */
}/*end UserLedProcessIO*/

/******************************************************************************
 * Function:        UserLedRelease(byte i)
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
 *					when the module is close	
 *
 * Note:            None
 *****************************************************************************/

void UserLedRelease(byte i){
    getPortDescriptor(i)->set_data(LED_OFF);
    getPortDescriptor(i)->change_port_direction(IN);
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);    
}

/******************************************************************************
 * Function:        UserLedReceived(byte* recBuffPtr, byte len)
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

void UserLedReceived(byte* recBuffPtr, byte len, byte handler){
    byte j;	
    byte userLedCounter = 0;
    switch(((LED_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION:
            ((LED_DATA_PACKET*)sendBufferUsrLed)->_byte[0] = ((LED_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            ((LED_DATA_PACKET*)sendBufferUsrLed)->_byte[1] = LED_MINOR_VERSION;
            ((LED_DATA_PACKET*)sendBufferUsrLed)->_byte[2] = LED_MAJOR_VERSION;
            userLedCounter=0x04;
            break;

        case SET_LED_ON:            
            ((LED_DATA_PACKET*)sendBufferUsrLed)->_byte[0] = ((LED_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((LED_DATA_PACKET*)sendBufferUsrLed)->_byte[1] = LED_ON;
            getPortDescriptor(handler)->set_data(LED_ON);
            getPortDescriptor(handler)->change_port_direction(OUT);
            userLedCounter=0x02;
            break;

        case SET_LED_OFF:
            changeDirectionPort1(0);
            ((LED_DATA_PACKET*)sendBufferUsrLed)->_byte[0] = ((LED_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((LED_DATA_PACKET*)sendBufferUsrLed)->_byte[1] = LED_OFF;
            getPortDescriptor(handler)->set_data(LED_OFF);
            getPortDescriptor(handler)->change_port_direction(IN);
            userLedCounter=0x02;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
      }/*end switch(s)*/
      if(userLedCounter != 0)
      {
       j = 255;
       while(mUSBGenTxIsBusy() && j-->0); /* pruebo un máximo de 255 veces*/
       if(!mUSBGenTxIsBusy())
              USBGenWrite2(handler, userLedCounter);
      }/*end if*/

}/*end UserLedReceived*/

/** EOF usr_led.c ***************************************************************/