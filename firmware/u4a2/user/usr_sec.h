/* Author                                                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Andrés Aguirre                                         08/09/2010    Original.
 *****************************************************************************/

#ifndef USER_SEC_H
#define USER_SEC_H

/** I N C L U D E S **********************************************************/
#include <EEP.h>
#include "system\typedefs.h"
#include "user\adminModule.h"
#include "user\loaderModule.h"
#include "usb4all\proxys\T0Service.h"
#include "io_cfg.h"

/** D E F I N I T I O N S ****************************************************/

#define SEC_MINOR_VERSION   0x01    
#define SEC_MAJOR_VERSION   0x00
#define BROKEN_FLAG        0x42
#define ADDRESS_FLAG        0x69
#define FLAG_RESET    0xFF
/*
#define mInitIOR_D() TRISD &= 0x00;
#define mReleaseIOR_D() TRISD |= 0xFF;
void Busy_eep_non_block(void);
*/
/** S T R U C T U R E S ******************************************************/
typedef union SEC_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
            GET_SEC         = 0X01,
            INTRUSION       = 0x02,
            RESET_FLAG      = 0x03,
            CONT_INT        = 0x04,
            MESS            = 0x05,
            RESET           = 0xFF //backward compatibility
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
        byte move_num;
        byte move_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} SEC_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/



#endif //USER_SEC_H
