/* Author                                                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre, Edgardo Vaz, Santiago Reyes
 *****************************************************************************/
 
/* Modulo para guardar en memoria EEPROM del microcontrolador. Notar que aunque
se desconecte la alimentacion del dispositivo, los datos van a seguir estando
guardados en la EEPROM */ 

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/handlerManager.h"
#include "user/usr_eeprom.h"
#include "user/adminModule.h"

  
/** V A R I A B L E S ********************************************************/
#pragma udata 


byte* sendBufferUsrEeprom;  // buffer to send data


/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserEepromInit(byte handler);
void UserEepromReceived(byte*, byte, byte);
void UserEepromRelease(byte handler);



// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab UserEepromModuleTable = {&UserEepromInit,&UserEepromRelease,"eeprom"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module


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

void UserEepromInit(byte handler){
    
    setHandlerReceiveFunction(handler, &UserEepromReceived);
    sendBufferUsrEeprom = getSharedBuffer(handler);

}


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

void UserEepromRelease(byte handler){
    unsetHandlerReceiveBuffer(handler);
    unsetHandlerReceiveFunction(handler);
}

/******************************************************************************
 * Function:        write_eeprom(unsigned int address, unsigned char data)
 *
 * PreCondition:    None
 *
 * Input:           Direccion y valor
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

void write_eeprom(unsigned int address, unsigned char data) {
    Busy_eep_non_block();
    Write_b_eep(address, data);
}

/******************************************************************************
 * Function:        read_eeprom(unsigned int address)
 *
 * PreCondition:    None
 *
 * Input:           Direccion
 *
 * Output:          Valor de memoria en esa direccion
 *
 * Side Effects:    None
 *
 * Overview:        Lee un valor desde un lugar especifico de la eeprom     
 *
 * Note:            None
 *****************************************************************************/
unsigned char read_eeprom(unsigned int address){
    Busy_eep_non_block(); 
    return Read_b_eep(address);
}


/******************************************************************************
 * Function:        UserSecReceived(byte* recBuffPtr, byte len, byte handler)
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

void UserEepromReceived(byte* recBuffPtr, byte len, byte handler){
      
    byte UserEepromCounter = 0;
    unsigned int address;
    unsigned char data;
    
    switch(((EEPROM_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
            ((EEPROM_DATA_PACKET*)sendBufferUsrEeprom)->_byte[0] = ((EEPROM_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            ((EEPROM_DATA_PACKET*)sendBufferUsrEeprom)->_byte[1] = EEPROM_MINOR_VERSION;
            ((EEPROM_DATA_PACKET*)sendBufferUsrEeprom)->_byte[2] = EEPROM_MAJOR_VERSION;
            UserEepromCounter = 0x03;
            break;  

        case WRITE:
            ((EEPROM_DATA_PACKET*)sendBufferUsrEeprom)->_byte[0] = ((EEPROM_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            address = ((EEPROM_DATA_PACKET*)recBuffPtr)->_byte[1];
            data = ((EEPROM_DATA_PACKET*)recBuffPtr)->_byte[2];
            write_eeprom(address, data);
            UserEepromCounter = 0x01;
            break;  

        case READ:
            ((EEPROM_DATA_PACKET*)sendBufferUsrEeprom)->_byte[0] = ((EEPROM_DATA_PACKET*)recBuffPtr)->_byte[0];
            address = ((EEPROM_DATA_PACKET*)recBuffPtr)->_byte[1];
            ((EEPROM_DATA_PACKET*)sendBufferUsrEeprom)->_byte[1] = read_eeprom(address);
            UserEepromCounter=0x02;
            break; 
 
        case RESET:
            Reset();
            break;
          
        default:
            break;
 
      }//end switch(s)

    USBGenWrite2(handler, UserEepromCounter);
                
}//end UserSecReceived

/** EOF usr_Buzzer.c ***************************************************************/
