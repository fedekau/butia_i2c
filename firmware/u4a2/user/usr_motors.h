/* Author             									  Date        Comment
 * John Pereira                             28/2/2012
 * Andrew
 *****************************************************************************/

#ifndef USER_MOTORS_H
#define USER_MOTORS_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"
#include "user/ax12.h"

/** D E F I N I T I O N S ****************************************************/

#define MOTORS_AX12        (byte) 0x01
#define MOTORS_SHIELD_CC   (byte) 0x02

#define MOTORS_MINOR_VERSION   0x02    /*motors version*/
#define MOTORS_MAJOR_VERSION   0x00

#define TIME_UNIT        2000
#define LONG_TIME_UNIT   5000
#define TIME_C           1000

#define C_ID_MOTORS   (byte) 253
#define C_TRIES       (byte) 2

#define MASK_SHIELD (byte) 0x07
#define SHIELD_CC   (byte) 0x04

typedef void (*fGetVolt)(int *);
typedef void (*fMoveMotor)(unsigned int, byte);

/** S T R U C T U R E S ******************************************************/
typedef union MOTORS_DATA_PACKET {
    byte _byte[USBGEN_EP_SIZE]; /*For byte access*/
    word _word[USBGEN_EP_SIZE / 2]; /*For word access(USBGEN_EP_SIZE msut be even)*/

    struct {

        enum {
            READ_VERSION = 0x00,
            SET_VEL_2MTR = 0x01,
            SET_VEL_MTR = 0x02,
            TEST_MOTORS = 0x03,
            GET_TYPE = 0x04            
        } CMD;
        byte len;
    };

    struct {
        unsigned : 8;
        byte id;
    };

    struct {
        unsigned : 8;
        byte motors_num;
        byte motors_status;
    };

    struct {
        unsigned : 8;
        word word_data;
    };
} MOTORS_DATA_PACKET;

/** P U B L I C  P R O T O T Y P E S *****************************************/
void autoDetectWheels(void);
void getVoltage(int*);
byte getMotorType(void);
void getVoltCC(int*);

#endif /*USER_MOTORS_H*/