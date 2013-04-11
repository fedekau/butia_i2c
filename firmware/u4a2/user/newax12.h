#ifndef __NAX12_H
#define __NAX12_H

/* Includes */
#include <p18f4550.h>       /* PIC184550 */
#include "../typedefs.h"

#define FF              0xFF
#define TIMEOUT         15000
#define MAX_PACKET_SIZE 0x20
#define LEN_PRE_PACK    0x04
#define BRODCAST        0xFE
#define MAX_MOTOR_ID    0xFE
#define MAX_PACKET_SIZE 0x20    /*FIXME*/
#define LEN_PRE_PACK    0x04
#define SINC_0      0
#define SINC_1      1
#define ID          2
#define LEN         3
#define ERROR_CODE  4
#define DATA        5
#define CHECKSUM    6

void ax12InitSerial(void); /* Configuracion de la USART */
byte ReadSerial(void);
byte ax12ReceiveRawPacket1(byte*, byte*);   /* SUSPICIOUSLY NOT WORKING */
byte ax12ReceiveRawPacket2(byte*, byte*);   /* WORKING */
void ax12SendRawPacket(byte*, byte);

#endif
