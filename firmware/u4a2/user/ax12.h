#ifndef __AX12_H 
#define __AX12_H 

/****************************************************************************** 
* Nombre: ax12.h 
* Tipo:   HEADER
* Uso:    Librer�a para el control de los servos Dynamixel AX-12.
******************************************************************************* 
* Microcontrolador: 18f4550
* Compildador:      C18
******************************************************************************* 
* Observaciones:
*         1)Librer�a creada a partir de la Datasheet del servo Dynamixel AX-12.
*           Incluye todas las direcciones tanto las que est�n en EEPROM como en
*           RAM, instrucciones y constantes.
*
*         2)La librer�a puede ser modificada para ser utilizada por otro
*           microcontrolador. Se debe modificar "#include <p18f4550.h>" por el 
*           nuevo HEADER. NOTA: El cambio de microcontrolador puede implicar
*           modificaciones en funciones utilizadas en �sta librer�a.
*
******************************************************************************* 
* Creada por:           Andr�s Aguirre | Kenji Nakasone
*                                PROYECTO BUT�A
*                             Fac. de ING | UDELAR
******************************************************************************* 
* Fecha: 09|06|2010
* Versi�n: 1.0
* Errores y sugerencias: 
******************************************************************************/ 
   
     //Includes
    #include <p18f4550.h>                   //PIC184550
#include "../typedefs.h"

/*****************************************************************************/ 
/**************************    Tabla de direcciones   ************************/
/*****************************    del servo Ax-12  ***************************/
/*****************************************************************************/       
    //EEPROM                        //HEX   //DEC
    #define MODEL_NUMBER_L          0X00    //00
    #define MODEL_NUMBER_H          0X01    //01
    #define VERSION_FIRMWARE        0X02    //02
    #define BUSID                   0x03    //03
    #define BAUD_RATE               0x04    //04
    #define RETURN_DELAY            0x05    //05
    #define CW_ANGLELIMIT_L         0x06    //06
    #define CW_ANGLELIMIT_H         0x07    //07
    #define CCW_ANGLELIMIT_L        0x08    //08
    #define CCW_ANGLELIMIT_H        0x09    //09
            /* RESERVADA */                 //10    
    #define LIMIT_TEMPERATURE       0x0B    //11
    #define LOWEST_LIMIT_VOLT       0x0C    //12
    #define HIGHEST_LIMIT_VOLT      0x0D    //13
    #define MAX_TORQUE_L            0x0E    //14
    #define MAX_TORQUE_H            0x0F    //15
    #define STATUS_RETURN           0x10    //16
    #define ALARM_LED               0x11    //17
    #define ALARM_SHUTDOWN          0x12    //18
            /* RESERVADA */                 //19
    #define DOWN_CALIBRATION_L      0x14    //20
    #define DOWN_CALIBRATION_H      0x15    //21
    #define UP_CALIBRATION_L        0x16    //23
    #define UP_CALIBRATION_H        0x17    //24

    //RAM                           //HEX   //DEC
    #define TORQUE_ENABLE           0x18    //24
    #define LED                 	0x19    //25
    #define CW_COMPLIANCE_MARGIN    0x1A    //26
    #define CCW_COMPLIANCE_MARGIN   0x1B    //27
    #define CW_COMPLIANCE_SLOPE     0x1C    //28
    #define CCW_COMPLIANCE_SLOPE    0x1D    //29
    #define GOAL_POSITION_L         0x1E    //30
    #define GOAL_POSITION_H         0x1F    //31
    #define MOVING_SPEED_L          0x20    //32
    #define MOVING_SPEED_H          0x21    //33
    #define TORQUE_LIMIT_L          0x22    //34
    #define TORQUE_LIMIT_H          0x23    //35
    #define PRESENT_POSITION_L      0x24    //36
    #define PRESENT_POSITION_H      0x25    //37
    #define PRESENT_SPEED_L         0x26    //38
    #define PRESENT_SPEED_H         0x27    //39
    #define PRESENT_LOAD_L          0x28    //40
    #define PRESENT_LOAD_H          0x29    //41
    #define PRESENT_VOLTAGE         0x2A    //42
    #define PRESENT_TEMPERATURE     0x2B    //43
    #define REGISTERED_INST         0x2C    //44
            /* RESERVADA */                 //45 
    #define MOVING                  0x2E    //46
    #define LOCK                    0x2F    //47
    #define PUNCH_L                 0x30    //48
    #define PUNCH_H                 0x31    //49

    #define MAXPAQSIZE              0x10
/*****************************************************************************/ 
/**************************   Set de Instrucciones   *************************/
/*****************************    del servo Ax-12   **************************/
/*****************************************************************************/ 
                                    //HEX   //DEC
    #define PING                    0x01    //01
    #define READ_DATA               0x02    //02 
    #define WRITE_DATA              0x03    //03 
    #define REG_WRITE               0x04    //04     
    #define ACTION                  0x05    //05
    #define RESET_AX12              0x06    //06
    #define SYNC_WRITE              0x83    //131 

/*****************************************************************************/ 
/**************************   Constantes Auxiliares   ************************/
/*****************************************************************************/ 
                                    //HEX   //DEC
    #define BRODCAST	 	        0xFE    //254
    #define AX12_MAX_SERVOS         0x12    //18
    #define AX12_BUFFER_SIZE        0x20    //32

/*****************************************************************************/ 
/***************************   Definici�n de Tipos   *************************/
/*****************************************************************************/ 
//    typedef unsigned char byte;
    typedef unsigned char boolean;


/*****************************************************************************/ 
/*************************   Prototipos de Funciones   ***********************/
/*********************    Funciones utilizadas en ax12.c   *******************/
/*****************************************************************************/ 
    //Funciones Auxiliares para la implementaci�n del Half-Duplex
    void setTX(void);
    void setRX(void);
    void setNone(void);
//    void autoDetect (int* list_motors, byte num_motors);

    //Configuraci�n de la USART
    void ax12InitSerial(void);

    //Funciones de Transmisi�n y Recepci�n
    byte ax12writeB(byte data);
    void ax12SendPacket (byte id, byte datalength, byte instruction, byte* data);
    byte ax12ReadPacket (int* status_id, int* status_error, int* status_data);

    //Funciones de control del Ax-12 
    byte ping ();
    byte reset (byte id);
    byte readData (byte id, byte regstart, byte reglength);
    byte writeData (byte id,byte regstart, byte reglength, byte *values);
    byte action ();
    byte regWrite (byte regstart, byte reglength, int value);
    byte readInfo (byte regstart);
    byte writeInfo (byte id,byte regstart, int value);
    void setEndlessTurnMode (byte id,boolean onoff);
    void endlessTurn (byte id, int velocidad, byte inverse  );
    byte presentPSL (boolean inverse, byte id, int* PSL);

    //Funciones auxiliares
    boolean sign2bin (int numero);
    char bin2sign (boolean var);
    int makeInt (byte l, byte h);
    byte highByte(int value);

    #define abs(a) ((a<0) ? -a : a)
    //ISR
    void isr_RX(void);

    
#endif 