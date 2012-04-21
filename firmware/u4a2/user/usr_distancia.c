/* Author                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca              16/04/2012  Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "user\usr_distancia.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user\handlerManager.h"
#include "dynamicPolling.h"
#include "user/usb4butia.h"     /**/

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrDistHandler;	 /* Handler number asigned to the module*/
byte* sendBufferUsrDist; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserDistProcessIO(void);
void UserDistInit(byte i);
void UserDistReceived(byte*, byte, port_descriptor);
void UserDistRelease(byte i);
void UserDistConfigure(void);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
uTab userDistModuleTable = {&UserDistInit,&UserDistRelease,&UserDistConfigure,"dist"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserDistInit(void)
 *
 * PreCondition:    None
 *
 * Input:           module handler identifier
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initialices the resources that the user
 *                  module needs to work, it is called by the framework when
 *                  the module is opened.
 *
 * Note:            None
 *****************************************************************************/
void UserDistInit(byte i){
    port_descriptor port;
    usrDistHandler = i;
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(usrDistHandler,&UserDistReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrDist = getSharedBuffer(usrDistHandler);
    /* get port where sensor/actuator is connected and set to IN mode*/
    port = board_ports[usrDistHandler];
    port.change_port_direction(IN);
}/*end UserDistInit*/

/******************************************************************************
 * Function:        UserDistConfigure(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the specific configuration for the user
 *                  module, it is called by the framework.
 *
 * Note:            None
 *****************************************************************************/
void UserDistConfigure(void){
    /* Do the configuration */
}/*end UserDistConfigure*/

/******************************************************************************
 * Function:        UserDistProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is registered in the dinamic polling, who
 *                  calls it periodically to process the IO interaction in the
 *                  PIC, it also can comunicate things to the pc by the USB.
 *
 * Note:            None
 *****************************************************************************/
void UserDistProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
	/* here enter the code that want to be called periodically,
         * per example interaction with buttons and leds */
}/*end UserDistProcessIO*/

/******************************************************************************
 * Function:        UserDistRelease(byte i)
 *
 * PreCondition:    None
 *
 * Input:           module handler identifier
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function release all the resources that the user
 *                  module used, it is called by the framework
 *                  when the module is close.
 *
 * Note:            None
 *****************************************************************************/
void UserDistRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}/*end UserDistRelease*/

/******************************************************************************
 * Function:        UserDistReceived(byte* recBuffPtr, byte len)
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
void UserDistReceived(byte* recBuffPtr, byte len, port_descriptor port){
    byte j;
    WORD data;
    byte userDistCounter = 0;
    switch(((DIST_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case GET_DISTANCE:
            ((DIST_DATA_PACKET*)sendBufferUsrDist)->_byte[0] = ((DIST_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((DIST_DATA_PACKET*)sendBufferUsrDist)->_byte[1] = port.get_data_analog().v[1];
            ((DIST_DATA_PACKET*)sendBufferUsrDist)->_byte[2] = port.get_data_analog().v[0];
            userDistCounter=0x03;
            break;

        case READ_VERSION:
            ((DIST_DATA_PACKET*)sendBufferUsrDist)->_byte[0] = ((DIST_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((DIST_DATA_PACKET*)sendBufferUsrDist)->_byte[1] = DIST_MINOR_VERSION;
            ((DIST_DATA_PACKET*)sendBufferUsrDist)->_byte[2] = DIST_MAJOR_VERSION;
            userDistCounter=0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    if(userDistCounter != 0)
    {
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); /* pruebo un máximo de 255 veces */
        if(!mUSBGenTxIsBusy())
            USBGenWrite2(usrDistHandler, userDistCounter);
    }/*end if*/
}/*end UserDistReceived*/

/** EOF usr_distancia.c ***************************************************************/
