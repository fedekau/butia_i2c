/* Author                                                   Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Andres Aguirre                                         08/09/2010    Original
 *****************************************************************************/

#ifndef USER_SEC_H
#define USER_SEC_H

/** I N C L U D E S **********************************************************/
#include <EEP.h>
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"
#include "usb4all/proxys/T0Service.h"
#include "io_cfg.h"

/** D E F I N I T I O N S ****************************************************/

#define EEPROM_MINOR_VERSION   0x01    
#define EEPROM_MAJOR_VERSION   0x00


/** S T R U C T U R E S ******************************************************/
typedef union EEPROM_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
            WRITE           = 0X01,
            READ            = 0x02,
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
        byte move_num;
        byte move_status;
    };
    struct
    {
        unsigned :8;
        word word_data;
    };
} EEPROM_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/

void write_eeprom(unsigned int address, unsigned char data);
unsigned char read_eeprom(unsigned int address);

#endif //USER_EEPROM_H
