/* Author                                                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre, Edgardo Vaz, Santiago Reyes
 *****************************************************************************/
 
/* Modulo de seguridad para el sistema AFE, periodicamente monitorea los sensores de movimiento, en caso de encontrar intrusion se alamcena 
una flag en la memoria EEPROM del microcontrolador para registrar la instrusion. Esta flag es consultada mediante el comando intrusion. 
Notar que aunque se desconecte la alimentacion del dispositivo la flag va a seguir estando guardada en la EEPROM */ 

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user\handlerManager.h"
#include "dynamicPolling.h"
#include "user\usr_sec.h"
#include "user\adminModule.h"
#define TRUE 0x01
#define FALSE 0x00
  
/** V A R I A B L E S ********************************************************/
#pragma udata 

byte  usrSecHandler;     // Handler number asigned to the module
byte* sendBufferUsrSec;  // buffer to send data
byte  SecSensorValue_1, SecSensorValue_2;
int contAlarma = 0;
int maxContAlarma = 6000;
byte isWriteIntrusion = FALSE;
byte esperandoBajaSensor = FALSE;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserSecProcessIO(void);
void UserSecInit(byte i);
void UserSecReceived(byte*, byte);
void UserSecRelease(byte i);
void UserSecConfigure(void);

void Escribir_memoria(void);
unsigned char isHimenBroken(void);
void Alarma(void);
unsigned char resetFlag(void);


// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab UserSecModuleTable = {&UserSecInit,&UserSecRelease,&UserSecConfigure,"sec"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/***************************************************************************************
* helper function to test if the eeprom is ready similar to Busy_eep but non blockiing
***************************************************************************************/
/*
void Busy_eep_non_block ( void ){
    byte j = 255;
    while(EECON1bits.WR && j-->0);
}
*/

/******************************************************************************
 * Function:        UserSecInit(void)
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

void UserSecInit(byte i){
    BOOL res;
    usrSecHandler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(usrSecHandler,&UserSecReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically 
    res = addPollingFunction(&UserSecProcessIO);
    // initialize the send buffer, used to send data to the PC
    sendBufferUsrSec = getSharedBuffer(usrSecHandler);
    //andres registerT0event(65000, &Alarma);
}

/******************************************************************************
/* Function:        UserSecConfigure(void)
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
void UserSecConfigure(void){
// Do the configuration
}


/******************************************************************************
 * Function:        UserSecProcessIO(void)
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
/*implemento la consulta de los sensores de movimiento en la rutina de pooling, antes estaba registrado cada 500 ticks para la rutina del timer, eso producia que se pasara mucho tiempo
procesando interrupciones, dejando poco tiempo de CPU a proceso de modulos de usurio y producia ETIMEOUT (-145 en mips) a la aplicacion de usuario*/
void UserSecProcessIO(void){  

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    if ( contAlarma > maxContAlarma){
        SecSensorValue_1 = 0x00; 
        SecSensorValue_2 = 0x00;
        SecSensorValue_1 = PORTDbits.RD7;
        SecSensorValue_2 = PORTAbits.RA4;
        if ((SecSensorValue_1 == 0) && (SecSensorValue_2 == 0)){
                esperandoBajaSensor = FALSE;
        }
        if (((SecSensorValue_1 != 0) || (SecSensorValue_2 != 0)) && (isWriteIntrusion == FALSE)){
            //mLED_1_Toggle();mLED_2_Toggle();mLED_3_Toggle(); //testeando
            if(!esperandoBajaSensor){
                Escribir_memoria(); 
                isWriteIntrusion = TRUE;
            }
        }
        contAlarma = 0;
        //mLED_2_Toggle(); debug
    } else {
        contAlarma++;
    }
    return; //prbando si elimina el stack overflow
}//end ProcessIO

