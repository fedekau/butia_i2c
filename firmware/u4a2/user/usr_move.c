/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre
 *****************************************************************************/
 
/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_move.h"
//#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"   
                          
  
/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrMoveHandler;	 // Handler number asigned to the module
byte* sendBufferUsrMove; // buffer to send data


/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserMoveProcessIO(void);
void UserMoveInit(byte i);
void UserMoveReceived(byte*, byte);
void UserMoveRelease(byte i);
void UserMoveConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab UserMoveModuleTable = {&UserMoveInit,&UserMoveRelease,&UserMoveConfigure,"move"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserMoveInit(void)
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

void UserMoveInit(byte i){
	BOOL res;
	usrMoveHandler = i;
	// add my receive function to the handler module, to be called automatically when the pc sends data to the user module
	setHandlerReceiveFunction(usrMoveHandler,&UserMoveReceived);
	// add my receive pooling function to the dynamic pooling module, to be called periodically 
	// res = addPollingFunction(&UserMoveProcessIO);
	// initialize the send buffer, used to send data to the PC
	sendBufferUsrMove = getSharedBuffer(usrMoveHandler);
//    mInitMoveSensor();
//     mInitPortD();
//     TRISDbits.TRISD7=1;
}//end UserLedAmarilloInit

/******************************************************************************
/* Function:        UserMoveConfigure(void)
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
void UserMoveConfigure(void){
// Do the configuration
}


/******************************************************************************
 * Function:        UserMoveProcessIO(void)
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

void UserMoveProcessIO(void){  

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;

}//end ProcessIO

/******************************************************************************
 * Function:        UserMoveRelease(byte i)
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

void UserMoveRelease(byte i){
	unsetHandlerReceiveBuffer(i);
	unsetHandlerReceiveFunction(i);
    //removePoolingFunction(&UserMoveProcessIO);
}


/******************************************************************************
 * Function:        UserMoveReceived(byte* recBuffPtr, byte len)
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

void UserMoveReceived(byte* recBuffPtr, byte len){
	  byte index, moveSensorValue;
	  char mens[9] = "MOVE";	
      byte UserMoveCounter = 0;
      switch(((MOVE_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
			  ((MOVE_DATA_PACKET*)sendBufferUsrMove)->_byte[0] = ((MOVE_DATA_PACKET*)recBuffPtr)->_byte[0]; 
			  ((MOVE_DATA_PACKET*)sendBufferUsrMove)->_byte[1] = ((MOVE_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              ((MOVE_DATA_PACKET*)sendBufferUsrMove)->_byte[2] = MOVE_MINOR_VERSION;
              ((MOVE_DATA_PACKET*)sendBufferUsrMove)->_byte[3] = MOVE_MAJOR_VERSION;
              UserMoveCounter = 0x04;
              break;  

        case GET_MOVE:
              moveSensorValue = 0x00;
              moveSensorValue = PORTDbits.RD7;
              //moveSensorValue = MOVE_SENSOR;
			  ((MOVE_DATA_PACKET*)sendBufferUsrMove)->_byte[0] = ((MOVE_DATA_PACKET*)recBuffPtr)->_byte[0]; 
			  ((MOVE_DATA_PACKET*)sendBufferUsrMove)->_byte[1] = moveSensorValue;
              UserMoveCounter = 0x02;
              break;  

        case RESET:
              Reset();
			  break;
		  
		 case MESS:
				sendMes(mens, sizeof(mens));
              break;
         
		 default:
              break;
      }//end switch(s)
      if(UserMoveCounter != 0)
      {
          if(!mUSBGenTxIsBusy())
              USBGenWrite2(usrMoveHandler, UserMoveCounter);
      }//end if  	  	
}//end UserMoveReceived

/** EOF usr_Buzzer.c ***************************************************************/
