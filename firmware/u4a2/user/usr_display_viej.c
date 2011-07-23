/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Santiago Reyes Gonzalez					       10/07/09    Original.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
/*#include "xlcd.h" //Libreria para el controlador HD44780*/
#include <usart.h>
#include <delays.h>
#include <stdio.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "usr_display.h"
#include "io_cfg.h"              // I/O pin mapping
#include "user\handlerManager.h"
#include "user\dynamicPolling.h"                              



/** V A R I A B L E S ********************************************************/
#pragma udata 
byte  bCopyPORTD;
byte  usrDisplayHandler;	 // Handler number asigned to the module
byte* sendBufferUsrDisplay; // buffer to send data

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void UserDisplayProcessIO(void);
void UserDisplayInit(byte i);
void UserDisplayReceived(byte*, byte);
void UserDisplayRelease(byte i);
void UserDisplayConfigure(void);

// Table used by te framework to get a fixed reference point to the user module functions defined by the framework 
/** USER MODULE REFERENCE*****************************************************/
#pragma romdata user
uTab userDisplayModuleTable = {&UserDisplayInit,&UserDisplayRelease,&UserDisplayConfigure,"display"}; //modName must be less or equal 8 characters
#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code module

/************************************
 Timer
 ************************************/
/*#define TIMER_BASE		(1000.0/1000000.0)
#define Time(t)			(unsigned int)( (t) / TIMER_BASE )

static volatile near unsigned int Timer @ &(TMR1L);

void WaitTimer( unsigned int t )
{
	TMR1ON = false;
	Timer = -t;
	TMR1ON = true;
	TMR1IF = false;
	while( !TMR1IF );
}*/


/************************************
 LCD
 ************************************/

#define LCD_STROBE()			{ E_PIN = true; bCopyPORTD = displayPort ; Nop(); Nop(); E_PIN = false; bCopyPORTD = displayPort; }
#define LCD_STROBE_READ(value)	{ E_PIN = true; bCopyPORTD = displayPort; Nop(); Nop(); value = displayPort; E_PIN = false; bCopyPORTD = displayPort; }
#define LCD_NIBBLE(value)		{ displayPort = value; bCopyPORTD = displayPort; LCD_STROBE(); }

unsigned char lcd_read_cmd_nowait(void)
{
	unsigned char c, readc;
	displayPort = 0x0F;
	RW_PIN = true;			// Read LCD
	bCopyPORTD = displayPort;
	Nop();							// short propagation delay
	Nop();							// short propagation delay

	LCD_STROBE_READ(readc);			// Read high nibble
									// Move 4 bits to high nibble while zeroing low nibble
	c = ( ( readc << 4 ) & 0xF0 ); 
	LCD_STROBE_READ(readc);			// Read low nibble
   	c |= ( readc & 0x0F );			// Or in 4 more bits to low nibble
	RW_PIN = false;	// Return to default mode of writing LCD
	bCopyPORTD = displayPort;			
	displayPort = 0x00;		// Return to default mode of writing LCD
	return(c);
}

void lcd_check_busy(void) // Return when the LCD is no longer busy, or we've waiting long enough!
{
	// To avoid hanging forever in event there's a bad or 
	// missing LCD on hardware.  Will just run SLOW, but still run.
	unsigned int retry; 
	unsigned char c;

	for ( retry = 1000; retry--; )
	{
		c = lcd_read_cmd_nowait();
		if (0==(c&0x80)) break; // Check busy bit.  If zero, no longer busy
	}
}

void lcd_cmd(unsigned char c)
{
	lcd_check_busy(); // Check LCD busy flag
	LCD_NIBBLE( ( c >> 4 ) & 0x0F );
	LCD_NIBBLE( c & 0x0F );
}

void lcd_data(unsigned char c)
{
	lcd_check_busy(); // Check LCD busy flag
	RS_PIN = true;
	bCopyPORTD = displayPort;
	LCD_NIBBLE( ( c >> 4 ) & 0x0F );
	LCD_NIBBLE( c & 0x0F );
	RS_PIN = false;
	bCopyPORTD = displayPort;
}

void lcd_puts(const char * s)
{
	while(*s)
		lcd_data(*s++);
}

void lcd_init(void)
{
	LCD_NIBBLE( 0x03 );
	Delay10KTCYx(8);
	/*WaitTimer(Time(4.0));*/
	LCD_NIBBLE( 0x03 );
	Delay1KTCYx(2);
	/*WaitTimer(Time(0.100));*/
	LCD_NIBBLE( 0x03 );
	Delay1KTCYx(2);	
	/*WaitTimer(Time(0.100));*/
	LCD_NIBBLE( 0x02 );

	lcd_check_busy();	//Check LCD busy flag
	lcd_cmd(0x28);		//Function Set
	lcd_cmd(0x0C);		//Display On, Cursor On, Cursor Blink
	lcd_clear();		//Display Clear
	lcd_cmd(0x06);		//Entry Mode
	lcd_goto(0);		//Initialize DDRAM address to zero
}



