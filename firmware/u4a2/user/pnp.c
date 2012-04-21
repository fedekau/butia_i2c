#include "pnp.h"
#include "handlerManager.h"
#include "loaderModule.h"

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
#pragma code module

void initTableDetectedDevice(void){
    byte aux;
    for (aux=0; aux < MAX_PORTS ; aux++) detected_device_type_id[aux]= DISCONECTED;
}

byte get_device_type(WORD resistValue){

    byte i = 0;
    while(!((resistValue.v[0]== table_device_id_resistance[i].resValue.v[0]) && (resistValue.v[1]== table_device_id_resistance[i].resValue.v[1]) ) && (i < MAX_DEVICES)) i++ ;/*Need FIX when when range be define , need it compare to a range*/

    return i; /*if i = MAX_DEVICES that mean error happend*/
}

void openPnP(byte moduleId[8], byte handler){
    void (*pUser)(byte);
    pUserFunc dir;
    rom near char* tableDirec;
    tableDirec = getUserTableDirection(moduleId);
    dir = getModuleInitDirection(tableDirec);
    if((byte)dir != ERROR){
            handler = newHandlerTableEntryForcingHandler(getPnPEndpoint(), tableDirec, handler);
            pUser = dir;
            pUser(handler); //hago el init ;)
    }
}

void closePnP(byte handler){
    removeHandlerTableEntry(handler);
}

void hotplug_pnp(void){
    byte port, device_type;
    for(port=1;port<=MAX_PORTS;port++){
//        device_type = get_device_type(board_ports[port].get_val_detection_pin());
//        if(device_type!=detected_device_type_id[port]){ /*Change that board_port[device_type].detected_device_id for detected_device_type_id[port]*/
//            if(device_type==DISCONECTED){
//                board_ports[port].change_port_direction(IN);
                /*CALL a close command*/
//                closePnP(port);

//            }else{
                /*CALL a open comand*/
                /*openPnP(table_device_id_resistance_value[device_type].name,port); /*in table_device_id_resistance_value are defined all device types with the resistance value*/


//            }
   //         detected_device_type_id[port] = device_type; /*Change that board_port[device_type].detected_device_id for detected_device_type_id[port]*/

//   }

        //do detection
        //open new connected modules with openPNP
        //close disconnected modules with closePNP
    }
 //   registerT0eventInEvent(PNP_DETECTION_TIME, &hotplug_pnp);


}

