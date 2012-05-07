/* Author                                                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *****************************************************************************/
 
/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_ax12.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"   
#include "usb4all/proxys/T0Service.h"

  
/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrAX12Handler;     // Handler number asigned to the module
byte* sendBufferUsrAX12; // buffer to send data

#define FIRST_ON    0x01
#define DELAY       0x02
#define SECOND_ON   0x03
#define END         0x04

#define TIME_UNIT   2000

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserAX12ProcessIO(void);
void UserAX12Init(byte i);
void UserAX12Received(byte*, byte);
void UserAX12Release(byte i);
void UserAX12Configure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userAX12ModuleTable = {&UserAX12Init,&UserAX12Release,&UserAX12Configure,"ax"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UseBuzzerInit(void)
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

void UserAX12Init(byte i) {
    BOOL res;
    byte resWriteInfo;
    usrAX12Handler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrAX12Handler,&UserAX12Received);
    // add my receive pooling function to the dynamic pooling module, to be called periodically 
    /* andres res = addPollingFunction(&UserAX12ProcessIO);*/
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrAX12 = getSharedBuffer(usrAX12Handler);
    init_serial(); /*serial configuration for ax12*/
    resWriteInfo = writeInfo(BRODCAST, LED, 1);
   
}

/******************************************************************************
/* Function:        UserAX12Configure(void)
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
void UserAX12Configure(void){
// Do the configuration
}

/******************************************************************************
 * Function:        UserAX12ProcessIO(void)
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
 *                    int the PIC, also it can comunicate things to the pc by the USB    
 *
 * Note:            None
 *****************************************************************************/

void UserAX12ProcessIO(void){  

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
}//end ProcessIO

/******************************************************************************
 * Function:        UserAX12Release(byte i)
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

void UserAX12Release(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    //unregisterT0event(&ax12Event);
    removePoolingFunction(&UserAX12ProcessIO);
}


/******************************************************************************
 * Function:        UserAX12Received(byte* recBuffPtr, byte len)
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

void UserAX12Received(byte* recBuffPtr, byte len){
      byte index;
      byte j;  
      byte userAX12Counter = 0;
      byte id, regstart, resWriteInfo, valueH, valueL, sentidoIzq, velIzq, sentidoDer, velDer;
      int value;
      switch(((AX12_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
              ((AX12_DATA_PACKET*)sendBufferUsrAX12)->_byte[0] = ((AX12_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              ((AX12_DATA_PACKET*)sendBufferUsrAX12)->_byte[1] = ((AX12_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              ((AX12_DATA_PACKET*)sendBufferUsrAX12)->_byte[2] = AX12_MINOR_VERSION;
              ((AX12_DATA_PACKET*)sendBufferUsrAX12)->_byte[3] = AX12_MAJOR_VERSION;
              userAX12Counter = 0x04;
              break;  
        //byte writeInfo (byte id,byte regstart, int value) {
        case WRITE_INFO:
              ((AX12_DATA_PACKET*)sendBufferUsrAX12)->_byte[0] = ((AX12_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              id       = (byte)(((AX12_DATA_PACKET*)recBuffPtr)->_byte[1]);
              regstart = (byte)(((AX12_DATA_PACKET*)recBuffPtr)->_byte[2]);  
              valueH   = (byte)(((AX12_DATA_PACKET*)recBuffPtr)->_byte[3]);
              valueL   = (byte)(((AX12_DATA_PACKET*)recBuffPtr)->_byte[4]);
              value    = valueH; 
              value    = ((value << 8) | valueL);
              resWriteInfo = writeInfo(id, regstart, value);
              //resWriteInfo = writeInfo(0xFE, 0x19, 0x01);
              ((AX12_DATA_PACKET*)sendBufferUsrAX12)->_byte[1] = resWriteInfo; 
              userAX12Counter = 0x02;
              break;    
        case RESET:
              Reset();
              break;
     
         default:
              break;
      }//end switch(s)
      if(userAX12Counter != 0){
            j = 255;
            while(mUSBGenTxIsBusy() && j-->0); // pruebo un máximo de 255 veces
                if(!mUSBGenTxIsBusy())
                    USBGenWrite2(usrAX12Handler, userAX12Counter);
      }//end if            
}//end UserAX12Received

/** EOF usr_Buzzer.c ***************************************************************/
