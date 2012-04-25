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
#include "user/test_resistance.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"   
#include "usb4all/proxys/T0Proxy.h"

  
/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrTestResHandler;     // Handler number asigned to the module
byte* sendBufferUsrTestRes; // buffer to send data
/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserTestResProcessIO(void);
void UserTestResInit(byte i);
void UserTestResReceived(byte*, byte, byte);
void UserTestResRelease(byte i);
void UserTestResConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userTestResModuleTable = {&UserTestResInit,&UserTestResRelease,&UserTestResConfigure,"testres"}; //modName must be less or equal 8 characters
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

void UserTestResInit(byte i) {
    BOOL res;
    usrTestResHandler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrTestResHandler,&UserTestResReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically 
    /* andres res = addPollingFunction(&UserTestResProcessIO);*/
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrTestRes = getSharedBuffer(usrTestResHandler);
    //TODO return res value 
    //initT0Service();
    // se inicializa en el main mInitTestRes(); /*Inicializo el puerto del TestRes*/

    /*Confiugures things for read anaogic*/
    ADCON1bits.VCFG = 0; /*Voltage reference higth 5v = Vss and low 0v = Vdd*/
    ADCON1bits.PCFG = 0x00;

    /*ADCON register configuration*/
    ADCON2bits.ADFM = 0x00; /*Left justified*/
    ADCON2bits.ACQT = 0x07; /*Acquisition Time Select*/
    ADCON2bits.ADCS = 0x04; /*Acquisition Time Select Fosc/4*/

}//end UserLedAmarilloInit

/******************************************************************************
/* Function:        UserTestResConfigure(void)
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
void UserTestResConfigure(void){
// Do the configuration
}

void UserTestResProcessIO(void){

}//end ProcessIO

/******************************************************************************
 * Function:        UserTestResRelease(byte i)
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

void UserTestResRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i); 
    removePoolingFunction(&UserTestResProcessIO);
}


/******************************************************************************
 * Function:        UserTestResReceived(byte* recBuffPtr, byte len)
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

void UserTestResReceived(byte* recBuffPtr, byte len, byte handler){
      byte index;
      byte j;  
      byte userTestResCounter = 0;
      byte tiempo;
      WORD aux;
      port_descriptor port;
      port = board_ports[0]; //it's harcode to port 1

      switch(((TEST_RESISTANCE_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
              //dataPacket._byte[1] is len
              ((TEST_RESISTANCE_DATA_PACKET*)sendBufferUsrTestRes)->_byte[0] = ((TEST_RESISTANCE_DATA_PACKET*)recBuffPtr)->_byte[0];
              ((TEST_RESISTANCE_DATA_PACKET*)sendBufferUsrTestRes)->_byte[1] = ((TEST_RESISTANCE_DATA_PACKET*)recBuffPtr)->_byte[1];
              ((TEST_RESISTANCE_DATA_PACKET*)sendBufferUsrTestRes)->_byte[2] = TEST_RESISTANCE_MINOR_VERSION;
              ((TEST_RESISTANCE_DATA_PACKET*)sendBufferUsrTestRes)->_byte[3] = TEST_RESISTANCE_MAJOR_VERSION;
              userTestResCounter = 0x04;
              break;  
              
        case GET_RES:
              ((TEST_RESISTANCE_DATA_PACKET*)sendBufferUsrTestRes)->_byte[0] = ((TEST_RESISTANCE_DATA_PACKET*)recBuffPtr)->_byte[0];
              aux = port.get_val_detection_pin();
              ((TEST_RESISTANCE_DATA_PACKET*)sendBufferUsrTestRes)->_byte[1] = LSB(aux);
              ((TEST_RESISTANCE_DATA_PACKET*)sendBufferUsrTestRes)->_byte[2] = MSB(aux);

              userTestResCounter = 0x03;
              break;       
        
     
         default:
              break;
      }//end switch(s)
      if(userTestResCounter != 0){
            j = 255;
            while(mUSBGenTxIsBusy() && j-->0); // pruebo un máximo de 255 veces
                if(!mUSBGenTxIsBusy())
                    USBGenWrite2(usrTestResHandler, userTestResCounter);
      }//end if            
}//end UserTestResReceived

/** EOF usr_TestRes.c ***************************************************************/
