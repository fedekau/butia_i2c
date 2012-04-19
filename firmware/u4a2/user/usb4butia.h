/******************************************************************************/
/*Autor: Aylen Ricca, Andres Aguirre, John Pereira                            */
/*Autor: 12/04/2012                                                           */
/******************************************************************************/

#ifndef USB4BUTIA_H
#define USB4BUTIA_H

#include <p18cxxx.h>
#include "typedefs.h"

#define MAX_PORTS 6
#define DISCONECTED 0

/*#define MAX_TYPE_SENSORS 5
#define MAX_SENSOR_TABLE_ATRIBUTE 2*/




typedef enum _direction {
    _OUT = 0,
    _IN = 1
} direction;

/*structure to describe a USB4butia port*/
typedef struct _port_descriptor{
    byte (*get_data_digital) (void); /*get data of pin from a port, digital*/
    WORD (*get_data_analog) (void); /*get data of pin from a port, analog*/ /*NEED IMPLEMENTATION*/
    void (*set_data) (byte); /*set data of pin in a port, digital*/
    WORD (*get_val_detection_pin)(void); /*pic pin used to identify the connected device*/
    void (*change_port_direction) (direction);/*callback function to change port direction*/
} port_descriptor;

/*mapping between idPort and the port descriptor*/
extern port_descriptor board_ports[MAX_PORTS];

/*******************************************************************************/
/*Struct that contain Artibutes of sensors types*/
/*typedef struct _sensorType{
    byte analogic;
    WORD resValue;
} sensorType;

/*Array of sensorsTypes, here have alla information about sensors types matched to SensorType ID*/
/*typedef sensorType sensorsTable[MAX_TYPE_SENSORS];
*/
/*Here we define the range of resistence*/
/*sensorsTable st;*/

/*void initSensorsTable(void);*/

byte get_device_type(WORD resistValue);


/****************************************/

/*------------ Port 1 ------------------*/
void changeDirectionPort1(direction io);

byte getData1();

void setData1(byte data);

WORD getDetectionPinValue1(void);

/*------------ Port 2 ------------------*/
void changeDirectionPort2(direction io);

byte getData2();

void setData2(byte data);

WORD getDetectionPinValue2(void);

/*------------ Port 3 ------------------*/
void changeDirectionPort3(direction io);

byte getData3();

void setData3(byte data);

WORD getDetectionPinValue3(void);

/*------------ Port 4 ------------------*/
void changeDirectionPort4(direction io);

byte getData4();

void setData4(byte data);

WORD getDetectionPinValue4(void);

/*------------ Port 5 ------------------*/
void changeDirectionPort5(direction io);

byte getData5();

void setData5(byte data);

WORD getDetectionPinValue5(void);

/*------------ Port 6 ------------------*/
void changeDirectionPort6(direction io);

byte getData6();

void setData6(byte data);

WORD getDetectionPinValue6(void);

/******************************************************************************/


const port_descriptor * getBoardPortDescriptor(byte port);


const port_descriptor * getPortDescriptor(byte handler_id);

#endif // USB4BUTIA_H
