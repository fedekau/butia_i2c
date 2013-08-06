/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre       01/04/07    Original. 
 ********************************************************************/

#ifndef USER_TEMP_H
#define USER_TEMP_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/usr_temp.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define MINOR_VERSION   0x01
#define MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union TEMP_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
            GET_VALUE       = 0x01,
            RESET           = 0xFF
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
} DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/


#endif //USER_TEMP_H
