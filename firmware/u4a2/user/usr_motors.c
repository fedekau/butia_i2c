/* Author                                                   Date        Comment
 *John Pereira                                              28/02/2012
 * Andres Aguirre                                           02/03/2012
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_motors.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"
#include "usb4all/proxys/T0Service.h"

/* Structures to hold motors */
#pragma code module

typedef struct _MOTOR {
    int id;
    int inverse;
} MOTOR;

typedef struct _WHEELS {
    MOTOR left;
    MOTOR right;
} WHEELS;

/** V A R I A B L E S ********************************************************/
#pragma udata

/* robot wheels */
WHEELS wheels;
byte* sendBufferUsrMotors; // buffer to send data

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserMotorsProcessIO(void);
void UserMotorsInit(byte i);
void UserMotorsReceived(byte*, byte, byte);
void UserMotorsRelease(byte i);
void sexyMotorMoveStart(void);

// Table used by the framework to get a fixed reference point to the user module functions defined by the framework
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab userMotorsModuleTable = {&UserMotorsInit, &UserMotorsRelease, "motors"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/* Definitions to deal with autodetection motors */
byte current_id = 0;
byte index = 0;
byte list_motors[2];

void stopRight() {
    writeInfo(wheels.right.id, 32, 0);
}

void backwardRight() {
    endlessTurn(wheels.right.id, -600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &stopRight);
}

void forwardRight() {
    endlessTurn(wheels.right.id, 600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &backwardRight);
}

void stopLeft() {
    writeInfo(wheels.left.id, 32, 0);
    registerT0eventInEvent(LONG_TIME_UNIT, &forwardRight);
}

void backwardLeft() {
    endlessTurn(wheels.left.id, -600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &stopLeft);
}

void forwardLeft() {
    endlessTurn(wheels.left.id, 600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &backwardLeft);
}

void sexyMotorMoveStart() {
    setEndlessTurnMode(wheels.left.id, 1);
    setEndlessTurnMode(wheels.right.id, 1);
    registerT0event(TIME_UNIT, &forwardLeft);
}

boolean getVoltage(int *data_received) {
    byte data [2];
    int id, err = 0;
    data[0] = PRESENT_VOLTAGE;
    data[1] = 0x01; /*length of data to read*/
    ax12SendPacket(wheels.left.id, 0x02, READ_DATA, data);
    return ax12ReadPacket(&id, &err, data_received);
}

void ConfigWheels(byte id){
/*    setEndlessTurnMode(id, 1);
    writeInfo (id, CW_COMPLIANCE_MARGIN, 0);
    writeInfo (id, CCW_COMPLIANCE_MARGIN, 0);
    writeInfo (id, CW_COMPLIANCE_SLOPE, 95);
    writeInfo (id, CCW_COMPLIANCE_SLOPE, 95);
    writeInfo (id, PUNCH_L, 150);
    writeInfo (id, MAX_TORQUE_L, 1023);
    writeInfo (LIMIT_TEMPERATURE, 85);
    writeInfo (DOWN_LIMIT_VOLTAGE, 60);
    writeInfo (DOWN_LIMIT_VOLTAGE, 190);
    writeInfo (RETURN_DELAY_TIME, 150);
*/}

/*
 * Function to auto-detect motors (robot wheels)
 * the less id motor correspond to left wheel
 * the other one to right wheel.
 */
void TryAutoDetect() {
    int _id, _error, _data, i;
    for (i = 0; i < C_TRIES; i++) {
        ax12SendPacket(current_id, 0, PING, 0);
        ax12ReadPacket(&_id, &_error, &_data);
        if (_id == current_id++) {
            list_motors[index++] = _id;
            /*FIXME config motor to be used as wheels*/
            break;
        }
    }
    if (index == 2) {
        /*Set found motors as Rigth/Left wheels*/
        wheels.left.id = list_motors[0];
        wheels.left.inverse = 0;
        wheels.right.id = list_motors[1];
        wheels.right.inverse = 1;
        sexyMotorMoveStart();
        return;
    }
    if (index == C_ID_MOTORS){
        return;
    }
    registerT0eventInEvent(LONG_TIME_UNIT, &TryAutoDetect);
}

void autoDetectWheels() {
    registerT0event(TIME_UNIT, &TryAutoDetect);
}

/******************************************************************************
 * Function:        UseBuzzerInit(void)
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
void UserMotorsInit(byte usrMotorsHandler) {
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrMotorsHandler, &UserMotorsReceived);
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrMotors = getSharedBuffer(usrMotorsHandler);
}

/******************************************************************************
 * Function:        UserAX12ProcessIO(void)
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
 *                    int the PIC, also it can comunicate things to the pc by the USB
 *
 * Note:            None
 *****************************************************************************/

void UserMotorsProcessIO(void) {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == 1)) return;
}/*end ProcessIO*/

/******************************************************************************
 * Function:        UserAX12Release(byte i)
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

void UserMotorsRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    unregisterT0event(&autoDetectWheels);
}

/******************************************************************************
 * Function:        UserMotorsReceived(byte* recBuffPtr, byte len)
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

void UserMotorsReceived(byte* recBuffPtr, byte len, byte handler) {
    byte j;
    byte userMotorsCounter = 0;
    char direction1, direction2;
    byte lowVel1, lowVel2, highVel1, highVel2, res;
    word vel1, vel2;
    switch (((MOTORS_DATA_PACKET*) recBuffPtr)->CMD) {

        case READ_VERSION:
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[1] = MOTORS_MINOR_VERSION;
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[2] = MOTORS_MAJOR_VERSION;
            userMotorsCounter = 0x03;
            break;
        case RESET:
            Reset();
            break;
        case SET_VEL_2MTR:
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[0];
            direction1 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[1];
            highVel1 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[2];
            lowVel1 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[3];
            vel1 = highVel1;
            vel1 = vel1 << 8 | lowVel1;
            direction2 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[4];
            highVel2 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[5];
            lowVel2 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[6];
            vel2 = highVel2;
            vel2 = vel2 << 8 | lowVel2;
            if (direction1 == 0x01) {
                endlessTurn(wheels.left.id, vel1, 0);
            } else {
                endlessTurn(wheels.left.id, -vel1, 0);
            }
            if (direction2 == 0x01)
                endlessTurn(wheels.right.id, vel2, 1);
            else
                endlessTurn(wheels.right.id, -vel2, 1);
            userMotorsCounter = 0x01;
            break;

        case TEST_MOTORS:
            sexyMotorMoveStart();
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[0];
            userMotorsCounter = 0x01;
            break;
        default:
            break;
    }/*end switch(s)*/
    if (userMotorsCounter != 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > 0); /*pruebo un maximo de 255 veces*/
        if (!mUSBGenTxIsBusy())
            USBGenWrite2(handler, userMotorsCounter);
    }/*end if*/
}/*end UserMotorsReceived*/

/** EOF usr_motors.c ***************************************************************/
