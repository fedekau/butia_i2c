/* Author                                                   Date        Comment
 *John Pereira                                              28/02/2012
 * Andres Aguirre                                           02/03/2012
 * Aylen Ricca                                              01/04/2013
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
#include "usb4all/proxys/T0Service.h"
#include "pnp.h"

#pragma code module

/* Structures to hold motors */
typedef struct _MOTOR {
    byte id;
    byte inverse;
} MOTOR;

typedef struct _WHEELS {
    MOTOR left;
    MOTOR right;
} WHEELS;

/** V A R I A B L E S ********************************************************/
#pragma udata
WHEELS wheels;
byte* sendBufferUsrMotors; // buffer to send data
fMoveMotor moveLeftMOTOR;
fMoveMotor moveRightMOTOR;
fGetVolt getVolt;
byte current_id = 0;
byte index = 0;
byte list_motors[2];
byte MOTORS_T = MOTORS_AX12;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserMotorsInit(byte handler);
void UserMotorsReceived(byte*, byte, byte);
void UserMotorsRelease(byte handler);
void sexyMotorMoveStart();

// Table used by the framework to get a fixed reference point to the user module functions defined by the framework
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab userMotorsModuleTable = {&UserMotorsInit, &UserMotorsRelease, "motors"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module


void moveRightCC(unsigned int vel, byte sen){
    /*
     * ENABLE A = RD1
     * SENTIDO A : RD5 - RD6
     */
    //TRISD = 0x09;
    if (vel == (unsigned) 0) {
        /* detener motor derecho */
        PORTDbits.RD5 = 0;
        PORTDbits.RD6 = 0;
        PORTDbits.RD1 = 0;
    } else {
        /* mover motor derecho */
        PORTDbits.RD1 = 1;
        if (sen == (byte) 1) {
            /* adelante */
            PORTDbits.RD5 = 0;
            PORTDbits.RD6 = 1;
        } else {
            /* atras */
            PORTDbits.RD5 = 1;
            PORTDbits.RD6 = 0;
        }
    }
}

void moveLeftCC(unsigned int vel, byte sen){
     /*
     * ENABLE B = RD2
     * SENTIDO B : RD4 - RD7
     */
    //TRISD = 0x09;
    if (vel == (unsigned) 0) {
        /* detener motor izquierdo */
        PORTDbits.RD4 = 0;
        PORTDbits.RD7 = 0;
        PORTDbits.RD2 = 0;
    } else {
        /* mover motor izquierdo */
        PORTDbits.RD2 = 1;
        if (sen == (byte) 0) {
            /* adelante */
            PORTDbits.RD4 = 0;
            PORTDbits.RD7 = 1;
        } else {
            /* atras */
            PORTDbits.RD4 = 1;
            PORTDbits.RD7 = 0;
        }
    }
}

void moveRightAX(unsigned int vel, byte sen){
    endlessTurn(wheels.right.id, vel, sen);
}

void moveLeftAX(unsigned int vel, byte sen){
    endlessTurn(wheels.left.id, vel, sen);
}

void stopRight() {
    moveRightMOTOR(0, 0);
}

void backwardRight() {
    moveRightMOTOR(600, 0);
    registerT0eventInEvent(LONG_TIME_UNIT, &stopRight);
}

void forwardRight() {
    moveRightMOTOR(600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &backwardRight);
}

void stopLeft() {
    moveLeftMOTOR(0, 0);
    registerT0eventInEvent(LONG_TIME_UNIT, &forwardRight);
}

void backwardLeft() {
    moveLeftMOTOR(600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &stopLeft);
}

void forwardLeft() {
    moveLeftMOTOR(600, 0);
    registerT0eventInEvent(LONG_TIME_UNIT, &backwardLeft);
}

void sexyMotorMoveStart() {
    registerT0event(TIME_UNIT, &forwardLeft);
}

void getVoltAX(int *data_received) {
    byte data [2];
    int err = 0;
    byte id;
    data[0] = PRESENT_VOLTAGE;
    data[1] = 0x01; /*length of data to read*/
    ax12SendPacket(wheels.left.id, 0x02, READ_DATA, data);
    ax12ReadPacket(&id, &err, data_received);
}

void getVoltCC(int *data_received) {
    *data_received = 255;
}

void getVoltage(int *data_received) {
    getVolt(data_received);
}

void ConfigWheels(byte id) {
    setEndlessTurnMode(id, 1);
    writeInfo(id, CW_COMPLIANCE_MARGIN, 0);
    writeInfo(id, CCW_COMPLIANCE_MARGIN, 0);
    writeInfo(id, CW_COMPLIANCE_SLOPE, 95);
    writeInfo(id, CCW_COMPLIANCE_SLOPE, 95);
    writeInfo(id, PUNCH_L, 150);
    writeInfo(id, MAX_TORQUE_L, 1023);
    writeInfo(id, LIMIT_TEMPERATURE, 85);
    writeInfo(id, LOWEST_LIMIT_VOLT, 60);
    writeInfo(id, HIGHEST_LIMIT_VOLT, 190);
    writeInfo(id, RETURN_DELAY, 150);
}

/*
 * Function to auto-detect motors (robot wheels)
 * the less id motor correspond to left wheel
 * the other one to right wheel.
 */
void TryAutoDetect() {
    int _error, _data;
    byte _id, i;
    for (i = 0; i < C_TRIES; i++) {
        _id = 0xFFFF;
        ax12SendPacket(current_id, 0, PING, 0);
        ax12ReadPacket(&_id, &_error, &_data);
        if (_id == current_id++) {
            list_motors[index++] = _id;
            break;
        }
    }

    if (index >= (byte) 2) {
        /*Set found motors as Rigth/Left wheels*/
        wheels.left.id = list_motors[0];
        wheels.left.inverse = (byte) 0;
        ConfigWheels(wheels.left.id);
        wheels.right.id = list_motors[1];
        wheels.right.inverse = (byte) 1;
        ConfigWheels(wheels.right.id);
        sexyMotorMoveStart();
        return;
    }
    if (current_id == C_ID_MOTORS) {
        return;
    }
    registerT0eventInEvent(LONG_TIME_UNIT, &TryAutoDetect);
}

void autoDetectWheels() {
    if ((PORTC & MASK_SHIELD) == SHIELD_CC) {
        moveLeftMOTOR = &moveLeftCC;
        moveRightMOTOR = &moveRightCC;
        MOTORS_T = MOTORS_SHIELD_CC;
        getVolt = &getVoltCC;
        TRISD = 0x09;
        PORTD = 0x00;
        sexyMotorMoveStart();
    } else {
        moveLeftMOTOR = &moveLeftAX;
        moveRightMOTOR = &moveRightAX;
        MOTORS_T = MOTORS_AX12;
        getVolt = &getVoltAX;
        registerT0event(TIME_UNIT, &TryAutoDetect);
    }
}

byte getMotorType() {
    return MOTORS_T;
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
void UserMotorsInit(byte handler) {
    setHandlerReceiveFunction(handler, &UserMotorsReceived);
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrMotors = getSharedBuffer(handler);
}


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

void UserMotorsRelease(byte handler) {
    unsetHandlerReceiveBuffer(handler);
    unsetHandlerReceiveFunction(handler);
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
    byte userMotorsCounter = 0;
    byte direction1, direction2, lowVel1, lowVel2, highVel1, highVel2, idmotor;
    word vel1, vel2;
    switch (((MOTORS_DATA_PACKET*) recBuffPtr)->CMD) {

        case READ_VERSION:
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[1] = MOTORS_MINOR_VERSION;
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[2] = MOTORS_MAJOR_VERSION;
            userMotorsCounter = 0x03;
            break;

        case GET_TYPE:
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[1] = MOTORS_T;
            userMotorsCounter = 0x02;
            break;

        case SET_VEL_MTR:
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[0];
            idmotor = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[1];
            direction1 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[2];
            highVel1 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[3];
            lowVel1 = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[4];
            vel1 = highVel1;
            vel1 = vel1 << 8 | lowVel1;
            if (idmotor == (byte) 0) {
                moveLeftMOTOR(vel1, 1 - direction1);
            } else {
                moveRightMOTOR(vel1, direction1);
            }
            userMotorsCounter = 0x01;
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
            moveLeftMOTOR(vel1, 1 - direction1);
            moveRightMOTOR(vel2, direction2);
            userMotorsCounter = 0x01;
            break;

        case TEST_MOTORS:
            ((MOTORS_DATA_PACKET*) sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*) recBuffPtr)->_byte[0];
            sexyMotorMoveStart();
            userMotorsCounter = 0x01;
            break;

        default:
            break;
    }/*end switch(s)*/

    USBGenWrite2(handler, userMotorsCounter);

}/*end UserMotorsReceived*/

/** EOF usr_motors.c ***************************************************************/