/******************************************************************************
 * Function:        UserSecRelease(byte i)
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

void UserSecRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    removePoolingFunction(&UserSecProcessIO);
}

/******************************************************************************
 * Function:        Escribir_memoria(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:       Esta función graba la bandera de intrusión en la dirección estipulada
 *                    
 *
 * Note:            None
 *****************************************************************************/

void Escribir_memoria(void){
    Busy_eep_non_block();
    Write_b_eep(ADDRESS_FLAG,BROKEN_FLAG);
}

/******************************************************************************
 * Function:        isHimenBroken(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Valor de bandera alertando sobre una intrusion
 *
 * Side Effects:    None
 *
 * Overview:       Lee un valor desde un lugar específico de la eeprom y lo compara para saber si hubo instrusion     
 *
 * Note:            None
 *****************************************************************************/
unsigned char isHimenBroken(void){
    unsigned char data_eeprom;
    Busy_eep_non_block(); 
    data_eeprom = Read_b_eep(ADDRESS_FLAG);
    if(data_eeprom == BROKEN_FLAG)
        return 1;
    else    
	return 0;
}

unsigned char resetFlag(void){
    unsigned char data_eeprom;
    data_eeprom = Read_b_eep(ADDRESS_FLAG);
    data_eeprom = Read_b_eep(ADDRESS_FLAG);
    if(data_eeprom == BROKEN_FLAG){
        Busy_eep_non_block();
        Write_b_eep(ADDRESS_FLAG,FLAG_RESET);
        return 1;
    }
    else
        return 0;
}

/*void Alarma(void){
    SecSensorValue_1 = 0x00;
    SecSensorValue_2 = 0x00;
    if ( contAlarma > maxContAlarma){
        SecSensorValue_1 = PORTDbits.RD7;
        SecSensorValue_2 = PORTAbits.RA4;
        if ((SecSensorValue_1 != 0) || (SecSensorValue_2 != 0)){
            Escribir_memoria();                    
        }
        contAlarma = contAlarmaDelay;
	mLED_3_Toggle();
    } else {
        contAlarma++;
    }
///    if(registeredISR == FALSE){	
       registerT0eventInEvent(6500, &Alarma);
///        registeredISR = TRUE;
///    }
    mLED_2_Toggle()
}
*/

/******************************************************************************
 * Function:        UserSecReceived(byte* recBuffPtr, byte len)
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

void UserSecReceived(byte* recBuffPtr, byte len){
      byte index;
      byte j;
      byte UserSecCounter = 0;
      switch(((SEC_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
              ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[0] = ((SEC_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[1] = ((SEC_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[2] = SEC_MINOR_VERSION;
              ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[3] = SEC_MAJOR_VERSION;
              UserSecCounter = 0x04;
              break;  

        case GET_SEC:
              SecSensorValue_1 = 0x00;
              SecSensorValue_2 = 0x00;
              SecSensorValue_1 = PORTDbits.RD7;
              SecSensorValue_2 = PORTAbits.RA4;
              ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[0] = ((SEC_DATA_PACKET*)recBuffPtr)->_byte[0]; 
              ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[1] = SecSensorValue_1;
              ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[2] = SecSensorValue_2;
              UserSecCounter = 0x03;
              break;  

        case INTRUSION:
                ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[0] = isHimenBroken();
                UserSecCounter=0x01;
            break; 
        case RESET_FLAG:
                ((SEC_DATA_PACKET*)sendBufferUsrSec)->_byte[0] = resetFlag();
                isWriteIntrusion = FALSE;
                esperandoBajaSensor = TRUE;
                UserSecCounter=0x01;
            break; 
        case RESET:
              Reset();
              break;
          
         default:
              break;
      }//end switch(s)
      if(UserSecCounter != 0){
            j = 255;
            while(mUSBGenTxIsBusy() && j-->0); // pruebo un máximo de 255 veces
                if(!mUSBGenTxIsBusy())
                    USBGenWrite2(usrSecHandler, UserSecCounter);
      }//end if            
}//end UserSecReceived

/** EOF usr_Buzzer.c ***************************************************************/
