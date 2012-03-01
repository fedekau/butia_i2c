/* Author             									  Date        Comment
 * John Pereira                             28/2/2012
 *****************************************************************************/

#ifndef USER_MOTORES_H
#define USER_MOTORES_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"
#include "user/usr_ax12.h"

/** D E F I N I T I O N S ****************************************************/

//#define AX12_MINOR_VERSION   0x01    //ax12 version 0.1
//#define AX12_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union MOTORES_DATA_PACKET{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        {
            SET_VEL_MTR = 0x00,
            SET_VEL_2MTR = 0x01
        } CMD;
        byte len;
    };
    struct
    {
        unsigned :8;
        byte id;
    };
    struct
    {
        unsigned :8;
        byte ax12_num;
        byte ax12_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} MOTORES_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

#endif //USER_MOTORES_H

