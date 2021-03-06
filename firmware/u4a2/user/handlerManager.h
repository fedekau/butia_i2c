/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rafael Fernandez    10/03/07     Original.
 * Andres Aguirre	   26/03/07		Modificaciones Nuevo protocolo y agregados
 ********************************************************************/

#ifndef HANDLER_MANAGER_H
#define HANDLER_MANAGER_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/defines.h"
#include "user/descriptorManager.h"
#include "user/usb4butia.h"

/** D E F I N I T I O N S ****************************************************/
#define PACKET_MTU       (byte) 64
#define PACKET_DATA_SIZE (byte) 61
#define MAX_HANDLERS     (byte) 14 //20 es el maximo de handlers;
#define SIZE__HM_DATA_PACKET_HEADER 3 //TODO que se calcule en tiempo de compilacion en base  la estructura

/** S T R U C T U R E S ******************************************************/

typedef struct _epHandlerMapItem{
	endpoint ep;
	// Se necesita para tener una forma
	// de determinar si un modulo ya esta abierto, y para que el close obtenga el ptero a la fs close del usuario
	rom near char* uTableDirection;
} epHandlerMapItem;

typedef union _HM_DATA_PACKET_HEADER {
	struct {
		byte hn_op;
		byte pLength_ReservedH;
		byte pLength_ReservedL;
	};
	struct {
		unsigned operationType:3;
		unsigned handlerNumber:5;
		unsigned pLength:8;
		unsigned reserved:8;
	};
} HM_DATA_PACKET_HEADER;

typedef union _HANDLER_OPTYPE {
	byte hn_op;
	struct {
		unsigned operationType:3;
		unsigned handlerNumber:5;
	};
} HANDLER_OPTYPE;

typedef enum _opType {
	SEND 	= 0x00,
	CONFIG  = 0x01,
	SEND1   = 0x02,
	SEND2   = 0x03,
	SEND3   = 0x04,
	RT	= 0x05
} opType;

extern epHandlerMapItem epHandlerMap[MAX_HANDLERS];

/** P U B L I C  P R O T O T Y P E S *****************************************/

void USBGenRead2(void);
void USBGenWrite2(byte handler, byte len);
void initHandlerBuffers(void);
void setHandlerReceiveBuffer(byte handler, byte *rb);
void setHandlerReceiveFunction(byte handler,void (*pf) (byte* recBuffPtr,byte, byte));
byte newHandlerTableEntry(byte endPIn, rom near char* uTableDirection);
byte newHandlerTableEntryForcingHandler(byte endPIn, rom near char* uTableDirection, byte handler);
BOOL existsTableEntry(rom near char* uTableDirection);
byte handlerFromTableEntry(rom near char* uTableDirection);
void initHandlerTable();
void initHandlerManager(void);
respType removeHandlerTableEntry(byte handler);
respType configureHandlerTableEntry(byte handler);
byte removeAllOpenModules(void);
void unsetHandlerReceiveBuffer(byte handler);
void unsetHandlerReceiveFunction(byte handler);
byte* getSharedBuffer(byte handler);
byte getEPSizeIN(byte ep);
byte getEPSizeOUT(byte ep);
byte getMaxHandler(void);
#endif //HANDLER_MANAGER_H
