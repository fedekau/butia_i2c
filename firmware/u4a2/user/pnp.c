#include "user/pnp.h"
#include "usb4butia.h"



/** ESTRUCTURES **/

typedef struct _device_resistance {
    char name[8];/*name of the string*/
    WORD resValue;/*5v = 1023*/
}  device_resistance;

typedef struct _port_device_detected {
    int a;

} port_device_detected;

/** VARIABLES INITIALIZED, CONST ROM **/
rom const device_resistance table_device_resistance[4] = {
    { "boton"  , R_BOTON  },
    { "grises" , R_GRISES },
    { "dist"   , R_DIST   },
    { "TODO"   , R_DIST   }
};

/** VARIABLES UNINITIALIZED, RAM **/
#pragma udata
byte detected_device_type_id[MAX_PORTS]; /*the device_type_id of the device connected*/



/* CODE */
#pragma code

void initTableDetectedDevice(void){
    byte aux;
    for (aux=0; aux < MAX_PORTS ; aux++) detected_device_type_id[aux]= DISCONECTED;
}

