/******************************************************************************
 * Author - Date - Comment
 *----------------------------------------------------------------------------
 * Ayle - 03/2013 - new module.
 ******************************************************************************/

#ifndef USER_SHIELD_CC_H
#define USER_SHIELD_CC_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"
#include "user/ax12.h"

/** D E F I N I T I O N S ****************************************************/
#define  SHIELD_CC_MINOR_VERSION   0x01    /*motors version*/
#define  SHIELD_CC_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union SHIELD_CC_DATA_PACKET {
    byte _byte[USBGEN_EP_SIZE]; /*For byte access*/
    word _word[USBGEN_EP_SIZE / 2]; /*For word access(USBGEN_EP_SIZE msut be even)*/

    struct {

        enum {
            READ_VERSION = 0x00,
            SET_2CCMOTOR_SPEED = 0x01,
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
        byte shield_cc_num;
        byte shield_cc_status;
    };

    struct {
        unsigned : 8;
        word word_data;
    };
} SHIELD_CC_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif /*USER_SHIELD_CC_H*/