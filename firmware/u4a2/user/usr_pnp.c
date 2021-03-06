/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Andres Aguirre, Santiago Reyes, Guillermo Reisch          29/07/11    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "user\usr_pnp.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user\handlerManager.h"
#include "dynamicPolling.h"                              
#include "usb4all\proxys\T0Service.h"                      

#define mInitIDAnalog() TRISEbits.TRISE2=1;ADCON0=0x1D;ADCON2=0x3C;
#define TICKS_INICIAL 40
#define HOTPLUG_TIME_UNIT 1000
#define PORT_QTY 8
 
/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrPNP; // buffer to send data
byte id_by_port_low[PORT_QTY];
byte id_by_port_high[PORT_QTY];
byte handlerPortMapping[PORT_QTY];
byte timeOutTicksEvent = TICKS_INICIAL;
/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserPNPProcessIO(void);
void UserPNPInit(byte i);
void UserPNPReceived(byte*, byte);
void UserPNPRelease(byte i);
void UserPNPConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userPNPModuleTable = {&UserPNPInit,&UserPNPRelease,&UserPNPConfigure,"pnp"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/*helper function to set the control lines of the mulptiplexer with the byte pass as parameter*/
void set_mux(byte port_id){
//TODO do this with masks
    switch(port_id){
        case 0:
            S2=0;S1=0;S0=0;
        break;
        case 1:
            S2=0;S1=0;S0=1;
        break;
        case 2:
            S2=0;S1=1;S0=0;
        break;
        case 3:
            S2=0;S1=1;S0=1;
        break;
        case 4:
            S2=1;S1=0;S0=0;
        break;
        case 5:
            S2=1;S1=0;S0=1;
        break;
        case 6:
            S2=1;S1=1;S0=0;
        break;
        case 7:
            S2=1;S1=1;S0=1;
        break;
    }     
}      	
//this function assign a physical identifier to a recently open user module wich is logic identified by the handler number
void registerOpenedModuleInShieldPort(char* moduleID, byte handler){
    //TODO matchPort es simplemente una comparación de strings dado que en la funcion getDeviceName voy a guardar correctamente el nombre
    //matchPort debe de chequear que el id en el puerto port_id (id_by_port_high[port_id]*256 + byte id_by_port_low[port_id]) coincida con 
    //el valor de un moduleID
    byte port_id = 0;
    for(port_id=0;port_id<PORT_QTY;port_id++){
        if(matchPortIDValueWithDeviceName((id_by_port_high[port_id]*256 + byte id_by_port_low[port_id]),moduleID) && handlerPortMapping[port_id]==0){
            handlerPortMapping[port_id] = handler;
            break();
        }
    }
}
//this function frees the assigment of a logic usermodule to a physical port
void unregisterOpenedModuleInShieldPort(byte handler)
    byte port_id = 0;
    for(port_id=0;port_id<PORT_QTY;port_id++){
        if(handlerPortMapping[port_id] == handler)
            handlerPortMapping[port_id];
        }
    }

}
/*This function will be called by the user modules, to know wich is the port where the device is being controll it is connected*/
byte getPort(byte handler){
    byte port_id = 0;
    for(port_id=0;port_id<PORT_QTY;port_id++){
        if(handlerPortMapping[port_id] == handler){
            return(port_id);
        }
    }
    //TODO define error
    return ERROR;
}

/*This function will be used by the admin module to perform the GET_USER_MODULES_SIZE command with the new LIST command*/
byte countDevicesConnected(void){
    byte port_id = 0;
    counterDevices = 0;
    for(port_id=0;port_id<PORT_QTY;port_id++){
        set_mux(port_id);
        if((id_by_port_high[port_id]*256 + id_by_port_low[port_id])>0){
            counterDevices++;
        }
    }
    return counterDevices;
}

//devuelve en deviceName el string correspondiente al nombre del módulo concatenado con el número de instancia correspondiente al puerto port, retorna
//el código de error en caso de no encontrarse el módulo grabado en el firmware.
//sirve para el list
byte getDeviceName(char* deviceName, byte port){
    //TODO to be done!
    portDeviceNameMapping[port] = calculateDeviceName(id_by_port_high[port_id]*256 + id_by_port_low[port_id]);
    portDeviceInstanceNumberMapping[port] = DeviceInstanceNumber(port_id); 
    //DeviceInstanceNumber se tiene que fijar que tensión tiene en la pata id, y contar la cantidad de coincidencias con ese id hay en los puertos menores a port_id pasado por parametro
    deviceName = concatenarString(portDeviceNameMapping[port],portDeviceInstanceNumberMapping[port]);
    return 0;
}

byte readPort(byte port){
    //TODO
    byte error = 0;
    byte dataLow  = 0;
    byte dataHigh = 0;
    error = isInputPort?();
    if(!error){
        //TODO averiguar los pines
        switch(port_id){
            case 0:
                data=PORTDbits.RD7;
            break;
            case 1:
                data=PORTDbits.RD7;
            break;
            case 2:
                data=PORTDbits.RD7;
            break;
            case 3:
                data=PORTDbits.RD7;
            break;
            case 4:
                data=PORTDbits.RD7;
            break;
            case 5:
                data=PORTDbits.RD7;
            break;
            case 6:
                data=PORTDbits.RD7;
            break;
            case 7:
                data=PORTDbits.RD7;
            break;
        }     

    }
    return error
}

