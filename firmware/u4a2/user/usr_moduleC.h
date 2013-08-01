/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alan Aguiar                                      01/08/123   Original.
 *****************************************************************************/

#ifndef USER_MODULEC_H
#define USER_MODULEC_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define MODULEC_MINOR_VERSION   0x01    /*Grey Version */
#define MODULEC_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union MODULEC_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  /*For byte access*/
    word _word[USBGEN_EP_SIZE/2];/*For word access(USBGEN_EP_SIZE msut be even)*/
    struct
    {
        enum
        {
            READ_VERSION = 0x00,
            GET_VALUE    = 0x01,
            RESET	     = 0xFF /*backward compatibility*/
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
        byte modulec_num;
        byte modulec_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} MODULEC_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif /*USER_MODULEC_H*/
