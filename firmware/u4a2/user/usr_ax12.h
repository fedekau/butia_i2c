/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *****************************************************************************/

#ifndef USER_AX12_H
#define USER_AX12_H

/** I N C L U D E S **********************************************************/
#include "system\typedefs.h"
#include "user\adminModule.h"
#include "user\loaderModule.h"
#include "user\ax12.h"

/** D E F I N I T I O N S ****************************************************/

#define AX12_MINOR_VERSION   0x01    //ax12 version 0.1
#define AX12_MAJOR_VERSION   0x00
 
/** S T R U C T U R E S ******************************************************/
typedef union AX12_DATA_PACKET{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
            WRITE_INFO      = 0x01,
            RESETM          = 0xFF
        } CMD;
        byte len;
    };
    struct
    {
        unsigned :8;
        byte id;
    };
    struct
    {
        unsigned :8;
        byte ax12_num;
        byte ax12_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} AX12_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif //USER_AX12_H