byte writePort(byte port){
//TODO just do it!
}

/******************************************************************************
 * Function:        UsePNPInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is initialices the resources that the user module needs to work, it is called by the framework 
 *					when the module is opened	
 *
 * Note:            None
 *****************************************************************************/

void UserPNPInit(byte i){
	BOOL res;
	byte usrPNPHandler = i;
	// add my receive function to the handler module, to be called automatically when the pc sends data to the user module
	setHandlerReceiveFunction(usrPNPHandler,&UserPNPReceived);
	// add my receive pooling function to the dynamic pooling module, to be called periodically 
	//res = addPollingFunction(&UserPNPProcessIO);
	// initialize the send buffer, used to send data to the PC
	sendBufferUsrPNP = getSharedBuffer(usrPNPHandler);
	mInitIDAnalog();
	ADCON2bits.ADFM = 1;   // ADC result right justified
    S0Init S1Init S2Init
    //register the detection mecanism in the timmer interrupt
    registerT0event(HOTPLUG_TIME_UNIT, &hotplugEvent); 
}//end UserPNPInit

/******************************************************************************
/* Function:        UserPNPConfigure(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the specific configuration for the user module, it is called by the framework 
 *						
 *
 * Note:            None
 *****************************************************************************/
void UserPNPConfigure(void){
// Do the configuration
}

void detectEvent(void){
    byte port_id = 0;
    byte data_low;
    byte data_high;
    for(port_id=0;port_id<PORT_QTY;port_id++){
        set_mux(port_id);
        ADCON0bits.GO = 1;              // Start AD conversion
        while(ADCON0bits.NOT_DONE);     // Wait for conversion
        id_by_port_high[port_id] = ADRESH;
        id_by_port_low[port_id]  = ADRESL;
        //TODO si hubo cambio reconfigurar el TRIS y si es digital o analog
    }
}

void hotplugEvent(){
    timeOutTicksEvent --;
    if(timeOutTicksEvent<=0){
        detectEvent();
        registerT0eventInEvent(HOTPLUG_TIME_UNIT, &hotplugEvent); 
        timeOutTicksEvent = TICKS_INICIAL;    
    }
}

/******************************************************************************
 * Function:        UserPNPProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is registered in the dinamic polling, who call ir periodically to process the IO interaction
 *					int the PIC, also it can comunicate things to the pc by the USB	
 *
 * Note:            None
 *****************************************************************************/
//Deje configurado para que se haga por interrupción de timmer, asi que esta función no creo la usemos
void UserPNPProcessIO(void){  
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    timeOutTicksEvent --;
    if(timeOutTicksEvent<=0){
        detectEvent();
        timeOutTicksEvent = TICKS_INICIAL;    
    }
}//end ProcessIO



/******************************************************************************
 * Function:        UserPNPRelease(byte i)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function release all the resources that the user module used, it is called by the framework 
 *					when the module is close	
 *
 * Note:            None
 *****************************************************************************/

void UserPNPRelease(byte i){
	unsetHandlerReceiveBuffer(i);
	unsetHandlerReceiveFunction(i);
	//removePoolingFunction(&UserPNPProcessIO);
    unregisterT0event(&hotplugEvent); 
}


/******************************************************************************
 * Function:        UserPNPReceived(byte* recBuffPtr, byte len)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function manages the comunication with the pc
 *
 * Note:            None
 *****************************************************************************/


//This is a internal module model as a user module, so this command are for testing purpouse only
void UserPNPReceived(byte* recBuffPtr, byte len, byte handler){
      byte index;
      byte port_id = 0;
      byte userPNPCounter = 0;
      switch(((PNP_DATA_PACKET*)recBuffPtr)->CMD){
        case READ_VERSION:
              //dataPacket._byte[1] is len
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[0] = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[0]; 
	        ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[1] = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[1]; 
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[2] = PNP_MINOR_VERSION;
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[3] = PNP_MAJOR_VERSION;
            userPNPCounter = 0x04;
        break;  
	          
        case ASK_ID:
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[0] = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[0]; 
            port_id = ((PNP_DATA_PACKET*)recBuffPtr)->_byte[1];	
            set_mux(port_id);
            ADCON0bits.GO = 1;              // Start AD conversion
            while(ADCON0bits.NOT_DONE);     // Wait for conversion
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[1] = ADRESH;
            ((PNP_DATA_PACKET*)sendBufferUsrPNP)->_byte[2] = ADRESL;
            userPNPCounter = 0x03;
        break;  
        
	  case RESET:
              Reset();
			  break;
		           
		 default:
              break;
      }//end switch(s)
      if(userPNPCounter != 0)
      {
          if(!mUSBGenTxIsBusy())
              USBGenWrite2(usrPNPHandler, userPNPCounter);
      }//end if  	  	
}//end UserPNPReceived

/** EOF usr_puerta.c ***************************************************************/
