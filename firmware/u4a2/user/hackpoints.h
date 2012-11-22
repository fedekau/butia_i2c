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
            SET_HIGH_PINS = 0x01,
            SET_PIN19 = 0x02,
            SET_PIN20 = 0x03,
            SET_PIN21 = 0x04,
            SET_PIN22 = 0x05,
            SET_PIN27 = 0x06,
            SET_PIN28 = 0x07,
            SET_PIN29 = 0x08,
            SET_PIN30 = 0x09,
            GET_PIN19 = 0x0A,
            GET_PIN20 = 0x0B,
            GET_PIN21 = 0x0C,
            GET_PIN22 = 0x0D,
            GET_PIN27 = 0x0E,
            GET_PIN28 = 0x0F,
            GET_PIN29 = 0x10,
            GET_PIN30 = 0x11
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
#define OFF 0
#define ON  1

#endif /*HACK_POINTS_H*/
