/* Author          				  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andrés Aguirre, Rafael Fernandez, Carlos Grossy       16/10/07    Original.
 * Ayle 25/01/13 make it compatible
 *****************************************************************************/

#ifndef USER_LOOPBACK_H
#define USER_LOOPBACK_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define LOOPBACK_MINOR_VERSION   0x02
#define LOOPBACK_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/

typedef union LOOPBACK_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            LOOPBACK_VERSION = 0x00,
            SEND_DATA = 0x01
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
        byte led_num;
        byte led_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} LOOPBACK_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/



#endif //USER_SKEL_H
