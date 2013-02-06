/* Author     Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ayle
 *****************************************************************************/

#ifndef HACK_POINTS_H
#define HACK_POINTS_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
#include "user/adminModule.h"
#include "user/loaderModule.h"

/** D E F I N I T I O N S ****************************************************/

#define HACK_POINTS_MINOR_VERSION   0x02    /*Hackpoints version*/
#define HACK_POINTS_MAJOR_VERSION   0x00

/** S T R U C T U R E S ******************************************************/
typedef union HACK_POINTS_PACKET {
    byte _byte[USBGEN_EP_SIZE]; /* For byte access */
    word _word[USBGEN_EP_SIZE / 2]; /* For word access(USBGEN_EP_SIZE must be even) */

    struct {

        enum {
            READ_VERSION = 0x00,
            SET_MODE = 0x01,
            READ = 0x02,
            WRITE = 0x03,
            SET_PORT = 0x04,
            SET_PORT_IN = 0x05,
            SET_PORT_OUT = 0x06
        } CMD;
        byte len;
    };

    struct {
        unsigned : 8;
        byte ID;
    };

    struct {
        unsigned : 8;
        byte higth;
        byte low;
    };

    struct {
        unsigned : 8;
        word word_data;
    };
} HACK_POINTS_DATA_PACKET;

/* Declarations */
#define ZERO 0x00
#define INPUT  0xFF
#define OUTPUT 0x00
#define MASK 0x01

#endif /*HACK_POINTS_H*/
