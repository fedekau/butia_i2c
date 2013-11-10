/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rafael Fernandez    10/03/07     Original.
 * Andres Aguirre      27/03/07
 * Alan Aguiar         31/07/13
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "pnp.h"
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/defines.h"
#include "user/loaderModule.h"
#include "io_cfg.h"             // I/O pin mapping
#include "user/handlerManager.h"
#include "usr_motors.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
unsigned char ram_max_ep_number;
epHandlerMapItem epHandlerMap[MAX_HANDLERS];
HM_DATA_PACKET_HEADER hmDataPacketHeader;
byte* HandlerReceiveBuffer[MAX_HANDLERS];
void (*handlerReceivedFuncion[MAX_HANDLERS]) (byte*, byte, byte); //arreglo de punteros a las funcioens received de los modulos
HANDLER_OPTYPE hn_opType;

/** P R I V A T E  P R O T O T Y P E S ***************************************/

/** D E C L A R A T I O N S **************************************************/
#pragma code
#pragma code module

void setHandlerReceiveBuffer(byte handler, byte *rb){
    HandlerReceiveBuffer[handler] = rb;
}

void unsetHandlerReceiveBuffer(byte handler){
    HandlerReceiveBuffer[handler] = 0;
}

void setHandlerReceiveFunction(byte handler, void (*pf) (byte*,byte,byte)){
    handlerReceivedFuncion[handler] = pf;
}

void unsetHandlerReceiveFunction(byte handler){
    handlerReceivedFuncion[handler] = 0;
}

void USBGenRead2(void){
    byte len;
    byte ep = 1;
    HM_DATA_PACKET_HEADER* dph;

    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND== (unsigned) 1)) return;

    len = PACKET_MTU-1;

    //for(ep=1;ep<=ram_max_ep_number;ep++){

    if(!EPOUT_IS_BUSY(ep)){
        /*
         * Adjust the expected number of bytes to equal
         * the actual number of bytes received.
         */
        if(len > EPOUT_SIZE(ep))
            len = EPOUT_SIZE(ep);
        //antes de copiar el dato en el buffer tengo que mirar de que
        //handler es y pedir el buffer de receive del modulo de usuario
        dph = (HM_DATA_PACKET_HEADER*)EPBUFFEROUT(ep);
        handlerReceivedFuncion[dph->handlerNumber](EPBUFFEROUT(ep)+SIZE__HM_DATA_PACKET_HEADER,len-SIZE__HM_DATA_PACKET_HEADER, dph->handlerNumber);

        //Prepare dual-ram buffer for next OUT transaction
        EPOUT_SIZE(ep) = getEPSizeOUT(ep);

        //mUSBBufferReady(USBGEN_BD_OUT);

        mUSBBufferReady2(EPOUT_BDT(ep));

    }//end if
}//end USBGenRead

void USBGenWrite2(byte handler, byte len) {
    byte j = 255;
    epHandlerMapItem hmi;
    byte ep;

    if (len == (byte) 0) return;

    hmi = epHandlerMap[handler];
    ep = hmi.ep.EPNum;

    while (EPIN_IS_BUSY(ep) && j-- > (byte) 0);

    if(!EPIN_IS_BUSY(ep)) {
        /*
        * Value of len should be equal to or smaller than USBGEN_EP_SIZE.
        * This check forces the value of len to meet the precondition.
        */
        if(len > PACKET_DATA_SIZE)
            len = PACKET_DATA_SIZE;

        //seteo los datos del header
        hn_opType.handlerNumber=handler;
        hn_opType.operationType=SEND;
        //copio el header en la dual-ram buffer
        EPBUFFERIN(ep)[0] = hn_opType.hn_op;
        EPBUFFERIN(ep)[1] = len+SIZE__HM_DATA_PACKET_HEADER;
        EPBUFFERIN(ep)[2] = 0;
        //Copy data from user's buffer to dual-ram buffer
        EPIN_SIZE(ep) = len+SIZE__HM_DATA_PACKET_HEADER;

        mUSBBufferReady2(EPIN_BDT(ep));
    }

    //TODO deshardcodear la invocacion segun el numero hay que hacerlo segun el tipo de endpoint
    //mUSBBufferReady3 solo debe de invocarse para los endpoints interrupt*/

}//end USBGenWrite

byte newHandlerTableEntry(byte endPIn, rom near char* uTableDirection){
    byte i = 0;
    while (i < MAX_HANDLERS){
        if (epHandlerMap[i].ep.empty == (unsigned) 1) {
            epHandlerMap[i].ep.endPoint = endPIn;
            epHandlerMap[i].ep.empty = 0;
            epHandlerMap[i].uTableDirection = uTableDirection;
            return i;
        }
        i++;
    }
    return ERROR;
}

