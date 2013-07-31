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
    if ((usb_device_state < CONFIGURED_STATE) || (UCONbits.SUSPND == (unsigned) 1)) return;
}

void UserAX12Release(byte usrAXHandler) {
    unsetHandlerReceiveBuffer(usrAXHandler);
    unsetHandlerReceiveFunction(usrAXHandler);
    removePoolingFunction(&UserAX12ProcessIO);
}

void UserAX12Received(byte* recBuffPtr, byte lenght, byte usrAXHandler) {
    int data_received, err = 0, value;
    byte data [2];
    byte pack [20];
    byte j = 0, id = 0, regstart = 0, res = 0, valueH = 0, valueL = 0, userAXCounter = 0;
    byte wait_res = 0, len = 0, timeout = 0;

    switch (((AX_DATA_PACKET*) recBuffPtr)->CMD) {
        case READ_VERSION:
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[0] = ((AX_DATA_PACKET*) recBuffPtr)->_byte[0];
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[1] = AX_MINOR_VERSION;
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[2] = AX_MAJOR_VERSION;
            userAXCounter = 0x03;
            break;

        case SEND_RAW:
            ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[0] = ((AX_DATA_PACKET*) recBuffPtr)->_byte[0]; /* OPCODE */
            wait_res = ((AX_DATA_PACKET*) recBuffPtr)->_byte[1]; /* wait_res indicates whether a response is being waited */
            ax12SendRawPacket(recBuffPtr, lenght); /* raw packet is sent */

            if (wait_res) { /* the client is waiting for an answer */
                timeout = ax12ReceiveRawPacket((byte *) &len, (byte *) &pack); /* read the answer */
                ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[1] = (byte) len; /* LENGHT of answer */
                ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[2] = (byte) timeout; /* TIMEOUT of answer. 1 means timeout during reading */
                userAXCounter = (byte) (len + 3);

                j = 0; /* used to iterate in answer packet */
                while (len-- > (byte) 0) { /* while there are answer elements */
                    ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[j + 3] = (byte) pack[j];
                    j++;
                }
            } else {
                ((AX_DATA_PACKET*) sendBufferUsrAX)->_byte[1] = 0x00; /* no answer is expected */
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
            res = ax12ReadPacket((byte *) &id, (int *) &err, (int *) &data_received);
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

    USBGenWrite2(usrAXHandler, userAXCounter);

}
/** EOF usr_ax.c **************************************************************/
