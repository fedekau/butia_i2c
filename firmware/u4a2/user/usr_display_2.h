/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Santiago Reyes Gonzalez								         10/07/09    Original.
 *****************************************************************************/

#ifndef display_H
#define display_H

#define	lcd_cursor(x)			lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear()				lcd_cmd(0x01)
#define lcd_putch(x)			lcd_data(x)
#define lcd_goto(x)				lcd_cmd(0x80+(x));
#define lcd_cursor_right()		lcd_cmd(0x14)
#define lcd_cursor_left()		lcd_cmd(0x10)
#define lcd_display_shift()		lcd_cmd(0x1C)
#define lcd_home()				lcd_cmd(0x02)
#define lcd_home2()				lcd_cmd(0xC0)

unsigned char lcd_read_cmd_nowait(void);
void lcd_check_busy(void);
void lcd_cmd(unsigned char c);
void lcd_data(unsigned char c);
void lcd_puts(const char * s);
void lcd_init(void);

/** I N C L U D E S **********************************************************/
#include "system\typedefs.h"
#include "user\adminModule.h"
#include "user\loaderModule.h"
/*#include <stdio.h>*/
/** D E F I N I T I O N S ****************************************************/

#define DISPLAY_MINOR_VERSION   0x01    //IOR Version 0.01
#define DISPLAY_MAJOR_VERSION   0x00

#define displayPort	LATA

#define mInitDisplay() TRISA &= 0x00
#define mReleaseDisplay()  TRISA |= 0xFF

#define input 1
#define output 0

#define true 1
#define false 0

#define o0	0x00
#define o1	0x00
#define o2	0x00
#define o3	0x00
#define o4	0x00
#define o5	0x00
#define o6	0x00
#define o7	0x00
#define i0	0x01
#define i1	0x02
#define i2	0x04
#define i3	0x08
#define i4	0x10
#define i5	0x20
#define i6	0x40
#define i7	0x80

typedef union {
	struct {
		unsigned char Filler1:1;
		unsigned char E:1;
		unsigned char RW:1;
		unsigned char RS:1;
		unsigned char Filler2:4;
	} AsBits;
	unsigned char AsChar;
} BitsPORTA;

typedef union {
	struct {
		unsigned char S3:1;
		unsigned char Filler:7;
	} AsBits;
	unsigned char AsChar;
} BitsPORTB;

typedef union {
	struct {
		unsigned char Filler1:3;
		unsigned char SCK:1;
		unsigned char Filler2:4;
	} AsBits;
	unsigned char AsChar;
} BitsPORTC;

typedef union {
	struct {
		unsigned char Data:4;
		unsigned char Filler:4;
	} AsBits;
	unsigned char AsChar;
} BitsPORTD;

typedef union {
	struct {
		unsigned char Filler1:3;
	} AsBits;
	unsigned char AsChar;
} BitsPORTE;

#define DefaultPORTA (0x00)
#define DefaultPORTB (0x00)
#define DefaultPORTC (0x00)
#define DefaultPORTD (0x00)
#define DefaultPORTE (0x00)

#define DefaultTRISA (o5|i4|o3|o2|o1|o0)
#define DefaultTRISB (o7|o6|o5|o4|o3|o2|o1|i0)
#define DefaultTRISC (i7|o6|o5|i4|o3|o2|i1|i0)
#define DefaultTRISD (o7|o6|o5|o4|o3|o2|o1|o0)
#define DefaultTRISE (o2|o1|o0)


/** S T R U C T U R E S ******************************************************/
typedef union DISPLAY_DATA_PACKET
{
    byte _byte[USBGEN_EP_SIZE];  //For byte access
    word _word[USBGEN_EP_SIZE/2];//For word access(USBGEN_EP_SIZE msut be even)
    struct
    {
        enum
        { 
            READ_VERSION    = 0x00,
			ESCRIBIR		= 0x01,
			PRUEBA			= 0x02,
			MESS			= 0x05,
			SEND_DISPLAY	= 0x04,
			INTE			= 0x06,
			TEST			= 0x07,
			RESET			= 0xFF //backward compatibility
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
} DISPLAY_DATA_PACKET;

void gotoxyXLCD (unsigned char x, unsigned char y);
void comandXLCD (unsigned char a);
void DelayFor18TCY( void );
void DelayPORXLCD( void );
void DelayXLCD( void );

/** P U B L I C  P R O T O T Y P E S *****************************************/



#endif //USER_DISPLAY_H
