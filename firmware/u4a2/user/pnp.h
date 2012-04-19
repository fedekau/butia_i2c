/*******************************************************************************/
#ifndef PNP__H
#define PNP__H

#include "typedefs.h"
#include "user/usb4butia.h"
/*******************************************************************************/


/*Sensors*/
#define R_BOTON 700
#define R_GRISES 700
#define R_DIST 700
#define R_LUZ 700
#define R_ACCELEROMETER 700
#define R_PRECION
#define R_TEMPERATURE 700
#define R_MAGNETIC 700
#define R_MICROPHONE 700
#define R_TILT 700
#define R_VIBRATION 700
#define R_POTENTIOMETER 700
#define R_CAMERA 700
#define R_MOTION 700
/*Actuators*/
#define R_DCMOTOR 700
#define R_RELAY 700
#define R_LED 700
#define R_BUZZER 700


#define MAX_DEVICES 9 /*Max cant of senssor/actuator type*/

/** ESTRUCTURES **/

typedef struct _device_resistance {
    char name[8];/*name of the string*/
    WORD resValue;/*5v = 1023*/
}  device_resistance;

typedef struct _port_device_detected {
    int a;

} port_device_detected;

extern byte detected_device_type_id[];

/*Remember to change the old maping for that*/
extern rom device_resistance table_device_id_resistance[];


#endif //PNP__H