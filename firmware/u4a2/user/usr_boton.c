/* Author ayle			  Date 10/03/2012       Comment
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_boton.h"
#include "io_cfg.h"              /* I/O pin mapping */
#include "user/handlerManager.h"
#include "dynamicPolling.h"                              
#include "user/usb4butia.h"

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrBotonHandler;	 /* Handler number asigned to the module*/
byte* sendBufferUsrBoton; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserBotonProcessIO(void);
void UserBotonInit(byte i);
void UserBotonReceived(byte*, byte);
void UserBotonRelease(byte i);
void UserBotonConfigure(void);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userBotonModuleTable = {&UserBotonInit,&UserBotonRelease,&UserBotonConfigure,"boton"}; /*modName must be less or equal 8 characters*/
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserBotonInit(byte)
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

void UserBotonInit(byte i){
    port_descriptor port = board_ports[i];
    BOOL res;
    int j = 0;
    usrBotonHandler = i;
    /* add my receive function to the handler module, to be called automatically when the pc sends data to the user module*/
    setHandlerReceiveFunction(usrBotonHandler,&UserBotonReceived);
    /* initialize the send buffer, used to send data to the PC*/
    sendBufferUsrBoton = getSharedBuffer(usrBotonHandler);
    port.change_port_direction(IN);
}/*end UserBotonInit*/

/******************************************************************************
 * Function:        UserBotonConfigure(void)
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

void UserBotonConfigure(void){
    /*no configuration for boton module*/
}

/******************************************************************************
 * Function:        UserBotonProcessIO(void)
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

void UserBotonProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    /* here enter the code that want to be called periodically, per example interaction with botons and leds*/
	
}/*end ProcessIO*/

/******************************************************************************
 * Function:        UserBotonRelease(byte i)
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

void UserBotonRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}

/******************************************************************************
 * Function:        UserBotonReceived(byte* recBuffPtr, byte len)
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

void UserBotonReceived(byte* recBuffPtr, byte len, port_descriptor port){
    byte index;
    byte j;
    byte userBotonCounter = 0;
    byte boton_status = 0;
    switch(((BOTON_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION:
            ((BOTON_DATA_PACKET*)sendBufferUsrBoton)->_byte[0] = ((BOTON_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((BOTON_DATA_PACKET*)sendBufferUsrBoton)->_byte[1] = BOTON_MINOR_VERSION;
            ((BOTON_DATA_PACKET*)sendBufferUsrBoton)->_byte[2] = BOTON_MAJOR_VERSION;
            userBotonCounter=0x03;
            break;

        case GET_PRESSED:
            ((BOTON_DATA_PACKET*)sendBufferUsrBoton)->_byte[0] = ((BOTON_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((BOTON_DATA_PACKET*)sendBufferUsrBoton)->_byte[1] = port.get_data_digital();
            userBotonCounter=0x02;
            break;
         
        case RESET:
            Reset();
            break;

        default:
            break;
      }/*end switch(s)*/
      if(userBotonCounter != 0)
      {
       j = 255;
       while(mUSBGenTxIsBusy() && j-->0); /* pruebo un máximo de 255 veces */
       if(!mUSBGenTxIsBusy())
              USBGenWrite2(usrBotonHandler, userBotonCounter);
      }/*end if */

}/*end UserBotonReceived*/

/** EOF usr_boton.c ***************************************************************/