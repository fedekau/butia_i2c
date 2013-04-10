/******************************************************************************
 * Author - Date - Comment
 *----------------------------------------------------------------------------
 * Ayle - 02/2013 - new module.
 * Ayle - 02/2013 - fixed read_info function.
 ******************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include <delays.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "user/usr_ax.h"
#include "io_cfg.h"
#include "user/handlerManager.h"
#include "dynamicPolling.h"   
#include "usb4all/proxys/T0Service.h"

/** V A R I A B L E S ********************************************************/
#pragma udata 

byte* sendBufferUsrAX;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserAX12ProcessIO(void);
void UserAX12Init(byte);
void UserAX12Received(byte*, byte, byte);
void UserAX12Release(byte);

/** U S E R   M O D U L E   R E F E R E N C E ********************************/
#pragma romdata user
uTab userAX12ModuleTable = {&UserAX12Init, &UserAX12Release, "ax"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

void UserAX12Init(byte usrAXHandler) {
    setHandlerReceiveFunction(usrAXHandler, &UserAX12Received);
    sendBufferUsrAX = getSharedBuffer(usrAXHandler);
}

void UserAX12ProcessIO(void) {
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == 1)) return;
}

void UserAX12Release(byte usrAXHandler) {
    unsetHandlerReceiveBuffer(usrAXHandler);
    unsetHandlerReceiveFunction(usrAXHandler);
    removePoolingFunction(&UserAX12ProcessIO);
}



void UserAX12Received(byte* recBuffPtr, byte lenght, byte usrAXHandler) {
    int data_received, err = 0, value;
    byte data [2];
    byte pack[20];
    byte j, id, regstart, res, valueH, valueL, userAXCounter = 0;

    byte wait_res = 0x00, error = 0x00, len = 0x00, timeout = 0x00;

    switch (((AX_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[0] = ((AX_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[1] = ((AX_DATA_PACKET*) recBuffPtr)->_byte[1];
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[2] = AX_MINOR_VERSION;
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[3] = AX_MAJOR_VERSION;
            userAXCounter = 0x04;
            break;

        case SEND_RAW:
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[0] = ((AX_DATA_PACKET*) recBuffPtr)->_byte[0]; /* OPCODE */
            wait_res = ((AX_DATA_PACKET*) recBuffPtr)->_byte[1]; /* wait_res indicates whether a response is being waited */
            ax12SendRawPacket(recBuffPtr, lenght); /* raw packet is sent */

            if (wait_res) { /* the client is waiting an answer */
                timeout = ax12ReceiveRawPacket(&len, &error, &pack); /* read the answer */
//                res = ax12ReadPacket(&value, &err, &data_received, &pack);
                ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[1] = (byte) len; /* LENGHT of answer */
                ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[2] = (byte) timeout; /* TIMEOUT of answer. 1 means timeout during reading */
                ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[3] = (byte) error; /* ERROR of read operation. 1 means PREpacket is wrong. 2 means POSTpacket is wrong */

                /* from sendBufferUsrAx[4] is stored the answer, or part of it */
//                len = res;
                j = 0; /* used to iterate in answer packet */
                while (len > 0) { /* while there are answer elements */
                    ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[j + 4] = (byte) pack[j];
                    j++;
                    len--;
                }
                userAXCounter = (byte) (j + 0x04);
            } else {
                ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[1] = 0x00; /* no answer was expected */
                userAXCounter = 0x02;
            }
            break;

        case WRITE_INFO:
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[0] = ((AX_DATA_PACKET*) recBuffPtr)->_byte[0];
            id = (byte) (((AX_DATA_PACKET*) recBuffPtr)->_byte[1]);
            regstart = (byte) (((AX_DATA_PACKET*) recBuffPtr)->_byte[2]);
            valueH = (byte) (((AX_DATA_PACKET*) recBuffPtr)->_byte[3]);
            valueL = (byte) (((AX_DATA_PACKET*) recBuffPtr)->_byte[4]);
            value = valueH;
            value = ((value << 8) | valueL);
            res = writeInfo(id, regstart, value); /* byte writeInfo (byte id, byte regstart, int value) */
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[1] = res;
            userAXCounter = 0x02;
            break;

        case READ_INFO:
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[0] = ((AX_DATA_PACKET*) recBuffPtr)->_byte[0];
            id = (((AX_DATA_PACKET*) recBuffPtr)->_byte[1]);
            data[0] = (byte) (((AX_DATA_PACKET*) recBuffPtr)->_byte[2]); /* regstart */
            data[1] = (byte) (((AX_DATA_PACKET*) recBuffPtr)->_byte[3]); /* length of reg to read */
            ax12SendPacket(id, 0x02, READ_DATA, data); /* id, lenght(data[]), instr, data */
            res = ax12ReadPacket(&id, &err, &data_received, pack);
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[1] = (byte) (data_received / 256);
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[2] = (byte) (data_received % 256);
            userAXCounter = 0x03;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;
    }
    if (userAXCounter != 0) {
        j = 255;
        while (mUSBGenTxIsBusy() && j-- > 0);
        if (!mUSBGenTxIsBusy())
            USBGenWrite2(usrAXHandler, userAXCounter);
    }
}
/** EOF usr_ax.c ***************************************************************/
