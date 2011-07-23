/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Santiago Reyes Gonzalez								         10/07/09    Original.
 *****************************************************************************/

#ifndef display_H
#define display_H

/************************************
 Definitions
 ************************************/

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

/* DATA_PORT defines the port to which the LCD data lines are connected */
#define DATA_PORT      PORTD
#define TRIS_DATA_PORT TRISD

/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */
#define RW_PIN   LATDbits.LATD6   /* PORT for RW */ 
#define TRIS_RW  TRISDbits.TRISD6    /* TRIS for RW */ 
#define RS_PIN   LATDbits.LATD5   /* PORT for RS */ 
#define TRIS_RS  TRISDbits.TRISD5    /* TRIS for RS */ 
#define E_PIN    LATDbits.LATD4   /* PORT for D  */ 
#define TRIS_E   TRISDbits.TRISD4    /* TRIS for E  */

/** I N C L U D E S **********************************************************/
#include "system\typedefs.h"
#include "user\adminModule.h"
#include "user\loaderModule.h"
#include <stdio.h>
/** D E F I N I T I O N S ****************************************************/

#define DISPLAY_MINOR_VERSION   0x01    //IOR Version 0.01
#define DISPLAY_MAJOR_VERSION   0x00

#define displayPort	LATD

#define mInitDisplay() TRISD &= 0x00
#define mReleaseDisplay()  TRISD |= 0xFF



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

/** P U B L I C  P R O T O T Y P E S *****************************************/



#endif //USER_DISPLAY_H
