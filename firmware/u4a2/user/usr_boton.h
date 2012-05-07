/* Author  ayle               			  Date 10/03/2012       Comment
 *****************************************************************************/
#ifndef USER_BOTON_H
#define USER_BOTON_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define BOTON_MINOR_VERSION    0x01
#define BOTON_MAJOR_VERSION    0x00

/** S T R U C T U R E S ******************************************************/
typedef union BOTON_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  /*For byte access*/
    word _word[USBGEN_EP_SIZE/2];/*For word access(USBGEN_EP_SIZE msut be even)*/
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
            GET_PRESSED     = 0x01,
            RESET           = 0xFF  /*backward compatibility*/
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
        byte boton_num;
        byte boton_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} BOTON_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif /*USER_BOTON_H*/
