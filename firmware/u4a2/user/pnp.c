#include "pnp.h"
#include "handlerManager.h"
#include "loaderModule.h"

/** VARIABLES INITIALIZED, CONST ROM **/
rom const device_resistance table_device_id_resistance[MAX_DEVICES] = {
    { "port"   , 0, 255     },
    { "button"  , 31207 ,34492 },
    { "grey" , 59041, 60124 },
    { "dist"   , 37491, 40654 },
    { "gpio"   , R_GPIO_MIN, R_GPIO_MAX    }
};

#pragma udata 
byte PNPHandler;
byte* sendBufferPNP; // buffer to send data


/** P R I V A T E  P R O T O T Y P E S ***************************************/
void PNPProcessIO(void);
void PNPInit(byte i);
void PNPReceived(byte*, byte, byte);
void PNPRelease(byte i);
void PNPConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab PNPModuleTable = {&PNPInit,&PNPRelease,&PNPConfigure,"pnp"}; //modName must be less or equal 8 characters
#pragma code


/** VARIABLES UNINITIALIZED, RAM **/
#pragma udata
byte detected_device_type_id[MAX_PORTS]; /*the device_type_id of the device connected*/
endpoint pnpEndpoint;
/* CODE */
#pragma code module

void initTableDetectedDevice(void){
    byte aux;
    for (aux=0; aux < MAX_PORTS ; aux++) detected_device_type_id[aux]= DISCONECTED;
}


void PNPInit(byte i){
    byte modulename[8];
    BOOL res;

    PNPHandler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(PNPHandler,&PNPReceived);
    // add my receive pooling function to the dynamic pooling module, to be called periodically
    //res = addPollingFunction(&UserPNPProcessIO);
    // initialize the send buffer, used to send data to the PC
    sendBufferPNP = getSharedBuffer(PNPHandler);
    pnpEndpoint= getPnPEndpoint();

    initPorts(); //USB4butia init port
    initTableDetectedDevice(); //All Disconected

    modulename[0]='p'; modulename[1]='o'; modulename[2]='r'; modulename[3]='t';
    modulename[4]=0; modulename[5]=0  ; modulename[6]=0  ; modulename[7]=0  ;

    openPnP(modulename,1);
    openPnP(modulename,2);
    openPnP(modulename,3);
    openPnP(modulename,4);
    openPnP(modulename,5);
    openPnP(modulename,6);

    //register the detection mecanism in the timmer interrupt
    registerT0event(PNP_DETECTION_TIME, &hotplug_pnp);

}//end PNPInit




void PNPRelease(byte i){
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    //removePoolingFunction(&UserPNPProcessIO);
    unregisterT0event(&hotplug_pnp);
}


void PNPConfigure(void){
// Do the configuration
}



byte get_device_type(WORD resistValue){
    byte i = 0;
    WORD MAX;
    WORD MIN;
    /*Search the read resistance value in the resistance range of devices defined*/
    for (i=0 ; i < MAX_DEVICES ; ++i) {
        MAX = table_device_id_resistance[i].resValue_max;
        MIN = table_device_id_resistance[i].resValue_min;
        if ( (resistValue._word <= MAX._word) && (MIN._word <= resistValue._word) ) return i;
    }

    return DISCONECTED; // 0 = "port" device
}

void openPnP(byte moduleId[8], byte handler){
    void (*pUser)(byte);
    rom near char* tableDirec;
    tableDirec = getUserTableDirection(moduleId);

    if(tableDirec != (rom near char*)ERROR){
            handler = newHandlerTableEntryForcingHandler( pnpEndpoint.endPoint, tableDirec, handler);
            pUser = getModuleInitDirection(tableDirec);
            pUser(handler); //hago el init ;)
    }
}

void closePnP(byte handler){
    removeHandlerTableEntry(handler);
}


void hotplug_pnp(void){
    byte port, device_type;
    char modulename[8];
    /*do detection*/
    for(port=0;port<MAX_PORTS;port++){
        device_type = get_device_type(board_ports[port].get_val_detection_pin());
        if(device_type!=detected_device_type_id[port]){
            // Change that board_port[device_type].detected_device_id for detected_device_type_id[port]
            closePnP(port+1);

            modulename[0]=table_device_id_resistance[device_type].name[0];
            modulename[1]=table_device_id_resistance[device_type].name[1];
            modulename[2]=table_device_id_resistance[device_type].name[2];
            modulename[3]=table_device_id_resistance[device_type].name[3];
            modulename[4]=table_device_id_resistance[device_type].name[4];
            modulename[5]=table_device_id_resistance[device_type].name[5];
            modulename[6]=table_device_id_resistance[device_type].name[6];
            modulename[7]=table_device_id_resistance[device_type].name[7];

            openPnP(modulename, port+1); /*in table_device_id_resistance_value are defined all device types with the resistance value*/
            detected_device_type_id[port] = device_type;
        }
    }
    registerT0eventInEvent(PNP_DETECTION_TIME, &hotplug_pnp);
}


//This is a internal module model as a user module, so this command are for testing purpouse only
void PNPReceived(byte* recBuffPtr, byte len, byte handler){
       byte index;
      byte userPNPCounter = 0;
      switch(((PNP_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
              //dataPacket._byte[1] is len
            ((PNP_DATA_PACKET*)sendBufferPNP)->_byte[0] = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[0];
	        ((PNP_DATA_PACKET*)sendBufferPNP)->_byte[1] = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[1];
            ((PNP_DATA_PACKET*)sendBufferPNP)->_byte[2] = PNP_MINOR_VERSION;
            ((PNP_DATA_PACKET*)sendBufferPNP)->_byte[3] = PNP_MAJOR_VERSION;
            userPNPCounter = 0x04;
        break;
      }
      if(userPNPCounter != 0)
      {
          if(!mUSBGenTxIsBusy())
              USBGenWrite2(PNPHandler, userPNPCounter);
      }//end if
}//end PNPReceived


