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


/** V A R I A B L E S ********************************************************/
#pragma udata

byte  usrMotorsHandler;     // Handler number asigned to the module
byte* sendBufferUsrMotors; // buffer to send data

#define FIRST_ON    0x01
#define DELAY       0x02
#define SECOND_ON   0x03
#define END         0x04

#define TIME_UNIT        2000
#define LONG_TIME_UNIT   5000
#define LEFT_MOTOR   0x01
#define RIGHT_MOTOR  0x02

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserMotorsProcessIO(void);
void UserMotorsInit(byte i);
void UserMotorsReceived(byte*, byte);
void UserMotorsRelease(byte i);
void UserMotorsConfigure(void);

// Table used by the framework to get a fixed reference point to the user module functions defined by the framework
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userMotorsModuleTable = {&UserMotorsInit,&UserMotorsRelease,&UserMotorsConfigure,"motors"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

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
typedef struct _Motor{
    int id;
    int inverse;    
} Motor;


typedef struct _Wheels{
    Motor left;
    Motor rigth;
} Wheels;


void stopRight(){
    writeInfo (RIGHT_MOTOR, 32, 0);
}

void backwardRight(){
    //writeInfo (LEFT_MOTOR, 32, -600);
    endlessTurn(RIGHT_MOTOR, -600, 1 );
    registerT0eventInEvent(LONG_TIME_UNIT, &stopRight);
}
void forwardRight(){
    //writeInfo (RIGHT_MOTOR, 32, 600);
    endlessTurn(RIGHT_MOTOR, 600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &backwardRight);
}
void stopLeft(){
    writeInfo (LEFT_MOTOR, 32, 0);
    registerT0eventInEvent(LONG_TIME_UNIT, &forwardRight);
}

void backwardLeft(){
    //writeInfo (LEFT_MOTOR, 32, 0);
    endlessTurn(LEFT_MOTOR, -600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &stopLeft);
}


void forwardLeft(){
    endlessTurn(LEFT_MOTOR, 600, 1);
    registerT0eventInEvent(LONG_TIME_UNIT, &backwardLeft);
}
void sexyMotorMoveStart(){
    setEndlessTurnMode(LEFT_MOTOR, 1);
    setEndlessTurnMode(RIGHT_MOTOR, 1);
    registerT0event(TIME_UNIT, &forwardLeft);
}

void UserMotorsInit(byte i) {
    BOOL res;
    byte resWriteInfo;
    usrMotorsHandler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrMotorsHandler,&UserMotorsReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically
    /* andres res = addPollingFunction(&UserMotorsProcessIO);*/
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrMotors = getSharedBuffer(usrMotorsHandler);
    ax12InitSerial();
    setEndlessTurnMode(LEFT_MOTOR, 1);
    setEndlessTurnMode(RIGHT_MOTOR, 1);
    //Wheels ruedas;
    /*Implementar funcion de auto deteccion para que detecte los motores*/
    /*writeInfo (ruedas.left.id, CW_COMPLIANCE_MARGIN, 0);
    writeInfo (ruedas.left.id, CCW_COMPLIANCE_MARGIN, 0);
    writeInfo (ruedas.left.id, CW_COMPLIANCE_SLOPE, 95);
    writeInfo (ruedas.left.id, CCW_COMPLIANCE_SLOPE, 95);
    writeInfo (ruedas.left.id, PUNCH_L, 150);
    writeInfo (ruedas.left.id, MAX_TORQUE_L, 1023);
    writeInfo (LIMIT_TEMPERATURE, 85);
    writeInfo (DOWN_LIMIT_VOLTAGE, 60);
    writeInfo (DOWN_LIMIT_VOLTAGE, 190);
    writeInfo (RETURN_DELAY_TIME, 150);*/

}

/******************************************************************************
/* Function:        UserAX12Configure(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the specific configuration for the user module, it is called by the framework
 *
 *
 * Note:            None
 *****************************************************************************/
void UserMotorsConfigure(void){
// Do the configuration
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

void UserMotorsProcessIO(void){

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
}//end ProcessIO

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
    //unregisterT0event(&MotorsEvent);
    //removePoolingFunction(&UserMotorsProcessIO);
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

void UserMotorsReceived(byte* recBuffPtr, byte len){
    byte j;
    byte userMotorsCounter = 0;
    char direction1, direction2;
    byte lowVel1, lowVel2, highVel1, highVel2, res;
    word vel1, vel2;
    switch(((MOTORS_DATA_PACKET*)recBuffPtr)->CMD){

        case READ_VERSION:
              ((MOTORS_DATA_PACKET*)sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[0];
              ((MOTORS_DATA_PACKET*)sendBufferUsrMotors)->_byte[1] = MOTORS_MINOR_VERSION;
              ((MOTORS_DATA_PACKET*)sendBufferUsrMotors)->_byte[2] = MOTORS_MAJOR_VERSION;
              userMotorsCounter = 0x03;
              break;
        case RESET:
              Reset();
        break;
        case SET_VEL_2MTR:
            ((MOTORS_DATA_PACKET*)sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[1];
            direction1 = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[1];
            highVel1   = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[2];
            lowVel1    = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[3];
            vel1 = highVel1;
            vel1 = vel1<<8|lowVel1;
            direction2 = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[4];
            highVel2   = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[5];
            lowVel2    = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[6];
            vel2 = highVel2;
            vel2 = vel2<<8|lowVel2;
            if(direction1==0x01){
                endlessTurn(LEFT_MOTOR, vel1, 0);
                res = writeInfo(LEFT_MOTOR, LED, 0);
            }
            else{
                endlessTurn(LEFT_MOTOR, -vel1, 0);
                res = writeInfo(RIGHT_MOTOR, LED, 0);
            }
            if(direction2==0x01)
                endlessTurn(RIGHT_MOTOR, vel2, 1);
            else
                endlessTurn(RIGHT_MOTOR, -vel2, 1);
            //TODO return error code
            userMotorsCounter = 0x01;
        break;

        case TEST_MOTORS:
            sexyMotorMoveStart();
            ((MOTORS_DATA_PACKET*)sendBufferUsrMotors)->_byte[0] = ((MOTORS_DATA_PACKET*)recBuffPtr)->_byte[0];
            userMotorsCounter = 0x01;
        break;
        default:
              break;
        }/*end switch(s)*/
        if(userMotorsCounter != 0){
            j = 255;
            while(mUSBGenTxIsBusy() && j-->0); /*pruebo un maximo de 255 veces*/
                if(!mUSBGenTxIsBusy())
                    USBGenWrite2(usrMotorsHandler, userMotorsCounter);
        }/*end if*/
}/*end UserMotorsReceived*/

/** EOF usr_Buzzer.c ***************************************************************/
