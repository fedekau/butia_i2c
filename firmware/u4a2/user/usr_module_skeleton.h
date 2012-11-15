/* Author                                           Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Aylen Ricca                                      10/10/12    Original.
 *****************************************************************************/

#ifndef USER_SKELETON_H
#define USER_SKELETON_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define SKELETON_MINOR_VERSION   0x01    /* Skeleton Version 0.1 */
#define SKELETON_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union SKELETON_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  /* For byte access */
    word _word[USBGEN_EP_SIZE/2];/* For word access(USBGEN_EP_SIZE msut be even) */
    struct
    {
        enum
        {
            READ_VERSION        = 0x00,
            GET_ANALOG_VALUE    = 0x01,
            GET_DIGITAL_VALUE   = 0x02,
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
} SKELETON_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

/* here enter public prototypes */

#endif /* USER_SKELETON_H */
