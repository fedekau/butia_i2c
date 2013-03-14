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
    byte j;
    byte userShieldCCCounter = 0;
    char direction1, direction2;
    byte lowVel1, lowVel2, highVel1, highVel2, res, idmotor;
    word vel1, vel2;
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
//            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[0] = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[0];
//            direction1 = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[1];
//            highVel1 = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[2];
//            lowVel1 = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[3];
//            vel1 = highVel1;
//            vel1 = vel1 << 8 | lowVel1;
//            direction2 = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[4];
//            highVel2 = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[5];
//            lowVel2 = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[6];
//            vel2 = highVel2;
//            vel2 = vel2 << 8 | lowVel2;
//            if (direction1 == 0x01) {
//                endlessTurn(wheels.left.id, vel1, 0);
//            } else {
//                endlessTurn(wheels.left.id, 0 - vel1, 0);
//            }
//            if (direction2 == 0x01)
//                endlessTurn(wheels.right.id, vel2, 1);
//            else
//                endlessTurn(wheels.right.id, 0 - vel2, 1);
//            userShieldCCCounter = 0x01;
            break;

        default:
            break;
    }/*end switch(s)*/
    if (userShieldCCCounter != 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > 0);
        if (!mUSBGenTxIsBusy())
            USBGenWrite2(handler, userShieldCCCounter);
    }/*end if*/
}/*end UserShieldCCReceived*/

/** EOF usr_shield_cc.c ***************************************************************/
