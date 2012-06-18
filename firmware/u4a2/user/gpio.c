/* Author                                                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Santiago Reyes                           03/07/09    Original.
 *Andres Aguirre                           30/07/10    Interaccion con timmer y debugeo
 *****************************************************************************/
 
/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/gpio.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"   
#include "usb4all/proxys/T0Proxy.h"

  
/** V A R I A B L E S ********************************************************/
#pragma udata 


byte* sendBufferGpio; // buffer to send data
/** P R I V A T E  P R O T O T Y P E S ***************************************/
void GpioProcessIO(void);
void GpioInit(byte i);
void GpioReceived(byte*, byte, byte);
void GpioRelease(byte i);
void GpioConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab GpioModuleTable = {&GpioInit,&GpioRelease,&GpioConfigure,"gpio"}; //modName must be less or equal 8 characters
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

void GpioInit(byte i) {
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(i,&GpioReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically 
    /* andres res = addPollingFunction(&GpioProcessIO);*/
    // initialize the send buffer, used to send data to the PC
    sendBufferGpio = getSharedBuffer(i);
    
    
}//end UserLedAmarilloInit

/******************************************************************************
/* Function:        GpioConfigure(void)
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
void GpioConfigure(void){
// Do the configuration
}

void GpioProcessIO(void){

}//end ProcessIO

/******************************************************************************
 * Function:        GpioRelease(byte i)
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

void GpioRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i); 
}


/******************************************************************************
 * Function:        GpioReceived(byte* recBuffPtr, byte len)
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

void GpioReceived(byte* recBuffPtr, byte len, byte handler){
      byte j;  
      byte GpioCounter = 0;
      WORD aux;
      port_descriptor port;
      port = board_ports[0]; //it's harcode to port 1

      switch(((GPIO_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
              ((GPIO_DATA_PACKET*)sendBufferGpio)->_byte[0] = ((GPIO_DATA_PACKET*)recBuffPtr)->_byte[0];
              ((GPIO_DATA_PACKET*)sendBufferGpio)->_byte[1] = GPIO_MINOR_VERSION;
              ((GPIO_DATA_PACKET*)sendBufferGpio)->_byte[2] = GPIO_MAJOR_VERSION;
              GpioCounter = 0x03;
              break;  
              
        case GET_RES:
              ((GPIO_DATA_PACKET*)sendBufferGpio)->_byte[0] = ((GPIO_DATA_PACKET*)recBuffPtr)->_byte[0];
              aux = port.get_val_detection_pin();
              ((GPIO_DATA_PACKET*)sendBufferGpio)->_byte[1] = LSB(aux);
              ((GPIO_DATA_PACKET*)sendBufferGpio)->_byte[2] = MSB(aux);
              GpioCounter = 0x03;
              break;        
     
         default:
              break;
      }//end switch(s)
      if(GpioCounter != 0){
            j = 255;
            while(mUSBGenTxIsBusy() && j-->0); // pruebo un maximo de 255 veces
                if(!mUSBGenTxIsBusy())
                    USBGenWrite2(handler, GpioCounter);
      }//end if            
}//end GpioReceived

/** EOF gpio.c ***************************************************************/
