
/* Author 			     Comment
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_i2c.h"
#include "io_cfg.h"              /* I/O pin mapping */
#include "user/handlerManager.h"
#include "user/usb4butia.h"
#include <delays.h>
#include "i2c.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
byte* sendBufferUsrI2C; /* buffer to send data*/

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserI2CInit(byte handler);
void UserI2CReceived(byte*, byte, byte);
void UserI2CRelease(byte handler);

/* Table used by te framework to get a fixed reference point to the user module functions defined by the framework */
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab userI2CModuleTable = {&UserI2CInit, &UserI2CRelease, "i2c"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UserI2CInit(byte)
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

void UserI2CInit(byte handler) {
    /* add my receive function to the handler module, to be called automatically when the pc sends data to the user module*/
    setHandlerReceiveFunction(handler, &UserI2CReceived);
    /* initialize the send buffer, used to send data to the PC*/
    sendBufferUsrI2C = getSharedBuffer(handler);
    getPortDescriptor(handler)->change_port_direction(IN);
}/*end UserButtonInit*/


/******************************************************************************
 * Function:        UserI2CRelease(byte i)
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

void UserI2CRelease(byte handler) {
    unsetHandlerReceiveBuffer(handler);
    unsetHandlerReceiveFunction(handler);
}

/******************************************************************************
 * Function:        UserI2CReceived(byte* recBuffPtr, byte len)
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

void blinkRojo(){
    LATDbits.LATD4 = 1;
    Delay10KTCYx(0);
    LATDbits.LATD4 = 0;
    Delay10KTCYx(0);
}

void blinkVerde(){
    LATDbits.LATD5 = 1;
    Delay10KTCYx(0);
    Delay10KTCYx(0);
    LATDbits.LATD5 = 0;
    Delay10KTCYx(0);
}

char label[] = "SEND_HELLO";
int adcon, pcfg, adon;

void UserI2CReceived(byte* recBuffPtr, byte len, byte handler) {
    byte userI2CCounter = 0;
    
    adcon = ADCON1;
    pcfg = ADCON1bits.PCFG;
    adon = ADCON0bits.ADON;
            
    ADCON1bits.PCFG = 1;
    ADCON1 = 0x07;
    ADCON0bits.ADON = 0;
    //blinkRojo();
    switch (((I2C_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
           ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[0] = ((I2C_DATA_PACKET*) recBuffPtr)->_byte[0];
           ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[1] = 0;
           ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[2] = 0;
           userI2CCounter = 0x03;
           break;
        case OPEN_I2C:
            ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[0] = ((I2C_DATA_PACKET*) recBuffPtr)->_byte[0];
            OpenI2C(MASTER, SLEW_OFF);
            //blinkVerde();
            SSPADD = 0x31; //100kHz Baud clock(0x31) @20MHz
            //blinkVerde();
            //send(2);
            userI2CCounter = 0x01;
            break;
        case START_I2C:
            ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[0] = ((I2C_DATA_PACKET*) recBuffPtr)->_byte[0];
            StartI2C();
            IdleI2C();
            userI2CCounter = 0x01;
            break;
        case IDLE_I2C:
            ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[0] = ((I2C_DATA_PACKET*) recBuffPtr)->_byte[0];
            IdleI2C();
            userI2CCounter = 0x01;
            break;
        case WRITE_I2C:
            ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[0] = ((I2C_DATA_PACKET*) recBuffPtr)->_byte[0];
            //blinkVerde();
            WriteI2C(((I2C_DATA_PACKET*) recBuffPtr)->_byte[1]);
            //blinkVerde();
            IdleI2C();
            //blinkVerde();
            userI2CCounter = 0x01;
            //blinkVerde();
            break;
        case READ_I2C:
            ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[0] = ((I2C_DATA_PACKET*) recBuffPtr)->_byte[0];
            ReadI2C();
            userI2CCounter = 0x01;
            break;
        case STOP_I2C:
            ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[0] = ((I2C_DATA_PACKET*) recBuffPtr)->_byte[0];
            StopI2C();
            userI2CCounter = 0x01;
            break;
        case CLOSE_I2C:
            ((I2C_DATA_PACKET*) sendBufferUsrI2C)->_byte[0] = ((I2C_DATA_PACKET*) recBuffPtr)->_byte[0];
            CloseI2C();
            userI2CCounter = 0x01;
            break;
        default:
            break;
    }/*end switch(s)*/
    //blinkRojo();
    ADCON1 = adcon;
    ADCON0bits.ADON = adon;
    ADCON1bits.PCFG = pcfg;
    USBGenWrite2(handler, userI2CCounter);

}/*end UserButtonReceived*/

/** EOF usr_button.c ***************************************************************/