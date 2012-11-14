/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * andrew
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "system/typedefs.h"
#include "user/usr_butia.h"
#include "user/handlerManager.h"
#include "dynamicPolling.h"                              
#include "ax12.h"
#include "usr_motors.h"

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferusrButia; // buffer to send data

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserButiaProcessIO(void);
void UserButiaInit(byte i);
void UserButiaReceived(byte*, byte, byte);
void UserButiaRelease(byte i);
void UserButiaConfigure(byte);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab UserButiaModuleTable = {&UserButiaInit,&UserButiaRelease,&UserButiaConfigure,"butia"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserButiaInit(void)
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
 *					when the module is opened	
 *
 * Note:            None
 *****************************************************************************/

void UserButiaInit(byte usrButiaHandler){
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrButiaHandler,&UserButiaReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically
    // res = addPollingFunction(&UserButiaProcessIO);
    // initialize the send buffer, used to send data to the PC
    sendBufferusrButia = getSharedBuffer(usrButiaHandler);
    //TODO return res value
}//end UserButiaInit

/******************************************************************************
 * Function:        UserButiaConfigure(void)
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
void UserButiaConfigure(byte handler){
// Do the configuration
}

/******************************************************************************
 * Function:        UserButiaProcessIO(void)
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

void UserButiaProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
	// here enter the code that want to be called periodically, per example interaction with buttons and leds
	
}//end ProcessIO



/******************************************************************************
 * Function:        UserButiaRelease(byte i)
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

void UserButiaRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}


/******************************************************************************
 * Function:        UserButiaReceived(byte* recBuffPtr, byte len)
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

void UserButiaReceived(byte* recBuffPtr, byte len, byte handler){
    byte i, j;
    byte UserButiaCounter = 0;
    int data_received = 3;

    switch(((BUTIA_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION_BUTIA:
            ((BUTIA_DATA_PACKET*)sendBufferusrButia)->_byte[0] = ((BUTIA_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((BUTIA_DATA_PACKET*)sendBufferusrButia)->_byte[1] = BUTIA_VERSION;
            UserButiaCounter=0x02;
        break;
        case GET_VOLT:
            ((BUTIA_DATA_PACKET*)sendBufferusrButia)->_byte[0] = ((BUTIA_DATA_PACKET*)recBuffPtr)->_byte[0];
            getVoltage(&data_received);     //controlar error
            ((BUTIA_DATA_PACKET*)sendBufferusrButia)->_byte[1] = data_received;
            UserButiaCounter=0x02;
        break;
        case RESET:
            Reset();
        break;

        default:
        break;
    }/*end switch(s)*/
    if(UserButiaCounter != 0){
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); // pruebo un maximo de 255 veces
            if(!mUSBGenTxIsBusy())
                USBGenWrite2(handler, UserButiaCounter);
    }/*end if*/

}/*end UserButiaReceived*/

/** EOF usr_butia.c ***************************************************************/
