/* Author                                                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Santiago Reyes                           03/07/09    Original.
 *Andres Aguirre                           30/07/10    Interaccion con timmer y debugeo
 *****************************************************************************/
 
/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "user\usr_buzzer.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user\handlerManager.h"
#include "dynamicPolling.h"   
#include "usb4all\proxys\T0Service.h"                           

  
/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrBuzzerHandler;     // Handler number asigned to the module
byte* sendBufferUsrBuzzer; // buffer to send data
byte  buzzerState;
byte  timeOutTicksBuzz;
byte  cantTicks1  = 30;
byte  cantTicks2  = 60;
byte  cantTicks3  = 120;
byte  needRegister = 1;

#define FIRST_ON    0x01
#define DELAY       0x02
#define SECOND_ON   0x03
#define END         0x04

#define TIME_UNIT   2000

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserBuzzerProcessIO(void);
void UserBuzzerInit(byte i);
void UserBuzzerReceived(byte*, byte);
void UserBuzzerRelease(byte i);
void UserBuzzerConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userBuzzerModuleTable = {&UserBuzzerInit,&UserBuzzerRelease,&UserBuzzerConfigure,"buzzer"}; //modName must be less or equal 8 characters
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

void UserBuzzerInit(byte i) {
    BOOL res;
    usrBuzzerHandler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrBuzzerHandler,&UserBuzzerReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically 
    /* andres res = addPollingFunction(&UserBuzzerProcessIO);*/
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrBuzzer = getSharedBuffer(usrBuzzerHandler);
    //TODO return res value 
    //initT0Service();
    // se inicializa en el main mInitBuzzer(); /*Inicializo el puerto del buzzer*/
}//end UserLedAmarilloInit

/******************************************************************************
/* Function:        UserBuzzerConfigure(void)
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
void UserBuzzerConfigure(void){
// Do the configuration
}
/***********************************************************************
*
* Callback function to execute periodicaly by te Timmer interrupt ISR
*
************************************************************************/
void buzzEvent(void) {    
    needRegister = 1;
    timeOutTicksBuzz --;
    switch(buzzerState){
        case FIRST_ON:
            if(timeOutTicksBuzz <= 0){
                buzzerState = DELAY;
                timeOutTicksBuzz = cantTicks2;
                buzzer_off();
                needRegister = 1;
            }
        break;  
        case DELAY:
            if(timeOutTicksBuzz <= 0){
                buzzerState = SECOND_ON;
                timeOutTicksBuzz = cantTicks3;
                buzzer_on();
                needRegister = 1;
            }
        break;
        case SECOND_ON:
            if(timeOutTicksBuzz <= 0){
                buzzerState = END;
                buzzer_off();
                needRegister = 0;
            }
	break; //FIXME agregado
        case END:
	     needRegister = 0; 	
             //No hago nada
        break;
     }
     if(needRegister == 1){ 
        registerT0eventInEvent(TIME_UNIT, &buzzEvent);
     }
     ///mLED_2_Toggle(); debug	
}

/***********************************************************************
*
* Register buzzEvent for double beep
*
************************************************************************/
void boubleBeep(byte t1, byte t2, byte t3) {  
    unregisterT0event(&buzzEvent);
    timeOutTicksBuzz = t1;
    cantTicks2       = t2;
    cantTicks3       = t3;
    buzzerState      = FIRST_ON;
    buzzer_on();
    registerT0event(TIME_UNIT, &buzzEvent);
}

/******************************************************************************
 * Function:        UserBuzzerProcessIO(void)
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

void UserBuzzerProcessIO(void){  

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    if(needRegister == 0){
        unregisterT0event(&buzzEvent);
        needRegister = 1;
    }
}//end ProcessIO

/******************************************************************************
 * Function:        UserBuzzerRelease(byte i)
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

void UserBuzzerRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    unregisterT0event(&buzzEvent);
    removePoolingFunction(&UserBuzzerProcessIO);
}


/******************************************************************************
 * Function:        UserBuzzerReceived(byte* recBuffPtr, byte len)
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

void UserBuzzerReceived(byte* recBuffPtr, byte len){
      byte index;
      byte j;  
      byte userBuzzerCounter = 0;
      byte tiempo;

      switch(((BUZZER_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
              //dataPacket._byte[1] is len
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[0] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[1] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[2] = BUZZER_MINOR_VERSION;
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[3] = BUZZER_MAJOR_VERSION;
              userBuzzerCounter = 0x04;
              break;  
              
        case PRENDER:
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[0] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[1] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              buzzer_on();
              userBuzzerCounter = 0x02;
              break;  
        
        case APAGAR:
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[0] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[1] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              buzzer_off(); 
              userBuzzerCounter = 0x02;
              break;  

        case BUZZER_TRIPLE:
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[0] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[1] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              cantTicks1 = (byte)(((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[1]);
              cantTicks2 = (byte)(((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[2]);  
              cantTicks3 = (byte)(((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[3]);
              boubleBeep(cantTicks1, cantTicks2, cantTicks3);
              userBuzzerCounter = 0x02;
              break;        

        case BUZZER_CORTO:
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[0] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              ((BUZZER_DATA_PACKET*)sendBufferUsrBuzzer)->_byte[1] = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              cantTicks3 = ((BUZZER_DATA_PACKET*)recBuffPtr)->_byte[1];
              timeOutTicksBuzz = 1; // lo seteo timmer para que venza inmediantamente
              buzzerState = DELAY;  
              registerT0event(0, &buzzEvent);
              userBuzzerCounter = 0x02;
              break;    

        case RESET:
              Reset();
              break;
     
         default:
              break;
      }//end switch(s)
      if(userBuzzerCounter != 0){
            j = 255;
            while(mUSBGenTxIsBusy() && j-->0); // pruebo un máximo de 255 veces
                if(!mUSBGenTxIsBusy())
                    USBGenWrite2(usrBuzzerHandler, userBuzzerCounter);
      }//end if            
}//end UserBuzzerReceived

/** EOF usr_Buzzer.c ***************************************************************/
