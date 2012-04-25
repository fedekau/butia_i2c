/*******************************************************************************/
#ifndef PNP__H
#define PNP__H

#include "typedefs.h"
#include "user/usb4butia.h"
/*******************************************************************************/


/*Sensors*/
#define R_BOTON_MIN 922
#define R_BOTON_MAX 939
#define R_GRISES_MIN 878
#define R_GRISES_MAX 901
#define R_DIST_MIN 824
#define R_DIST_MAX 854

#define R_LUZ 9999
#define R_ACCELEROMETER 9999
#define R_PRECION
#define R_TEMPERATURE 9999
#define R_MAGNETIC 9999
#define R_MICROPHONE 9999
#define R_TILT 9999
#define R_VIBRATION 9999
#define R_POTENTIOMETER 9999
#define R_CAMERA 9999
#define R_MOTION 9999
/*Actuators*/
#define R_DCMOTOR 9999
#define R_RELAY 9999
#define R_LED 9999
#define R_BUZZER 9999


#define MAX_DEVICES 9 /*Max cant of senssor/actuator type*/
/*TODO review this time, the micro is running @20MHZ with a pipeline of 4steps => 20000000/4 = 5000000 instructions per second */
#define PNP_DETECTION_TIME 10000


/** ESTRUCTURES **/

typedef struct _device_resistance {
    char name[8];/*name of the string*/
    WORD resValue_min;/*5v = 1023*/
    WORD resValue_max;/*5v = 1023*/
}  device_resistance;

typedef struct _port_device_detected {
    int a;

} port_device_detected;

extern byte detected_device_type_id[];

/*Remember to change the old maping for that*/
extern rom device_resistance table_device_id_resistance[];


#endif //PNP__H