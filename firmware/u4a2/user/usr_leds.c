/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Reyes, Aguirre                 					       28/10/10    Original.
 ******************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_leds.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "dynamicPolling.h"                              
#include "usb4all/proxys/T0Service.h"

//#define TIME_UNIT 63583 //100ms
#define TIME_UNIT 2000

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrLedsHandler;	 // Handler number asigned to the module
byte* sendBufferUsrLeds;  // buffer to send data
byte num_led = 3;
byte timeOutTicks1, timeOutTicks2, timeOutTicks3;
byte ticks1, ticks2, ticks3;
byte blinks = 200;
byte blinks1, blinks2, blinks3;
byte cantTicks = 20;
byte needRegister1 = 1, needRegister2 = 1, needRegister3 = 1;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserLedsProcessIO(void);
void UserLedsInit(byte i);
void UserLedsReceived(byte*, byte);
void UserLedsRelease(byte i);
void UserLedsConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userLedsModuleTable = {&UserLedsInit,&UserLedsRelease,&UserLedsConfigure,"leds"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/******************************************************************************
 * Function:        UseLedsInit(void)
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
 *					when the module is opened	
 *
 * Note:            None
 *****************************************************************************/

void UserLedsInit(byte i) {
	BOOL res;
	usrLedsHandler = i;
	// add my receive function to the handler module, to be called automatically when the pc sends data to the user module
	setHandlerReceiveFunction(usrLedsHandler,&UserLedsReceived);
	// add my receive pooling function to the dynamic pooling module, to be called periodically 
	res = addPollingFunction(&UserLedsProcessIO);
	// initialize the send buffer, used to send data to the PC
	sendBufferUsrLeds = getSharedBuffer(usrLedsHandler);
    //se hace en el main ahora mInitLeds();
	/*mInitLed1();
	mInitLed2();
	mInitLed3();*/
    //initT0Service();
}//end UserLedsInit

/******************************************************************************
/* Function:        UserLedsConfigure(void)
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
void UserLedsConfigure(void){
// Do the configuration
}

 
/***********************************************************************
*
* Callback function to execute periodicaly by te Timmer interrupt ISR
*
************************************************************************/
#define CREATE_blinkEvent_N(N)                                          \
void blinkEvent_ ## N() {                                               \
    needRegister ## N = 1;                                              \
    if(timeOutTicks ## N < 255) timeOutTicks ## N --;                   \
    if(timeOutTicks ## N == 0) {                                        \
        if(blinks ## N > 0) {                                           \
            mLED_N_Toggle(N);                                           \
            blinks ## N --;                                             \
            timeOutTicks ## N = ticks ## N;                             \
        } else {                                                        \
            needRegister ## N = 0;                                      \
            mLED_N_Off(N);                                              \
        }                                                               \
    }                                                                   \
    if (needRegister ## N == 1) {                                       \
        registerT0eventInEvent(TIME_UNIT, &blinkEvent_ ## N);           \
    }                                                                   \                                                    \
}

CREATE_blinkEvent_N(1)
CREATE_blinkEvent_N(2)
CREATE_blinkEvent_N(3)

       
/******************************************************************************
 * Function:        blink_led
 *
 * PreCondition:    -
 *
 * Input:           - ticks: delay of blink, bks: amount of blinks, led: witch led
 *
 * Output:          -
 *
 * Side Effects:    -
 *
 * Overview:        it register blinkEvent_N for the led to be bliking
 *
 * Note:            -
 *****************************************************************************/

#define CASE(N)                                                               \
        case N:                                                               \
            ticks ## N = ticks;                                               \
            blinks ## N = bks * 2;                                            \
            timeOutTicks ## N = ticks ## N;                                   \
            unregisterT0event(&blinkEvent_ ## N);                             \
            registerT0event(TIME_UNIT, &blinkEvent_ ## N);                    \
            break;

//            mLED_ ## N ## _Toggle();                                          \

void blink_led(byte ticks, byte bks, byte led) { 
    switch(led) {
        CASE(1);
        CASE(2);
        CASE(3);
    }
}


/******************************************************************************
 * Function:        UserLedsProcessIO(void)
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
 *					int the PIC, also it can comunicate things to the pc by the USB	
 *
 * Note:            None
 *****************************************************************************/

void UserLedsProcessIO(void){  

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    if(needRegister1 == 0){
        unregisterT0event(&blinkEvent_1);
        needRegister1 = 1;
    }
    if(needRegister2 == 0){
        unregisterT0event(&blinkEvent_2);
        needRegister2 = 1;
    }
    if(needRegister3 == 0){
        unregisterT0event(&blinkEvent_3);
        needRegister3 = 1;
    }
}//end ProcessIO

/******************************************************************************
 * Function:        UserLedsRelease(byte i)
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

void UserLedsRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    unregisterT0event(&blinkEvent_1);
    unregisterT0event(&blinkEvent_2);
    unregisterT0event(&blinkEvent_3);
}



/******************************************************************************
 * Function:        UserLedsReceived(byte* recBuffPtr, byte len)
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

void UserLedsReceived(byte* recBuffPtr, byte len){
    byte index, j;
    byte userLedsCounter = 0;
    switch(((LEDS_DATA_PACKET*)recBuffPtr)->CMD)
    {
    case READ_VERSION:
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[0] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[0];
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[1] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[1]; 
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[2] = LEDS_MINOR_VERSION;
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[3] = LEDS_MAJOR_VERSION;
        while(1);
        userLedsCounter = 0x04;
        break;
    case BLINK:
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[0] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[0];
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[1] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[1];
        cantTicks = (((LEDS_DATA_PACKET*)recBuffPtr)->_byte[1]);
        blinks    = (((LEDS_DATA_PACKET*)recBuffPtr)->_byte[2]) - 1;  
        num_led   = (((LEDS_DATA_PACKET*)recBuffPtr)->_byte[3]);  

        if(needRegister1 == 0) {
            unregisterT0event(&blinkEvent_1);
            needRegister1 = 1;
        }
        if(needRegister2 == 0) {
            unregisterT0event(&blinkEvent_2);
            needRegister2 = 1;
        }
        if(needRegister3 == 0) {
            unregisterT0event(&blinkEvent_3);
            needRegister3 = 1;
        }
        blink_led(cantTicks, blinks, num_led);     
        /*
        if (num_led == 1){
            blinks1 = blinks;
            timeOutTicks1 = cantTicks;
            unregisterT0event(&blinkEvent_1);
            mLED_1_Toggle();
            registerT0event(TIME_UNIT, &blinkEvent_1);
        }else if(num_led == 2){
            blinks2 = blinks;
            timeOutTicks2 = cantTicks;
            unregisterT0event(&blinkEvent_2);
            mLED_2_Toggle();
            registerT0event(TIME_UNIT, &blinkEvent_2);
        }else{
            blinks3 = blinks;
            timeOutTicks3 = cantTicks;
            unregisterT0event(&blinkEvent_3);
            mLED_3_Toggle();
            registerT0event(TIME_UNIT, &blinkEvent_3);
        }
        */
        userLedsCounter = 0x02;
        break;
    case PRENDER:
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[0] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[0];
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[1] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[1]; 
        num_led = (((LEDS_DATA_PACKET*)recBuffPtr)->_byte[1]);

        if (num_led == 1){
            mLED_1_On();
        }else if(num_led == 2){
            mLED_2_On();
        }else{
            mLED_3_On();
        }
        userLedsCounter = 0x02;
        //sendDebug("prendo", 7);
        break;
    case APAGAR:
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[0] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[0];
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[1] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[1];
        num_led = (((LEDS_DATA_PACKET*)recBuffPtr)->_byte[1]); 

        if (num_led == 1){
            mLED_1_Off();
                unregisterT0event(&blinkEvent_1);
        }else if(num_led == 2){
            mLED_2_Off();
                unregisterT0event(&blinkEvent_2);
        }else{
            mLED_3_Off();
                unregisterT0event(&blinkEvent_3);
        }
        userLedsCounter = 0x02;
        //sendDebug("apago", 6);
        break;
    case RESET:
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[0] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[0];
        ((LEDS_DATA_PACKET*)sendBufferUsrLeds)->_byte[1] = ((LEDS_DATA_PACKET*)recBuffPtr)->_byte[1]; 
        Reset();
        userLedsCounter = 0x02;
        break;
    default:
        break;
    }//end switch(s)
    if(userLedsCounter != 0){
        j = 255;
        while(mUSBGenTxIsBusy() && j-->0); // pruebo un máximo de 255 veces
            if(!mUSBGenTxIsBusy())
                USBGenWrite2(usrLedsHandler, userLedsCounter);
    }//end if  	  	
}//end UserledsReceived

/** EOF usr_leds.c ***************************************************************/
