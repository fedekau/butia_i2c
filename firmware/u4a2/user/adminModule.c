/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre	   27/03/07 	Original
 * Andres Aguirre 	   18/04/09     adding RESET
 * Andres Aguirre          22/03/12     Adding PnP support
 ********************************************************************/

#include "user/adminModule.h"
#include "user/pnp.h"
#include "user/usb4butia.h"
#include "handlerManager.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
//AM_PACKET adminDataPacket;
byte* sendBufferAdmin;
byte adminHandler;
word counter_big;
byte cantTicksW = 50;
byte keepAlive = TRUE;
byte timeOutTicksWatchdog;


/** USER MODULE REFERENCE *************************************************/
// Admin ModuleType=0,
//#pragma romdata user=DIRECTION_TABLE       // THIS DONT WORK!!!
#pragma romdata user
const uTab AdminModuleTable = {&adminModuleInit, &adminModuleRelease, "admin"}; //modName must be less or equal 8 characters
#pragma code

/*mapping between module name and an device type id used for optimization
 0 dist
 1 grises
 2 boton
 3 luz
 ....*/
/*byte* device_type_module_name_map[MAX_DEVICES];*/


/** P R I V A T E  P R O T O T Y P E S ***************************************/

/** D E C L A R A T I O N S **************************************************/
#pragma code sys

void Busy_eep_non_block() {
    byte j = 255;
    while (EECON1bits.WR && j-- > 0);
}

void Escribir_memoria_boot(void) {
    Busy_eep_non_block();
    Write_b_eep(ADDRESS_BOOT, BOOT_FLAG);
}


/*the device_type_module_name_map asociates for each string representing a module name an internal index
 for optimization propurses. Also this structure parses dynamically the name of the modules using rom data user*/

/*void device_type_module_name_map_popullate(void){
    byte userTableSize = 0;
    byte lineNumber;
    byte lineName[8]; //Se le cambio el tipo a byte, porque device_type_module_name_map es un arreglo de bytes
    userTableSize = getUserTableSize();
    for(lineNumber=0;lineNumber<userTableSize;lineNumber++){
        getModuleName(lineNumber, (char*)lineName);
        device_type_module_name_map[lineNumber]= lineName; 
    }
}
 */
void adminModuleInit(byte handler) {
    /*system initialization*/
    adminHandler = handler; //hardcode, the admin module allways respond at handler 0
    /*set the receive function for admin commands*/
    setHandlerReceiveFunction(adminHandler, &adminReceived);
    sendBufferAdmin = getSharedBuffer(adminHandler);
}

void adminModuleRelease(byte handler) {
    /*what? close admin? Are you crazy?*/
    return;
}

void goodByeCruelWorld(void) {
    //When resetting, make sure to drop the device off the bus
    //for a period of time. Helps when the device is suspended.
    UCONbits.USBEN = 0;
    counter_big = 0;
    while (--counter_big);
    Reset();
}

