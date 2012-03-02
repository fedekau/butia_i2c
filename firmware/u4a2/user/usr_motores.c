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
#include "user/usr_motores.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"
#include "usb4all/proxys/T0Service.h"


/** V A R I A B L E S ********************************************************/
#pragma udata

byte  usrMotoresHandler;     // Handler number asigned to the module
byte* sendBufferUsrMotores; // buffer to send data

#define FIRST_ON    0x01
#define DELAY       0x02
#define SECOND_ON   0x03
#define END         0x04

#define TIME_UNIT        2000
#define LONG_TIME_UNIT   5000
#define LEFT_MOTOR   0x01
#define RIGHT_MOTOR  0x02

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserMotoresProcessIO(void);
void UserMotoresInit(byte i);
void UserMotoresReceived(byte*, byte);
void UserMotoresRelease(byte i);
void UserMotoresConfigure(void);

// Table used by the framework to get a fixed reference point to the user module functions defined by the framework
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userMotoresModuleTable = {&UserMotoresInit,&UserMotoresRelease,&UserMotoresConfigure,"motores"}; //modName must be less or equal 8 characters
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

void UserMotoresInit(byte i) {
    BOOL res;
    byte resWriteInfo;
    usrMotoresHandler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrMotoresHandler,&UserMotoresReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically
    /* andres res = addPollingFunction(&UserMotoresProcessIO);*/
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrMotores = getSharedBuffer(usrMotoresHandler);
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
void UserMotoresConfigure(void){
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

void UserMotoresProcessIO(void){

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

void UserMotoresRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    //unregisterT0event(&MotoresEvent);
    //removePoolingFunction(&UserMotoresProcessIO);
}


/******************************************************************************
 * Function:        UserMotoresReceived(byte* recBuffPtr, byte len)
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

void UserMotoresReceived(byte* recBuffPtr, byte len){
    byte index;
    byte j;
    byte userMotoresCounter = 0;
    byte id, regstart, resWriteInfo, valueH, valueL, sentidoIzq, velIzq, sentidoDer, velDer;
    int value;
    char direction1, direction2;
    byte lowVel1, lowVel2, highVel1, highVel2, res;
    word vel1, vel2;
    switch(((MOTORES_DATA_PACKET*)recBuffPtr)->CMD){

        case READ_VERSION:
              ((MOTORES_DATA_PACKET*)sendBufferUsrMotores)->_byte[0] = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[0];
              ((MOTORES_DATA_PACKET*)sendBufferUsrMotores)->_byte[1] = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[1];
              ((MOTORES_DATA_PACKET*)sendBufferUsrMotores)->_byte[2] = MOTORES_MINOR_VERSION;
              ((MOTORES_DATA_PACKET*)sendBufferUsrMotores)->_byte[3] = MOTORES_MAJOR_VERSION;
              userMotoresCounter = 0x04;
              break;
        //byte writeInfo (byte id,byte regstart, int value) {
        case RESET:
              Reset();
        break;
        case SET_VEL_2MTR:
            ((MOTORES_DATA_PACKET*)sendBufferUsrMotores)->_byte[0] = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[1];
            ((MOTORES_DATA_PACKET*)sendBufferUsrMotores)->_byte[1] = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[4];
            direction1 = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[1];
            highVel1   = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[2];
            lowVel1    = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[3];
            vel1 = highVel1;
            vel1 = vel1<<8|lowVel1;
            direction2 = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[4];
            highVel2   = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[5];
            lowVel2    = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[6];
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
            userMotoresCounter = 0x02;
        break;

        case TEST_MOTORES:
            sexyMotorMoveStart();
            ((MOTORES_DATA_PACKET*)sendBufferUsrMotores)->_byte[0] = ((MOTORES_DATA_PACKET*)recBuffPtr)->_byte[0];
            userMotoresCounter = 0x01;
        break;
        default:
              break;
        }//end switch(s)
        if(userMotoresCounter != 0){
            j = 255;
            while(mUSBGenTxIsBusy() && j-->0); // pruebo un máximo de 255 veces
                if(!mUSBGenTxIsBusy())
                    USBGenWrite2(usrMotoresHandler, userMotoresCounter);
        }//end if
}//end UserMotoresReceived

/** EOF usr_Buzzer.c ***************************************************************/
