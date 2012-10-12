/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca                                      12/10/12    Original.
 *****************************************************************************/

#ifndef USER_VOLTAGE_H
#define USER_VOLTAGE_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define VOLTAGE_MINOR_VERSION   0x01    /* Voltage Version 0.1 */
#define VOLTAGE_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union VOLTAGE_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  /* For byte access */
    word _word[USBGEN_EP_SIZE/2];/* For word access(USBGEN_EP_SIZE msut be even) */
    struct
    {
        enum
        {
            READ_VERSION        = 0x00,
            GET_VALUE           = 0x01,
            RESET               = 0xFF
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
} VOLTAGE_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

/* here enter public prototypes */

#endif /* USER_VOLTAGE_H */
