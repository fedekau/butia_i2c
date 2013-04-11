#ifndef __NAX12_H
#define __NAX12_H

/* Includes */
#include <p18f4550.h>       /* PIC184550 */
#include "../typedefs.h"

#define FF              0xFF
#define TIMEOUT         15000
#define MAX_MOTOR_ID    0xFE
#define LEN_PRE_PACK    0x04

void ax12InitSerial(void);      /* Configuracion de la USART */
byte ax12ReceiveRawPacket (byte*, byte*);
void ax12SendRawPacket (byte*, byte);

#endif
