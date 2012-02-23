/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Andrés Aguirre     									08/09/2010    Original.
 *****************************************************************************/

#ifndef USER_DEBUG_H
#define USER_DEBUG_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"
#include "io_cfg.h"

/** D E F I N I T I O N S ****************************************************/

#define DEBUG_MINOR_VERSION   0x01    
#define DEBUG_MAJOR_VERSION   0x00
 

/** S T R U C T U R E S ******************************************************/
typedef union DEBUG_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
			RD_DEBUG		= 0X01,
			MESSAGE			= 0x02	
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
        byte debug_num;
        byte debug_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} DEBUG_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/



#endif //USER_DEBUG_H

