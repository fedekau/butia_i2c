/******************************************************************************
 * Author - Date - Comment
 *----------------------------------------------------------------------------
 * Ayle - 02/2013 - new module.
 * Ayle - 02/2013 - fixed read_info function.
 ******************************************************************************/

#ifndef USER_AX_H
#define USER_AX_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"
#include "user/newax12.h"

/** D E F I N I T I O N S ****************************************************/
#define AX_MINOR_VERSION   0x02
#define AX_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union AX_DATA_PACKET {
    byte _byte[USBGEN_EP_SIZE];
    word _word[USBGEN_EP_SIZE / 2];

    struct {

        enum {
            READ_VERSION = 0x00,
            WRITE_INFO = 0x01,
            READ_INFO = 0x02,
            SEND_RAW = 0x03,
            RESET = 0xFF
        } CMD;
        byte len;
    };

    struct {
        unsigned : 8;
        byte id;
    };

    struct {
        unsigned : 8;
        byte ax12_num;
        byte ax12_status;
    };

    struct {
        unsigned : 8;
        word word_data;
    };
} AX_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif /* USR_AX_H */
