/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andr?s Aguirre, Rafael Fernandez, Carlos Grossy       20/05/07    Original.
 *****************************************************************************/

#ifndef USER_BUTIA_H
#define USER_BUTIA_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define BUTIA_VERSION 0x16 //22 

/** S T R U C T U R E S ******************************************************/
typedef union BUTIA_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  /*For byte access*/
    word _word[USBGEN_EP_SIZE/2];/*For word access(USBGEN_EP_SIZE msut be even)*/
    struct
    {
        enum
        { 
            READ_VERSION_BUTIA = 0x02,
            GET_VOLT     = 0x03,
            RESET	 = 0xFF
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
} BUTIA_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif /*USER_BUTIA_H*/
