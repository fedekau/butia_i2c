/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca                                      19/04/12    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_light.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "dynamicPolling.h"
#include "user/usb4butia.h"     /**/

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrLight; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserLightProcessIO(void);
void UserLightInit(byte i);
void UserLightReceived(byte*, byte, byte);
void UserLightRelease(byte i);
void UserLightConfigure(void);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userLightModuleTable = {&UserLightInit,&UserLightRelease,&UserLightConfigure,"light"}; /*modName must be less or equal 8 characters*/
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserLightInit(void)
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
void UserLightInit(byte usrLightHandler){
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(usrLightHandler,&UserLightReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrLight = getSharedBuffer(usrLightHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(usrLightHandler)->change_port_direction(IN);
}/*end UserLightInit*/

/******************************************************************************
 * Function:        UserLightConfigure(void)
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
void UserLightConfigure(void){
    /* Do the configuration */
}/*end UserLightConfigure*/

/******************************************************************************
 * Function:        UserLightProcessIO(void)
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
void UserLightProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
	/* here enter the code that want to be called periodically,
         * per example interaction with buttons and leds */
}/*end UserLightProcessIO*/

/******************************************************************************
 * Function:        UserLightRelease(byte i)
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
void UserLightRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}/*end UserLightRelease*/

/******************************************************************************
 * Function:        UserLightReceived(byte* recBuffPtr, byte len)
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
void UserLightReceived(byte* recBuffPtr, byte len, byte handler){
    byte j;
    WORD data;
    byte userLightCounter = 0;
    switch(((LIGHT_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION:
            ((LIGHT_DATA_PACKET*)sendBufferUsrLight)->_byte[0] = ((LIGHT_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((LIGHT_DATA_PACKET*)sendBufferUsrLight)->_byte[1] = LIGHT_MINOR_VERSION;
            ((LIGHT_DATA_PACKET*)sendBufferUsrLight)->_byte[2] = LIGHT_MAJOR_VERSION;
            userLightCounter=0x03;
            break;

        case GET_VALUE:
            ((LIGHT_DATA_PACKET*)sendBufferUsrLight)->_byte[0] = ((LIGHT_DATA_PACKET*)recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((LIGHT_DATA_PACKET*)sendBufferUsrLight)->_byte[1] = LSB(data);
            ((LIGHT_DATA_PACKET*)sendBufferUsrLight)->_byte[2] = MSB(data);
            userLightCounter=0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    if(userLightCounter != 0)
    {
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); /* pruebo un mÃ¡ximo de 255 veces */
        if(!mUSBGenTxIsBusy())
            USBGenWrite2(handler, userLightCounter);
    }/*end if*/
}/*end UserLightReceived*/

/** EOF usr_light.c ***************************************************************/