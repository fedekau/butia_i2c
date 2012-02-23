/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Andrés Aguirre     									08/09/2010    Original.
 *****************************************************************************/

#ifndef USER_MOVE_H
#define USER_MOVE_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"
#include "io_cfg.h"

/** D E F I N I T I O N S ****************************************************/

#define MOVE_MINOR_VERSION   0x01    
#define MOVE_MAJOR_VERSION   0x00
 
/*
#define mInitIOR_D() TRISD &= 0x00;
#define mReleaseIOR_D() TRISD |= 0xFF;
*/
/** S T R U C T U R E S ******************************************************/
typedef union MOVE_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
			GET_MOVE		= 0X01,
            MESS			= 0x05,
            RESET			= 0xFF //backward compatibility
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
} MOVE_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/



#endif //USER_MOVE_H
