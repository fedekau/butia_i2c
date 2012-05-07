/*******************************************************************************/
#ifndef PNP__H
#define PNP__H

#include "typedefs.h"
#include "user/usb4butia.h"
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"
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
extern rom const device_resistance table_device_id_resistance[];

#define PNP_MINOR_VERSION 0xff //FIXME
#define PNP_MAJOR_VERSION 0xff //FIXME


typedef union PNP_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        {
            READ_VERSION    = 0x00,
            GET_RES         = 0x01
        } CMD;
        byte len;
    };
    struct
    {
        unsigned :8;
        byte ID;
    };
    struct
    {
        unsigned :8;
        byte higth;
        byte low;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} PNP_DATA_PACKET;


/** FUNCTIONS ****/
void PNPInit(byte handler);
void hotplug_pnp(void);
void openPnP(byte moduleId[8], byte handler);



#endif //PNP__H