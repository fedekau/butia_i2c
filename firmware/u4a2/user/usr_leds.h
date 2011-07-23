/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Santiago Reyes      									28/10/10    Original.
 *****************************************************************************/

#ifndef USER_LEDs_H
#define USER_LEDS_H

/** I N C L U D E S **********************************************************/
#include "system\typedefs.h"
#include "user\adminModule.h"
#include "user\loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define LEDS_MINOR_VERSION   0x01    //Leds Version 0.1
#define LEDS_MAJOR_VERSION   0x00

 


/** S T R U C T U R E S ******************************************************/
typedef union LEDS_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
            PRENDER         = 0x01,
            APAGAR          = 0x02,
            BLINK           = 0x03,
            MESS            = 0x05,
            RESET           = 0xFF //backward compatibility
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
} LEDS_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

void UserLedsInit(byte i);
void blink_led(byte ticks, byte bks, byte led);
    
#endif //USER_LEDS_H
