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
#include "../usb4all/proxys/T1Service.h"
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
    TRISD &= 0x0F;
    PORTD |= 0xF0;
}

void UserShieldCCProcessIO() {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == 1)) return;
}

void UserShieldCCRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    PORTD &= 0x0F;
}

void UserShieldCCReceived(byte* recBuffPtr, byte len, byte handler) {
    byte j, sen_MI, sen_MD, velH_MI, velH_MD, velL_MI, velL_MD;
    word velD, velI;
    byte userShieldCCCounter = 0;

    switch (((SHIELD_CC_DATA_PACKET*) recBuffPtr)->CMD) {

        case READ_VERSION:
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[0] = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[1] = SHIELD_CC_MINOR_VERSION;
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[2] = SHIELD_CC_MAJOR_VERSION;
            startPWM(70);
            userShieldCCCounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        case SET_2CCMOTOR_SPEED:
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[0] = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[0];
            sen_MI = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[1];
            velH_MI = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[2];
            velL_MI = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[3];
            sen_MD = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[4];
            velH_MD = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[5];
            velL_MD = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[6];

            velD = (unsigned int) velH_MD << 8 | velL_MD;
            velI = (unsigned int) velH_MI << 8 | velL_MI;

            // frenar
            if ((velD == 0) && (velI == 0)) {
                /* pongo en cero los 4 hackp */
                PORTD |= 0xF0;
            } else {
                // motor derecho
                if (sen_MD == 0) {
                    /* adelante */
                    /* pongo P4=0 P5=1 */
                    PORTDbits.RD4 = 0;
                    PORTDbits.RD5 = 1;
                } else {
                    /* atras */
                    /* pongo 4=1 5=0 */
                    PORTDbits.RD4 = 1;
                    PORTDbits.RD5 = 0;
                }
                // motor izquierdo
                if (sen_MI == 0) {
                    /* adelante */
                    /* pongo 6=0 7=1 */
                    PORTDbits.RD6 = 0;
                    PORTDbits.RD7 = 1;
                } else {
                    /* atras */
                    /* pongo 6=1 7=0 */
                    PORTDbits.RD6 = 1;
                    PORTDbits.RD7 = 0;
                }
            }
            userShieldCCCounter = 0x01;
            break;

        case TEST:
            ((SHIELD_CC_DATA_PACKET*) sendBufferUsrShieldCC)->_byte[0] = ((SHIELD_CC_DATA_PACKET*) recBuffPtr)->_byte[0];
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
