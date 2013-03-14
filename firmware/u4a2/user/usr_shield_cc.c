/******************************************************************************
 * Author - Date - Comment
 *----------------------------------------------------------------------------
 * Ayle - 03/2013 - new module.
 ******************************************************************************/

/** I N C L U D E S ***********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_shield_cc.h"
#include "io_cfg.h"
#include "user/handlerManager.h"
#include "dynamicPolling.h"

/** V A R I A B L E S *********************************************************/
#pragma udata
byte* sendBufferUsrShieldCC; /* buffer to send data */

/** P R I V A T E  P R O T O T Y P E S ****************************************/
void UserShieldCCProcessIO(void);
void UserShieldCCInit(byte i);
void UserShieldCCReceived(byte*, byte, byte);
void UserShieldCCRelease(byte i);
void sexyMotorMoveStart(void);

/** U S E R  M O D U L E  R E F E R E N C E ***********************************/
#pragma romdata user
const uTab userShieldCCModuleTable = {&UserShieldCCInit, &UserShieldCCRelease, "shld_cc"};
#pragma code

/** D E C L A R A T I O N S ***************************************************/
#pragma code module

void UserShieldCCInit(byte usrShieldCCHandler) {
    setHandlerReceiveFunction(usrShieldCCHandler, &UserShieldCCReceived);
    sendBufferUsrShieldCC = getSharedBuffer(usrShieldCCHandler);
}

void UserShieldCCProcessIO(void) {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == 1)) return;
}

void UserShieldCCRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
}

void UserShieldCCReceived(byte* recBuffPtr, byte len, byte handler) {
    byte j, dir_MI, dir_MD, en_MI, en_MD;
    byte userShieldCCCounter = 0;

    switch (((SHIELD_CC_DATA_PACKET*) recBuffPtr)->CMD) {

        case READ_VERSION:
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[0] = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[1] = SHIELD_CC_MINOR_VERSION;
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[2] = SHIELD_CC_MAJOR_VERSION;
            userShieldCCCounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        case SET_2CCMOTOR_SPEED:
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[0] = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[0];
            dir_MI = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[1];
            en_MI = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[2];
            dir_MD = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[3];
            en_MD = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[4];
            PORTD |= (dir_MI << 3) | (en_MI << 2) | (dir_MD << 1) | en_MD;
            userShieldCCCounter = 0x01;
            break;

        default:
            break;
    }
    if (userShieldCCCounter != 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > 0);
        if (!mUSBGenTxIsBusy())
            USBGenWrite2(handler, userShieldCCCounter);
    }
}/*end UserShieldCCReceived*/

/** EOF usr_shield_cc.c *******************************************************/