byte newHandlerTableEntryForcingHandler(byte endPIn, rom near char* uTableDirection, byte handler){
    if (epHandlerMap[handler].ep.empty == (unsigned) 1) {
        epHandlerMap[handler].ep.endPoint = endPIn;
        epHandlerMap[handler].ep.empty = 0;
        epHandlerMap[handler].uTableDirection = uTableDirection;
        return handler;
    } else {
        return ERROR;
    }
}

BOOL existsTableEntry(rom near char* uTableDirection){
    byte i=0;
    while (i<MAX_HANDLERS){
        if (epHandlerMap[i].uTableDirection == uTableDirection) {
            return TRUE;
        }
        i++;
    }
    return FALSE;
}

byte handlerFromTableEntry(rom near char* uTableDirection){
    byte i = 0;
    while (i < MAX_HANDLERS){
        if (epHandlerMap[i].uTableDirection == uTableDirection) {
            return i;
        }
        i++;
    }
    return ERROR;
}

void initHandlerTable() {
    byte i;
    for(i=0;i<MAX_HANDLERS;i++){
        epHandlerMap[i].ep.empty = 1;
        epHandlerMap[i].uTableDirection = 0;
    }
    //cargo el ROM_MAX_EP_NUMBER en ram
    ram_max_ep_number = ROM_MAX_EP_NUMBER;
}

void initHandlerManager(void){
    byte modulename[8];
    initHandlerTable();      //Initialize table index(handler)=>endpoint

    /* Staticaly Initialized modules */

    /* Admin module; Handler=0 */
    modulename[0]='a'; modulename[1]='d'; modulename[2]='m'; modulename[3]='i';
    modulename[4]='n'; modulename[5]=0  ; modulename[6]=0  ; modulename[7]=0  ;
    epHandlerMap[0].ep = getAdminEndpoint(); // Admin endpoint
    epHandlerMap[0].uTableDirection = getUserTableDirection(modulename); // ModuleType=0;
    adminModuleInit(0);

    /* PNP module ; Handler=7 */
    modulename[0]='p'; modulename[1]='n'; modulename[2]='p'; modulename[3]=0 ;
    modulename[4]=0; modulename[5]=0  ; modulename[6]=0  ; modulename[7]=0  ;
    epHandlerMap[MAX_PORTS + 1].ep = getPnPEndpoint();
    epHandlerMap[MAX_PORTS + 1].uTableDirection = getUserTableDirection(modulename);
    autoDetectWheels();
    PNPInit(MAX_PORTS + 1);
}

respType removeHandlerTableEntry(byte handler){
    pUserFunc releaseFunction;
    if (handler < MAX_HANDLERS && epHandlerMap[handler].ep.empty == (unsigned) 0){
        epHandlerMap[handler].ep.empty = 1;
        releaseFunction = getModuleReleaseDirection(epHandlerMap[handler].uTableDirection);
        releaseFunction(handler);
        epHandlerMap[handler].uTableDirection = 0;
        return ACK;
    }
    else{
        return NACK;
    }
}

byte removeAllOpenModules(void){
    byte handler;
    for(handler = 0; handler < MAX_HANDLERS; handler++){
        removeHandlerTableEntry(handler + 1);
    }
    return ACK;
}

byte* getSharedBuffer(byte handler){
    // esta hecho para modo 0 ping pong
    epHandlerMapItem hmi;
    byte ep;
    hmi = epHandlerMap[handler];
    ep = hmi.ep.EPNum;
    if (handler == (byte) 0)
        //Se que el admin atiende el endpoint 1 y esta es la forma que tengo de
        // que se pueda inicializar antes el admin que la tabla de BDTs
        return &ep1_in_buffer[SIZE__HM_DATA_PACKET_HEADER];
    else
        return EPBUFFERIN(ep) + SIZE__HM_DATA_PACKET_HEADER;
}

byte getEPSizeOUT(byte ep){
    return USBGEN_EP_SIZE;
}


byte getEPSizeIN(byte ep){
    return USBGEN_EP_SIZE;
}

byte getMaxHandler(void){
    byte handler, max_handler = 0;
    for(handler = 0; handler < MAX_HANDLERS; handler++){
        if (epHandlerMap[handler].ep.empty == (unsigned) 0){
            max_handler = handler;
        }
    }
    return max_handler;
}

/** EOF handlerManager.c ***************************************************************/

