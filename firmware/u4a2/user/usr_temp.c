/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andr�s Aguirre       01/04/07    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user/usr_temp.h"
#include "handlerManager.h"


/** V A R I A B L E S ********************************************************/
#pragma udata 


byte* sendBufferTemp; /* buffer to send data*/
byte counter_temp;          /* count to evite some unnecessary reads */
byte low_temp;
byte high_temp;


/** P R I V A T E  P R O T O T Y P E S ***************************************/
void TempProcessIO(void);
void UserTempInit(byte tempHandler);
void UserTempReceived(byte* recBuffPtr, byte len, byte tempHandler);
void UserTempRelease(byte tempHandler);

// Tabla para mantener en un lugar fijo una referencia a los modulos que el usuario introduce en USB4all
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
const uTab userTempModuleTable = {&UserTempInit, &UserTempRelease,"temp"};
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module


void UserTempInit(byte tempHandler){
    setHandlerReceiveFunction(tempHandler, &UserTempReceived);
    sendBufferTemp = getSharedBuffer(tempHandler);
    counter_temp = 255;
}

void TempProcessIO(void){
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND== (unsigned) 1)) return;
}

void UserTempRelease(byte tempHandler){
    unsetHandlerReceiveBuffer(tempHandler);
    unsetHandlerReceiveFunction(tempHandler);
}

void UserTempReceived(byte* recBuffPtr, byte len, byte tempHandler){
    WORD data;
    byte index;
    byte tempCounter = 0;
    
    switch(((DATA_PACKET*)recBuffPtr)->CMD)
    {
        case READ_VERSION:
            ((DATA_PACKET*)sendBufferTemp)->_byte[0] = ((DATA_PACKET*)recBuffPtr)->_byte[0];
            ((DATA_PACKET*)sendBufferTemp)->_byte[1] = MINOR_VERSION;
            ((DATA_PACKET*)sendBufferTemp)->_byte[2] = MAJOR_VERSION;
            tempCounter=0x03;
            break;

        case GET_VALUE:
            ((DATA_PACKET*)sendBufferTemp)->_byte[0] = ((DATA_PACKET*)recBuffPtr)->_byte[0];
            if (counter_temp < (byte) 1){
                data = getPortDescriptor(tempHandler)->get_data_analog();
                low_temp = LSB(data);
                high_temp = MSB(data);
                counter_temp = 255;
            }
            ((DATA_PACKET*)sendBufferTemp)->_byte[1] = low_temp;
            ((DATA_PACKET*)sendBufferTemp)->_byte[2] = high_temp;
            tempCounter=0x03;
            counter_temp--;
            break;

        case RESET:
            Reset();
            break;

        default:
            break;

      }//end switch()

      USBGenWrite2(tempHandler, tempCounter);
 	  	
}//end userTempReceived

/** EOF usr_temp.c ***************************************************************/
