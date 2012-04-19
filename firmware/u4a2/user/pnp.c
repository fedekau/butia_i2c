#include "user/pnp.h"






/** VARIABLES INITIALIZED, CONST ROM **/
rom device_resistance table_device_id_resistance[4] = {
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

byte get_device_type(WORD resistValue){

    byte i = 0;
    while(!((resistValue.v[0]== table_device_id_resistance[i].resValue.v[0]) && (resistValue.v[1]== table_device_id_resistance[i].resValue.v[1]) ) && (i < MAX_DEVICES)) i++ ;/*Need FIX when when range be define , need it compare to a range*/

    return i; /*if i = MAX_DEVICES that mean error happend*/
}
