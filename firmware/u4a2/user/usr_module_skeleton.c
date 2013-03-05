/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca                                      10/10/12    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "io_cfg.h"
#include "dynamicPolling.h"
#include "user/usb4butia.h"
#include "user/handlerManager.h"
#include "user/usr_module_skeleton.h"

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrSkeleton; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserSkeletonProcessIO(void);
void UserSkeletonInit(byte i);
void UserSkeletonReceived(byte*, byte, byte);
void UserSkeletonRelease(byte i);
void UserSkeletonConfigure(void);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE ****************************************************/
#pragma romdata user
const uTab userSkeletonModuleTable = {&UserSkeletonInit,&UserSkeletonRelease,&UserSkeletonConfigure,"modName"}; /* modName must be less 8 characters */
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserSkeletonInit(void)
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
void UserSkeletonInit(byte usrSkeletonHandler){
    /* add my receive function to the handler module, to be called automatically
     * when someone sends data to the user module */
    setHandlerReceiveFunction(usrSkeletonHandler, &UserSkeletonReceived);
    /* initialize the send buffer, used to send data */
    sendBufferUsrSkeleton = getSharedBuffer(usrSkeletonHandler);
    /* get port where sensor/actuator is connected and set to IN/OUT mode
     * as an example, it is set to IN mode */
    getPortDescriptor(usrSkeletonHandler)->change_port_direction(IN);
}/* end UserSkeletonInit */

/******************************************************************************
 * Function:        UserSkeletonConfigure(void)
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
void UserSkeletonConfigure(void){
    /* Do the configuration needed */
}/* end UserSkeletonConfigure */

/******************************************************************************
 * Function:        UserSkeletonProcessIO(void)
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
void UserSkeletonProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    /* here enter the code that want to be called periodically,
     * per example interaction with buttons and leds */
}/* end UserSkeletonProcessIO */

/******************************************************************************
 * Function:        UserSkeletonRelease(byte i)
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
void UserSkeletonRelease(byte usrSkeletonHandler){
    unsetHandlerReceiveBuffer(usrSkeletonHandler);
    unsetHandlerReceiveFunction(usrSkeletonHandler);
}/* end UserSkeletonRelease */

/******************************************************************************
 * Function:        UserSkeletonReceived(byte* recBuffPtr, byte len)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function manages the comunication with the other part
 *
 * Note:            None
 *****************************************************************************/
void UserSkeletonReceived(byte* recBuffPtr, byte len, byte handler){
    byte j;
    WORD data;
    byte userSkeletonCounter = 0;
    switch(((SKELETON_DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION:
            ((SKELETON_DATA_PACKET*)sendBufferUsrSkeleton)->_byte[0] = ((SKELETON_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((SKELETON_DATA_PACKET*)sendBufferUsrSkeleton)->_byte[1] = SKELETON_MINOR_VERSION;
            ((SKELETON_DATA_PACKET*)sendBufferUsrSkeleton)->_byte[2] = SKELETON_MAJOR_VERSION;
            userSkeletonCounter=0x03;   /* cant of bytes to be send */
            break;

        /* An example of how to read an analog value
         * sensor must have been set to IN mode, see line 63 */
        case GET_ANALOG_VALUE:
            ((SKELETON_DATA_PACKET*)sendBufferUsrSkeleton)->_byte[0] = ((SKELETON_DATA_PACKET*)recBuffPtr)->_byte[0];
            data = getPortDescriptor(handler)->get_data_analog();
            ((SKELETON_DATA_PACKET*)sendBufferUsrSkeleton)->_byte[1] = LSB(data);
            ((SKELETON_DATA_PACKET*)sendBufferUsrSkeleton)->_byte[2] = MSB(data);
            userSkeletonCounter=0x03;
            break;

        /* An example of how to read a digital value
         * sensor must have been set to IN mode, see line 63 */
        case GET_DIGITAL_VALUE:
            ((SKELETON_DATA_PACKET*)sendBufferUsrButton)->_byte[0] = ((SKELETON_DATA_PACKET*)recBuffPtr)->_byte[0];
            ((SKELETON_DATA_PACKET*)sendBufferUsrButton)->_byte[1] = getPortDescriptor(handler)->get_data_digital();
            userButtonCounter=0x02;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }/* end switch(s)*/

    if(userSkeletonCounter != 0)
    {
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); /* try at last 255 tries */
        if(!mUSBGenTxIsBusy())
            USBGenWrite2(handler, userSkeletonCounter);
    }/* end if */
}/* end UserSkeletonReceived */

/** EOF usr_module_skelton.c **************************************************/
