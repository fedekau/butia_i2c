/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre	   27/03/07 	Original
 * Andres Aguirre 	   18/04/09     Se agrega el RESET
 ********************************************************************/

#include "user/adminModule.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
//AM_PACKET adminDataPacket;
byte* sendBufferAdmin;
byte adminHandler;
word counter_big;
byte  cantTicksW    = 50;  
byte  keepAlive    = TRUE;
byte  timeOutTicksWatchdog;

/*mapping between idPort and the port descriptor*/
port_descriptor* board_ports[MAX_PORTS];


/*mapping between module name and an device type id used for optimization
 0 dist
 1 grises
 2 boton
 3 luz
 ....*/
byte* device_type_module_name_map[MAX_DEVICES];


/*TODO review this time, the micro is running @20MHZ with a pipeline of 4steps => 20000000/4 = 5000000 instructions per second */
#define PNP_DETECTION_TIME 10000

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void openPnP(byte moduleId[8], byte inEp);
/** D E C L A R A T I O N S **************************************************/
#pragma code sys

void Busy_eep_non_block ( void ){
    byte j = 255;
    while(EECON1bits.WR && j-->0);
}

void Escribir_memoria_boot(void){
    Busy_eep_non_block();
    Write_b_eep(ADDRESS_BOOT,BOOT_FLAG);
}

void hotplug_pnp(void){
    byte port, device_type;
    for(port=1;port<=MAX_PORTS;port++){
        device_type = get_device_type(board_ports[port]->detection_pin);
        if(device_type!=board_ports[port]){
            if(device_type==DISCONECTED){
                //CALL a close command
            }else{
                //CALL a open comand
                openPnP(device_type_module_name_map[device_type],port);

            }
            board_ports[port]->detected_device_type_id = device_type;
        }
        
        //do detection
        //open new connected modules with openPNP
        //close disconnected modules with closePNP
    }
    registerT0eventInEvent(PNP_DETECTION_TIME, &hotplug_pnp);
}

void board_ports_popullate(void){
    byte port;
    for(port=1;port<=MAX_PORTS;port++){
        board_ports[port]=getBoardPortDescriptor(port);
    }
}

void device_type_module_name_map_popullate(void){

}

void adminModuleInit(void){
	/*system initialization*/
	adminHandler=0; //hardcode, the admin module allways respond at handler 0
        /*set the receive function for admin commands*/
	setHandlerReceiveFunction(adminHandler,&adminReceived);
	sendBufferAdmin = getSharedBuffer(adminHandler);
        board_ports_popullate();
        device_type_module_name_map_popullate();
        registerT0event(PNP_DETECTION_TIME, &hotplug_pnp);
}

void goodByeCruelWorld(void){
    //When resetting, make sure to drop the device off the bus
    //for a period of time. Helps when the device is suspended.
    UCONbits.USBEN = 0;
    counter_big = 0;
    while(--counter_big);
    Reset();
}

void openPnP(byte moduleId[8], byte inEp){
    byte handler;
    void (*pUser)(byte);
    pUserFunc dir;
    rom near char* tableDirec;;
    tableDirec = getUserTableDirection(moduleId);
    dir = getModuleInitDirection(tableDirec);
    if((byte)dir != ERROR){
            handler = newHandlerTableEntryPNP(inEp,tableDirec);
            pUser = dir;
            pUser(handler); //hago el init ;)            
    }
}

