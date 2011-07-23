/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre, Santiago Reyes                       30/11/10      Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "user\usr_debug.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user\handlerManager.h"
#include "dynamicPolling.h"                              


/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrdebugHandler;	 // Handler number asigned to the module
byte* sendBufferUsrdebug; // buffer to send data
byte largoMensajeDebug = 3;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserdebugProcessIO(void);
void UserdebugInit(byte i);
void UserdebugReceived(byte*, byte);
void UserdebugRelease(byte i);
void UserdebugConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab UserdebugModuleTable = {&UserdebugInit,&UserdebugRelease,&UserdebugConfigure,"debug"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/*funcion que se encarga de recibir el mensaje de debug y guardarlo en el buffer de salida para ser luego consumido por el pc*/
void sendDebug(char* mensaje, byte largo){
    byte counter = 1;	
    largoMensajeDebug = largo;
    for (counter=1 ; counter < largo + 1 ; counter++){
	    *(sendBufferUsrdebug+counter)= *(mensaje+counter); 
	}
	*(sendBufferUsrdebug+counter)=0x00;
}

/******************************************************************************
 * Function:        UserdebugInit(void)
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

void UserdebugInit(byte i){
	BOOL res;
	usrdebugHandler = i;
	// add my receive function to the handler module, to be called automatically when the pc sends data to the user module
	setHandlerReceiveFunction(usrdebugHandler,&UserdebugReceived);
	// add my receive pooling function to the dynamic pooling module, to be called periodically 
	res = addPollingFunction(&UserdebugProcessIO);
	// initialize the send buffer, used to send data to the PC
	sendBufferUsrdebug = getSharedBuffer(usrdebugHandler);
	//TODO return res value 
}//end UserdebugInit


/******************************************************************************
 * Function:        UserdebugConfigure(void)
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
void UserdebugConfigure(void){
// Do the configuration
}

/******************************************************************************
 * Function:        UserdebugProcessIO(void)
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

void UserdebugProcessIO(void){  

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
	// here enter the code that want to be called periodically, per example interaction with buttons and leds
	
}//end ProcessIO



/******************************************************************************
 * Function:        UserdebugRelease(byte i)
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

void UserdebugRelease(byte i){
	unsetHandlerReceiveBuffer(i);
	unsetHandlerReceiveFunction(i);
	removePoolingFunction(&UserdebugProcessIO);
}


/******************************************************************************
 * Function:        UserdebugReceived(byte* recBuffPtr, byte len)
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

void UserdebugReceived(byte* recBuffPtr, byte len){
	  byte index;
	  char mens[9] = "Debug";	
      byte UserdebugCounter = 0;

switch(((DEBUG_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
			  ((DEBUG_DATA_PACKET*)sendBufferUsrdebug)->_byte[0] = ((DEBUG_DATA_PACKET*)recBuffPtr)->_byte[0]; 
			  ((DEBUG_DATA_PACKET*)sendBufferUsrdebug)->_byte[1] = ((DEBUG_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              ((DEBUG_DATA_PACKET*)sendBufferUsrdebug)->_byte[2] = DEBUG_MINOR_VERSION;
              ((DEBUG_DATA_PACKET*)sendBufferUsrdebug)->_byte[3] = DEBUG_MAJOR_VERSION;
              UserdebugCounter = 0x04;
              break;  

        case RD_DEBUG:
			  ((DEBUG_DATA_PACKET*)sendBufferUsrdebug)->_byte[0] = ((DEBUG_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              UserdebugCounter = largoMensajeDebug + 1;
              break;  
		case MESSAGE:
		     sendDebug(mens, 6);
       		 break;
		 default:
              break;
      }//end switch(s)



      if(UserdebugCounter != 0)
      {
          if(!mUSBGenTxIsBusy())
              USBGenWrite2(usrdebugHandler, UserdebugCounter);
      }//end if  	  

	
}//end UserdebugReceived

/** EOF usr_debug.c ***************************************************************/

