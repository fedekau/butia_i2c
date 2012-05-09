/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  
 *****************************************************************************/

#ifndef GPIO_H
#define GPIO_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define GPIO_MINOR_VERSION   0x02    //Skeleton Version 0.13
#define GPIO_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union GPIO_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
            GET_RES         = 0x01            
        } CMD;
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
        byte higth;
        byte low;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} GPIO_DATA_PACKET;


#endif //GPIO_H
