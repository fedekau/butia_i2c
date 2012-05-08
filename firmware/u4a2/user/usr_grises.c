/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca                                      19/04/12    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_grises.h"
#include "io_cfg.h"              /* I/O pin mapping*/
#include "user/handlerManager.h"
#include "dynamicPolling.h"
#include "user/usb4butia.h"     /**/

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrGrises; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserGrisesProcessIO(void);
void UserGrisesInit(byte i);
void UserGrisesReceived(byte*, byte, byte);
void UserGrisesRelease(byte i);
void UserGrisesConfigure(void);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
uTab userGrisesModuleTable = {&UserGrisesInit,&UserGrisesRelease,&UserGrisesConfigure,"grises"}; /*modName must be less or equal 8 characters*/
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserGrisesInit(void)
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
void UserGrisesInit(byte usrGrisesHandler){
    /* add my receive function to the handler module, to be called automatically
     * when the pc sends data to the user module */
    setHandlerReceiveFunction(usrGrisesHandler,&UserGrisesReceived);
    /* initialize the send buffer, used to send data to the PC */
    sendBufferUsrGrises = getSharedBuffer(usrGrisesHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode*/
    getPortDescriptor(usrGrisesHandler)->change_port_direction(IN);
}/*end UserGrisesInit*/

/******************************************************************************
 * Function:        UserGrisesConfigure(void)
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
void UserGrisesConfigure(void){
    /* Do the configuration */
}/*end UserGrisesConfigure*/

/******************************************************************************
 * Function:        UserGrisesProcessIO(void)
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
void UserGrisesProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
	/* here enter the code that want to be called periodically,
         * per example interaction with buttons and leds */
}/*end UserGrisesProcessIO*/

/******************************************************************************
 * Function:        UserGrisesRelease(byte i)
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
void UserGrisesRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}/*end UserGrisesRelease*/

/******************************************************************************
 * Function:        UserGrisesReceived(byte* recBuffPtr, byte len)
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
void UserGrisesReceived(byte* recBuffPtr, byte len, byte handler){
    byte j;
    WORD data;
    byte userGrisesCounter = 0;
    switch(((GRISES_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION:
            ((GRISES_DATA_PACKET*)sendBufferUsrGrises)->_byte[0] = ((GRISES_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((GRISES_DATA_PACKET*)sendBufferUsrGrises)->_byte[1] = GRISES_MINOR_VERSION;
            ((GRISES_DATA_PACKET*)sendBufferUsrGrises)->_byte[2] = GRISES_MAJOR_VERSION;
            userGrisesCounter=0x03;
            break;

        case GET_ANA_VALUE:
            ((GRISES_DATA_PACKET*)sendBufferUsrGrises)->_byte[0] = ((GRISES_DATA_PACKET*)recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((GRISES_DATA_PACKET*)sendBufferUsrGrises)->_byte[1] = MSB(data);
            ((GRISES_DATA_PACKET*)sendBufferUsrGrises)->_byte[2] = LSB(data);
            userGrisesCounter=0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/*end switch(s)*/

    if(userGrisesCounter != 0)
    {
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); /* pruebo un mÃ¡ximo de 255 veces */
        if(!mUSBGenTxIsBusy())
            USBGenWrite2(handler, userGrisesCounter);
    }/*end if*/
}/*end UserGrisesReceived*/

/** EOF usr_grises.c ***************************************************************/
