/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre       26/03/07    Original.
 ********************************************************************/
#ifndef ADMIN_MODULE_H
#define ADMIN_MODULE_H
/** I N C L U D E S **********************************************************/
#include "user/handlerManager.h"
#include "user/defines.h"
#include "user/descriptorManager.h"
#include "user/loaderModule.h"
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "io_cfg.h"   
#include <p18cxxx.h>
#include "user/userTemp.h"
#include "usb4all/boot/boot.h"
#include <string.h>
#include <EEP.h>
#include "usb4all/proxys/T0Service.h"

/** D E F I N I T I O N S ****************************************************/
#define HM_PACKET_SIZE 253
#define HM_PACKET_HEADER_SIZE 1
#define HM_PACKET_PAYLOAD_SIZE (HM_PACKET_SIZE - HM_PACKET_HEADER_SIZE)
#define TIME_UNIT_WATCHDOG   65500
#define ADDRESS_BOOT 0x09
#define BOOT_FLAG 0x11

#define MAX_PORTS 8
#define MAX_DEVICES 9

/** S T R U C T U R E S ******************************************************/

typedef union _AM_PACKET {
	byte _byte[HM_PACKET_SIZE];
	struct {
		enum {
			OPEN    			   = 0x00,
			CLOSE  				   = 0x01,
			MESSAGE 			   = 0x02,
			LOAD    			   = 0x03,
			UNLOAD  			   = 0x04,
			GET_USER_MODULES_SIZE  = 0x05,
			GET_USER_MODULES_LINE  = 0x06,
			INIT				   = 0x07,
			CONFIGURE			   = 0x08,
			BOOT				   = 0x09, 
			RESET				   = 0xff
		}CMD;
		byte payload[HM_PACKET_PAYLOAD_SIZE];
	};
	struct { //Open, PC->PLACA
		unsigned :8;
		byte inEp;
		byte outEp;
		byte moduleId[8];
	};
	struct { //Open, PLACA->PC
		unsigned :8;
		byte handlerNumber;
		//byte epNumber; no devuelvo mas el endpoint, se administra en la pc
	};
	struct { //Close, PC->PLACA
		unsigned :8;
		byte handlerNumber;
	};
	struct { //Close, PLACA->PC
		unsigned :8;
		respType response; //respType en defines.h
	};
	struct { //Message, PLACA->PC y MODULO_USUARIO->ADMIN?
		unsigned :8;
		char texto[HM_PACKET_SIZE - HM_PACKET_HEADER_SIZE];
	};
	struct { //GET_USER_MODULES_SIZE, PC->PLACA
		unsigned :8;
	};
	struct { //GET_USER_MODULES_SIZE, PLACA->PC 
		unsigned :8;
		byte size;
	};
	struct { //GET_USER_MODULES_LINE, PC->PLACA 
		unsigned :8;
		byte line;
	};	
	struct { //GET_USER_MODULES_LINE, PLACA->PC
		unsigned :8;
		char lineName[8];
	};		
	struct { //INIT, PLACA->PC
		unsigned :8;
	};		
	struct { //INIT, PLACA->PC
		unsigned :8;
	};		
} AM_PACKET;

/*structure to describe a USB4butia port*/
typedef struct port_descriptor{
    byte* data_pin; /*pic pin of data where the device is connected*/
    byte* detection_pin; /*pic pin used to identify the connected device*/
    byte* detected_device_type_id; /*the device_type_id of the device connected*/
};

/** P U B L I C  P R O T O T Y P E S *****************************************/
void adminModuleInit(void);
void adminReceived(byte* recBuffPtr,byte len);
void sendMes(char* mensaje, byte len);
void Escribir_memoria_boot(void);
void Busy_eep_non_block (void);

#endif //ADMIN_MODULE_H
