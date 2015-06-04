#include "pnp.h"
#include "handlerManager.h"
#include "loaderModule.h"
#include "user/usr_motors.h"

#pragma code sys

/** VARIABLES INITIALIZED, CONST ROM **/
rom const device_resistance table_device_id_resistance[MAX_DEVICES] = {
    { "port", R_PORT_MIN, R_PORT_MAX},
    { "light", R_LIGHT_MIN, R_LIGHT_MAX},
    { "button", R_BOTON_MIN, R_BOTON_MAX},
    { "grey", R_GREY_MIN, R_GREY_MAX},
    { "distanc", R_DIST_MIN, R_DIST_MAX},
    { "volt", R_VOLT_MIN, R_VOLT_MAX},
    { "res", R_RES_MIN, R_RES_MAX},
    { "modSenA", R_MOD_SEN_A_MIN, R_MOD_SEN_A_MAX},
    { "modSenB", R_MOD_SEN_B_MIN, R_MOD_SEN_B_MAX},
    { "modSenC", R_MOD_SEN_C_MIN, R_MOD_SEN_C_MAX},
    { "modActA", R_MOD_ACT_A_MIN, R_MOD_ACT_A_MAX},
    { "modActB", R_MOD_ACT_B_MIN, R_MOD_ACT_B_MAX},
    { "modActC", R_MOD_ACT_C_MIN, R_MOD_ACT_C_MAX},
    { "buzzer", R_MOD_BUZZER_MIN, R_MOD_BUZZER_MAX},
    { "relay", R_MOD_RELAY_MIN, R_MOD_RELAY_MAX}
};

/** VARIABLES UNINITIALIZED, RAM **/
#pragma udata
byte PNPHandler = 0;
byte* sendBufferPNP; // buffer to send data
byte detected_device_type_id[MAX_PORTS]; /*the device_type_id of the device connected*/
endpoint pnpEndpoint;


/** P R I V A T E  P R O T O T Y P E S ***************************************/
void PNPInit(byte i);
void PNPReceived(byte*, byte, byte);
void PNPRelease(byte i);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab PNPModuleTable = {&PNPInit, &PNPRelease, "pnp"};
#pragma code

/* CODE */
#pragma code module

void initTableDetectedDevice(void) {
    byte aux;
    for (aux = 0; aux < MAX_PORTS; aux++) detected_device_type_id[aux] = DISCONECTED;
}

void PNPInit(byte i) {
    byte modulename[8];
    byte aux;

    if (PNPHandler) return;
    PNPHandler = i;
    // add my receive function to the handler module, to be called automatically when the pc sends data to the user module
    setHandlerReceiveFunction(PNPHandler, &PNPReceived);
    // initialize the send buffer, used to send data to the PC
    sendBufferPNP = getSharedBuffer(PNPHandler);
    pnpEndpoint = getPnPEndpoint();
    if (getMotorType() == MOTORS_SHIELD_CC) {
        initPorts(1);
    } else {
        initPorts(0);
    }
    initTableDetectedDevice(); //All Disconected

    modulename[0] = 'p';
    modulename[1] = 'o';
    modulename[2] = 'r';
    modulename[3] = 't';
    modulename[4] = 0;
    modulename[5] = 0;
    modulename[6] = 0;
    modulename[7] = 0;

    for (aux = 0; aux < MAX_PORTS; aux++) {
        openPnP(modulename, aux + 1);
    }

    //register the detection mecanism in the timmer interrupt
    registerT0event(PNP_DETECTION_TIME, &hotplug_pnp);

}//end PNPInit

void PNPRelease(byte i) {
    unsetHandlerReceiveBuffer(i);
    unsetHandlerReceiveFunction(i);
    unregisterT0event(&hotplug_pnp);
}

byte get_device_type(WORD resistValue) {
    byte i = 0;
    WORD MAX;
    WORD MIN;
    /*Search the read resistance value in the resistance range of devices defined*/
    for (i = 0; i < MAX_DEVICES; ++i) {
        MAX = table_device_id_resistance[i].resValue_max;
        MIN = table_device_id_resistance[i].resValue_min;
        if ((resistValue._word <= MAX._word) && (MIN._word <= resistValue._word)) return i;
    }
    return DISCONECTED; // 0 = "port" device
}

void openPnP(byte moduleId[8], byte handler) {
    void (*pUser)(byte);
    rom near char* tableDirec;
    tableDirec = getUserTableDirection(moduleId);
    if (tableDirec != (rom near char*) ERROR) {
        handler = newHandlerTableEntryForcingHandler(pnpEndpoint.endPoint, tableDirec, handler);
        pUser = getModuleInitDirection(tableDirec);
        pUser(handler); //hago el init ;)
    }
}

void closePnP(byte handler) {
    removeHandlerTableEntry(handler);
}

void hotplug_pnp(void) {
    byte port, device_type;
    byte modulename[8];
    /*do detection*/
    for (port = 0; port < MAX_PORTS; port++) {
        device_type = get_device_type(board_ports[port].get_val_detection_pin());
        if (device_type != detected_device_type_id[port]) {
            closePnP(port + 1);
            // is this necessary or we can use table_devie.. directly ?
            modulename[0] = table_device_id_resistance[device_type].name[0];
            modulename[1] = table_device_id_resistance[device_type].name[1];
            modulename[2] = table_device_id_resistance[device_type].name[2];
            modulename[3] = table_device_id_resistance[device_type].name[3];
            modulename[4] = table_device_id_resistance[device_type].name[4];
            modulename[5] = table_device_id_resistance[device_type].name[5];
            modulename[6] = table_device_id_resistance[device_type].name[6];
            modulename[7] = table_device_id_resistance[device_type].name[7];
            openPnP(modulename, port + 1);
            detected_device_type_id[port] = device_type;
        }
    }
    registerT0eventInEvent(PNP_DETECTION_TIME, &hotplug_pnp);
}


//This is a internal module model as a user module, so this command are for testing purpouse only

void PNPReceived(byte* recBuffPtr, byte len, byte handler) {
    byte userPNPCounter = 0;

    switch (((PNP_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((PNP_DATA_PACKET*) sendBufferPNP)->_byte[0] = ((PNP_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((PNP_DATA_PACKET*) sendBufferPNP)->_byte[1] = PNP_MINOR_VERSION;
            ((PNP_DATA_PACKET*) sendBufferPNP)->_byte[2] = PNP_MAJOR_VERSION;
            userPNPCounter = 0x03;
            break;

        default:
            break;
    }

    USBGenWrite2(PNPHandler, userPNPCounter);

}//end PNPReceived