void adminReceived(byte* recBuffPtr, byte len, byte admin_handler) {
    byte adminCounter;
    byte endIn = nullEP, endOut = nullEP;
    byte userTableSize = 0;
    byte lineNumber = 0;
    char lineName[8];
    rom near char* tableDirec;
    pUserFunc dir;
    void (*pUser)(byte);
    byte handler, response;
    byte i;
    byte j;
    adminCounter = 0;

    switch (((AM_PACKET*) recBuffPtr)->CMD) {
        case GET_FIRMWARE_VERSION:
            ((AM_PACKET*) sendBufferAdmin)->CMD = GET_FIRMWARE_VERSION;
            ((AM_PACKET*) sendBufferAdmin)->size = FIRMWARE_VERSION;
            adminCounter = 0x02;
            break;

            /* Abre un user module, y retorna el handler asignado en el sistema*/
        case OPEN:
            tableDirec = getUserTableDirection(((AM_PACKET*) recBuffPtr)->moduleId);
            if(!existsTableEntry(tableDirec)){
                if (tableDirec != (rom near char*) ERROR) {
                    endIn = ((AM_PACKET*) recBuffPtr)->inEp;
                    handler = newHandlerTableEntry(endIn, tableDirec);
                    pUser = getModuleInitDirection(tableDirec);
                    pUser(handler); //hago el init ;)
                    ((AM_PACKET*) sendBufferAdmin)->handlerNumber = handler;
                } else {
                    ((AM_PACKET*) sendBufferAdmin)->handlerNumber = ERROR;
                }
            } else{
                ((AM_PACKET*)sendBufferAdmin)->handlerNumber = ERROR;
            }
            ((AM_PACKET*) sendBufferAdmin)->CMD = OPEN;
            adminCounter = 0x02; //1 byte para el campo CMD, otro para el handler
            break;

            /* Cierra un user module */
        case CLOSE:
            handler = ((AM_PACKET*) recBuffPtr)->handlerNumber;
            response = removeHandlerTableEntry(handler);
            ((AM_PACKET*) sendBufferAdmin)->response = response;
            ((AM_PACKET*) sendBufferAdmin)->CMD = CLOSE;
            adminCounter = 0x02; //1 byte para el campo CMD, otro para la respuesta
            break;

            /* Cierra todos los modulos */
        case INIT:
            //removeAllOpenModules(); called by bobot, at start, dont work whit autodetection!!!
            ((AM_PACKET*) sendBufferAdmin)->CMD = INIT;
            adminCounter = 0x01; //1 byte para el campo CMD
            break;

        case MESSAGE:
            // me limito a solamente mandar el paquete que me genera el usuario mediante sendMes (ping)
            adminCounter = sizeof (((AM_PACKET*) recBuffPtr));
            break;

        case LOAD:
            //Ver loaderModule.h
            //loadModule(byte idModule, byte* binaryStream);
            adminCounter = 0x01;
            break;

        case UNLOAD:
            adminCounter = 0x03;
            break;

            /* retorna la cantidad de modulos de usuarios presentes en el firmware */
        case GET_USER_MODULES_SIZE:
            userTableSize = getUserTableSize();
            ((AM_PACKET*) sendBufferAdmin)->CMD = GET_USER_MODULES_SIZE;
            ((AM_PACKET*) sendBufferAdmin)->size = userTableSize;
            adminCounter = 0x02;
            break;

            /* retorna el nombre correspondiente al modulo de usuario n-esimo*/
        case GET_USER_MODULES_LINE:
            ((AM_PACKET*) sendBufferAdmin)->CMD = GET_USER_MODULES_LINE;
            lineNumber = ((AM_PACKET*) recBuffPtr)->line;
            getModuleName(lineNumber, (char*) lineName);
            //memcpy(((AM_PACKET*)sendBufferAdmin)->lineName, lineName, 8); no anda, sera porque estan en espacios de memoria separados (RAM/ROM)?
            for (j = 0; j < 8; j++) {
                ((AM_PACKET*) sendBufferAdmin)->lineName[j] = lineName[j];
            }
            adminCounter = 0x09;
            break;

//        case CONFIGURE:
//            handler = ((AM_PACKET*) recBuffPtr)->handlerNumber;
//            response = configureHandlerTableEntry(handler);
//            ((AM_PACKET*) sendBufferAdmin)->response = response;
//            ((AM_PACKET*) sendBufferAdmin)->CMD = CONFIGURE;
//            adminCounter = 0x02; //1 byte para el campo CMD, otro para la respuesta
//            break;

        case BOOT:
            Escribir_memoria_boot();
            goodByeCruelWorld();
            adminCounter = 0x01; //;)
            break;

        case GET_HANDLER_SIZE:
            ((AM_PACKET*) sendBufferAdmin)->CMD = GET_HANDLER_SIZE;
            ((AM_PACKET*) sendBufferAdmin)->size = getMaxHandler();
            adminCounter = 0x02;
            break;

        case GET_HANDLER_TYPE:
            ((AM_PACKET*) sendBufferAdmin)->CMD = GET_HANDLER_TYPE;
            handler = ((AM_PACKET*) recBuffPtr)->size;
            handler = handler % MAX_HANDLERS; //sanity check
            if (epHandlerMap[handler].ep.empty == 0) {
                ((AM_PACKET*) sendBufferAdmin)->type = getModuleType(epHandlerMap[handler].uTableDirection);
            } else {
                ((AM_PACKET*) sendBufferAdmin)->type = NULLTYPE;
            };
            adminCounter = 0x02;
            break;

        case RESET:
            goodByeCruelWorld();
            adminCounter = 0x01; //1 byte para el campo CMD sensless ;)
            break;

        default:
            break;

    }//end switch()
    if (adminCounter != 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > 0); // probing a max of 255 times
        if (!mUSBGenTxIsBusy())
            USBGenWrite2(adminHandler, adminCounter);
    }//end if

}//end adminReceived

/* Not used*/
void sendMes(char* mensaje, byte len) {
    byte adminCounter, j;
    ((AM_PACKET*) sendBufferAdmin)->CMD = MESSAGE;
    for (j = 0; j < len; j++) {
        ((AM_PACKET*) sendBufferAdmin)->texto[j] = mensaje[j];
    }
    adminCounter = len + 1; //sizeof(adminDataPacket);
    if (!mUSBGenTxIsBusy())
        USBGenWrite2(adminHandler, adminCounter);
}

/*****************************************************************************
 * Keep Alive para el watchdog
 *****************************************************************************/

void watchdogKeepAlive(void) {
    keepAlive = TRUE;
}

/***********************************************************************
 *
 * Callback function to execute periodicaly by te Timmer interrupt ISR
 *
 ************************************************************************/

void watchdogEvent(void) {
    //    timeOutTicksWatchdog --;
    //    if(timeOutTicksWatchdog == 0){
    if (keepAlive) {
        //            timeOutTicksWatchdog = cantTicksW;
        keepAlive = FALSE;
    } else {
        goodByeCruelWorld();
    }
    //    }
    registerT0eventInEvent(TIME_UNIT_WATCHDOG, &watchdogEvent);
}

/*****************************************************************************
 * Start watchdog
 *****************************************************************************/

void watchdogStart(void) {
    keepAlive = TRUE;
    registerT0event(2 * TIME_UNIT_WATCHDOG, &watchdogEvent);
}

/*
void sendMes(char mensaje[8]){
        byte adminCounter, j;
        ((AM_PACKET*)sendBufferAdmin)->CMD = MESSAGE;
        for (j = 0; j < 8; j++){
                ((AM_PACKET*)sendBufferAdmin)->texto[j] = mensaje[j];
        }
        adminCounter = 9; //sizeof(adminDataPacket);
    if(!mUSBGenTxIsBusy())
        USBGenWrite2(adminHandler,sendBufferAdmin,adminCounter);
}*/

/** EOF adminModule.c ***************************************************************/


