/* Author  ayle               			  Date 10/03/2012       Comment
 *****************************************************************************/
#ifndef USER_I2C_H
#define USER_I2C_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

//#define BUTTON_MINOR_VERSION    0x01    /*button version*/
//#define BUTTON_MAJOR_VERSION    0x00

/** S T R U C T U R E S ******************************************************/
typedef union I2C_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  /*For byte access*/
    word _word[USBGEN_EP_SIZE/2];/*For word access(USBGEN_EP_SIZE msut be even)*/
    struct
    {
        enum
        {
            READ_VERSION = 0x00,
            OPEN_I2C = 0x05,
            START_I2C = 0x06,
            IDLE_I2C = 0x07,
            WRITE_I2C = 0x08,
            READ_I2C = 0x09,
            STOP_I2C = 0x10,
            CLOSE_I2C = 0x11
        }CMD;
        byte len;
    };
    struct
    {
        unsigned :8;
        byte ID;
    };
    struct
    {
        unsigned :8;
        byte i2c_num;
        byte i2c_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} I2C_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif /*USER_I2C_H*/
