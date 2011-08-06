/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Andres Aguirre, Santiago Reyes, Guillermo Reisch          29/07/11    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "user\usr_pnp.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user\handlerManager.h"
#include "dynamicPolling.h"                              
#define mInitIDAnalog() TRISEbits.TRISE2=1;ADCON0=0x1D;ADCON2=0x3C;
 
/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrPNPHandler;	 // Handler number asigned to the module
byte* sendBufferUsrPNP; // buffer to send data

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserPNPProcessIO(void);
void UserPNPInit(byte i);
void UserPNPReceived(byte*, byte);
void UserPNPRelease(byte i);
void UserPNPConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userPNPModuleTable = {&UserPNPInit,&UserPNPRelease,&UserPNPConfigure,"pnp"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UsePNPInit(void)
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

void UserPNPInit(byte i){
	BOOL res;
	usrPNPHandler = i;
	// add my receive function to the handler module, to be called automatically when the pc sends data to the user module
	setHandlerReceiveFunction(usrPNPHandler,&UserPNPReceived);
	// add my receive pooling function to the dynamic pooling module, to be called periodically 
	//res = addPollingFunction(&UserPNPProcessIO);
	// initialize the send buffer, used to send data to the PC
	sendBufferUsrPNP = getSharedBuffer(usrPNPHandler);
	//TODO return res value 
	mInitIDAnalog();
	ADCON2bits.ADFM = 1;   // ADC result right justified
    S0Init S1Init S2Init
}//end UserPNPInit

/******************************************************************************
/* Function:        UserPNPConfigure(void)
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
void UserPNPConfigure(void){
// Do the configuration
}

/******************************************************************************
 * Function:        UserPNPProcessIO(void)
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

void UserPNPProcessIO(void){  

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
	// here enter the code that want to be called periodically, per example interaction with buttons and leds
}//end ProcessIO



/******************************************************************************
 * Function:        UserPNPRelease(byte i)
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

void UserPNPRelease(byte i){
	unsetHandlerReceiveBuffer(i);
	unsetHandlerReceiveFunction(i);
	//removePoolingFunction(&UserPNPProcessIO);
}


/******************************************************************************
 * Function:        UserPNPReceived(byte* recBuffPtr, byte len)
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

void UserPNPReceived(byte* recBuffPtr, byte len){
      byte index;
      char mens[9] = "puerta";	
      byte port_id = 0;
      byte userPNPCounter = 0;
      switch(((PNP_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
              //dataPacket._byte[1] is len
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[0] = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[0]; 
	        ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[1] = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[1]; 
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[2] = PNP_MINOR_VERSION;
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[3] = PNP_MAJOR_VERSION;
            userPNPCounter = 0x04;
        break;  
	          
        case ASK_ID:
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[0] = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            port_id = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[1];	
            switch(port_id){
		        case 0:
                    S2=0;S1=0;S0=0;
                break;
                case 1:
                    S2=0;S1=0;S0=1;
                break;
                case 2:
                    S2=0;S1=1;S0=0;
                break;
                case 3:
                    S2=0;S1=1;S0=1;
                break;
                case 4:
                    S2=1;S1=0;S0=0;
                break;
                case 5:
                    S2=1;S1=0;S0=1;
                break;
                case 6:
                    S2=1;S1=1;S0=0;
                break;
                case 7:
                    S2=1;S1=1;S0=1;
                break;
            }           	
            ADCON0bits.GO = 1;              // Start AD conversion
            while(ADCON0bits.NOT_DONE);     // Wait for conversion
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[1] = ADRESH;
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[2] = ADRESL;
            userPNPCounter = 0x03;
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
      if(userPNPCounter != 0)
      {
          if(!mUSBGenTxIsBusy())
              USBGenWrite2(usrPNPHandler, userPNPCounter);
      }//end if  	  	
}//end UserPNPReceived

/** EOF usr_puerta.c ***************************************************************/