/******************************************************************************
 * Function:        UserDisplayInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is initialices the resources that the user module needs to work, it is called by the framework 
 *					when the module is opened	
 *
 * Note:            None
 *****************************************************************************/

void UserDisplayInit(byte i){
	BOOL res;
	usrDisplayHandler = i;
	// add my receive function to the handler module, to be called automatically when the pc sends data to the user module
	setHandlerReceiveFunction(usrDisplayHandler,&UserDisplayReceived);
	// add my receive pooling function to the dynamic pooling module, to be called periodically 
	res = addPollingFunction(&UserDisplayProcessIO);
	// initialize the send buffer, used to send data to the PC
	sendBufferUsrDisplay = getSharedBuffer(usrDisplayHandler);
	//TODO return res value 
	mInitDisplay(); //inicio Display en TRISD
	lcd_init();
	lcd_clear();
}//end UserDisplayInit

/******************************************************************************
 * Function:        UserDisplayConfigure(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the specific configuration for the user module, it is called by the framework 
 *						
 *
 * Note:            None
 *****************************************************************************/
void UserDisplayConfigure(void) {
// Do the configuration
}

/******************************************************************************
 * Function:        UserDisplayProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is registered in the dinamic polling, who call ir periodically to process the IO interaction
 *					int the PIC, also it can comunicate things to the pc by the USB	
 *
 * Note:            None
 *****************************************************************************/
void UserDisplayProcessIO(void){  


	if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
	// here enter the code that want to be called periodically, per example interaction with buttons and leds.	
     

} //end ProcessIO


/******************************************************************************
 * Function:        UserDesplayRelease(byte i)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function release all the resources that the user module used, it is called by the framework 
 *					when the module is close	
 *
 * Note:            None
 *****************************************************************************/

void UserDisplayRelease(byte i){
	unsetHandlerReceiveBuffer(i);
	unsetHandlerReceiveFunction(i);
	removePoolingFunction(&UserDisplayProcessIO);
	lcd_cmd(0b00001011);
	mReleaseDisplay(); /*libero el TRISB*/
}


/******************************************************************************
 * Function:        UserDisplayReceived(byte* recBuffPtr, byte len)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function manages the comunication with the pc
 *
 * Note:            None
 *****************************************************************************/

void UserDisplayReceived(byte* recBuffPtr, byte len){
	  byte index;
	  char mens[9] = "is alive";
	  char string_1[17]; // caracteres a mostrar en el display en la linea 1
	  char string_2[17]; // caracteres a mostrar en el display en la linea 2	
      char s1[17];
	  char s2[17];
      char * p1;
	  char * p2;

	  byte userDisplayCounter = 0;
      
	switch(((DISPLAY_DATA_PACKET*)recBuffPtr)->CMD)
      {
        case READ_VERSION:
              //dataPacket._byte[1] is len
			  ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[0] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[0]; 
			  ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[1] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[1]; 
              ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[2] = DISPLAY_MINOR_VERSION;
              ((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[3] = DISPLAY_MAJOR_VERSION;
              userDisplayCounter=0x04;
              break;  
	          
     case ESCRIBIR:

				for(userDisplayCounter=0; userDisplayCounter<16; userDisplayCounter++) {
						string_1[userDisplayCounter]=((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[userDisplayCounter] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[userDisplayCounter]; 
				}
						string_1[16]=0x00;

				for (userDisplayCounter; userDisplayCounter<16; userDisplayCounter++) {
					string_2[userDisplayCounter -16]=((DISPLAY_DATA_PACKET*)sendBufferUsrDisplay)->_byte[userDisplayCounter] = ((DISPLAY_DATA_PACKET*)recBuffPtr)->_byte[userDisplayCounter]; 
				}
		
				
				/*omando que necesitamos para poder escribir en el display*/
				/*OpenXLCD(FOUR_BIT & LINE_5X7); //Configura los pines de I/O para un LCD externo.*/
				/*commandXLCD(0x0C); *//*ciende el LCD en la web aparece el 0x0C pero para mi es 0x0F por lo que aparece en el xlcd.h*/
				lcd_home();
				lcd_puts(string_1);
				lcd_home2();
				lcd_puts(string_2);			
			break;  
     case PRUEBA:
				/*displayPort =0xff; *//* Prueba para comrobar que ande los puetos/*
			/*Comando que necesitamos para poder escribir en el display*/
			lcd_home();
			p1 = s1;
			p1 = "Hola Mundo";
			/*sprintf( s1, "Hola Mundo" );*/
			lcd_puts( s1 );
				
			break; 
     
          case RESET:
              Reset();
			  break;
		  
		 case MESS:
				sendMes(mens, sizeof(mens));
              break;
         
		 default:
              break;
      }//end switch(s)
      if(userDisplayCounter != 0)
      {
          if(!mUSBGenTxIsBusy())
              USBGenWrite2(usrDisplayHandler, userDisplayCounter);
      }//end if	  	
} //end UserDisplayReceived

/** EOF usr_display.c ***************************************************************/
