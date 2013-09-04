/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alan Aguiar                                      04/09/123   Original.
 *****************************************************************************/

#ifndef USER_MODACT_H
#define USER_MODACT_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define MODACT_MINOR_VERSION   0x01
#define MODACT_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union MODACT_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  /*For byte access*/
    word _word[USBGEN_EP_SIZE/2];/*For word access(USBGEN_EP_SIZE msut be even)*/
    struct
    {
        enum
        {
            READ_VERSION = 0x00,
            TURN    = 0x01,
            RESET	 = 0xFF /*backward compatibility*/
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
        byte modulea_num;
        byte modulea_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} MODACT_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif /*USER_MODACT_H*/