void adminReceived(byte* recBuffPtr,byte len){
	byte adminCounter;
	byte endIn = nullEP, endOut = nullEP;
	byte userTableSize = 0;
	byte lineNumber = 0;
	char lineName[8];
	rom near char* tableDirec;
	pUserFunc dir;	
	void (*pUser)(byte);
	byte handler, response;
	byte j;
	adminCounter = 0;
	switch(((AM_PACKET*)recBuffPtr)->CMD){
	/* Abre un user module, y retorna el handler asignado en el sistema*/
	case OPEN:
		tableDirec = getUserTableDirection(((AM_PACKET*)recBuffPtr)->moduleId);
                dir = getModuleInitDirection(tableDirec);
                if((byte)dir != ERROR){
                        endIn = ((AM_PACKET*)recBuffPtr)->inEp;
                        handler = newHandlerTableEntry(endIn,tableDirec);
                        pUser = dir;
                        pUser(handler); //hago el init ;)
                        ((AM_PACKET*)sendBufferAdmin)->handlerNumber = handler;
                }else{
                        ((AM_PACKET*)sendBufferAdmin)->handlerNumber = ERROR;
                }
              	((AM_PACKET*)sendBufferAdmin)->CMD = OPEN;
		adminCounter=0x02; //1 byte para el campo CMD, otro para el handler 	
	break;

	/* Cierra un user module */
	case CLOSE:
		handler  = ((AM_PACKET*)recBuffPtr)->handlerNumber;
		response = removeHandlerTableEntry(handler);	
		((AM_PACKET*)sendBufferAdmin)->response = response;
		((AM_PACKET*)sendBufferAdmin)->CMD = CLOSE; 
		adminCounter = 0x02; //1 byte para el campo CMD, otro para la respuesta
	break;
	
	/* Cierra todos los modulos */
	case INIT:
		removeAllOpenModules();
		((AM_PACKET*)sendBufferAdmin)->CMD = INIT; 
		adminCounter = 0x01; //1 byte para el campo CMD
	break;

	case MESSAGE:
		// me limito a solamente mandar el paquete que me genera el usuario mediante sendMes (ping)
		adminCounter = sizeof(((AM_PACKET*)recBuffPtr));
	break;
	
	case LOAD:
		//Ver loaderModule.h
		//loadModule(byte idModule, byte* binaryStream);
		adminCounter = 0x01;
	break;

	case UNLOAD:
		adminCounter=0x03;
	break;
	
	/* retorna la cantidad de modulos de usuarios presentes en el firmware */
	case GET_USER_MODULES_SIZE:
		userTableSize = getUserTableSize();
		((AM_PACKET*)sendBufferAdmin)->CMD  = GET_USER_MODULES_SIZE;
		((AM_PACKET*)sendBufferAdmin)->size = userTableSize;
		adminCounter=0x02;
	break;
	
	/* retorna el nombre correspondiente al modulo de usuario n-esimo*/
	case GET_USER_MODULES_LINE:
		((AM_PACKET*)sendBufferAdmin)->CMD  = GET_USER_MODULES_LINE;
		lineNumber = ((AM_PACKET*)recBuffPtr)->line;
		getModuleName(lineNumber, (char*)lineName);	
		//memcpy(((AM_PACKET*)sendBufferAdmin)->lineName, lineName, 8); no anda, sera porque estan en espacios de memoria separados (RAM/ROM)?			
		for (j = 0; j < 8; j++){       
			((AM_PACKET*)sendBufferAdmin)->lineName[j] = lineName[j];  
		}
		adminCounter=0x09;
	break;
	
	case CONFIGURE:
		handler  = ((AM_PACKET*)recBuffPtr)->handlerNumber;
		response = configureHandlerTableEntry(handler);	
		((AM_PACKET*)sendBufferAdmin)->response = response;
		((AM_PACKET*)sendBufferAdmin)->CMD = CONFIGURE; 
		adminCounter = 0x02; //1 byte para el campo CMD, otro para la respuesta
	break;

	case BOOT:
		Escribir_memoria_boot();
		goodByeCruelWorld();
		adminCounter = 0x01; //;)
	break;

	case RESET:
        goodByeCruelWorld();
		adminCounter = 0x01; //1 byte para el campo CMD sensless ;)
	break;
	
	default:
	break;
	
	}//end switch()
      	if(adminCounter != 0){
		j = 255;
		while(mUSBGenTxIsBusy() && j-->0); // pruebo un máximo de 255 veces
		if(!mUSBGenTxIsBusy())
			USBGenWrite2(adminHandler, adminCounter);
	}//end if

}//end adminReceived

void sendMes(char* mensaje, byte len){
	byte adminCounter, j;
	((AM_PACKET*)sendBufferAdmin)->CMD = MESSAGE;
	for (j = 0; j < len; j++){ 
		((AM_PACKET*)sendBufferAdmin)->texto[j] = mensaje[j];
	}
	adminCounter = len + 1; //sizeof(adminDataPacket);
    if(!mUSBGenTxIsBusy())
       	USBGenWrite2(adminHandler, adminCounter);
}

/*****************************************************************************
* Keep Alive para el watchdog
*****************************************************************************/

void watchdogKeepAlive(void){
    keepAlive = TRUE;
    mLED_3_On();
}

/***********************************************************************
*
* Callback function to execute periodicaly by te Timmer interrupt ISR
*
************************************************************************/

void watchdogEvent(void) {    
//    timeOutTicksWatchdog --;
//    if(timeOutTicksWatchdog == 0){            
        mLED_3_Off();
        if(keepAlive){
//            timeOutTicksWatchdog = cantTicksW;
            keepAlive = FALSE;
        }
        else{
            goodByeCruelWorld();
        }
//    }
    registerT0eventInEvent(TIME_UNIT_WATCHDOG, &watchdogEvent);
}

/*****************************************************************************
* Start watchdog
*****************************************************************************/

void watchdogStart(void){
    keepAlive = TRUE;
    registerT0event(2*TIME_UNIT_WATCHDOG, &watchdogEvent);
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
 

