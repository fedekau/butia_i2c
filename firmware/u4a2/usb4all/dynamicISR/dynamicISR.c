/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rafael Fernandez    16/06/07 	Original
 * 
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "system/typedefs.h"                        // Required
#include "system/usb/usb.h"                         // Required
#include "io_cfg.h"                                 // Required

#include "dynamicISR.h"                              // Modifiable

#include "system/usb/usb_compile_time_validation.h" // Optional
//#include "user\user.h" 
//#include "user\handlerManager.h"                              // Modifiable


/** V A R I A B L E S ********************************************************/
#pragma udata
void ( *ISRFunction[MAX_ISR_FUNCTIONS]) (void) ;//arreglo de punteros a las funciones ISR de los modulos
byte ISRListeners;
/** P R I V A T E  P R O T O T Y P E S ***************************************/

#pragma code sys


void initISRFunctions(void){
	byte i;
	for (i=0; i<MAX_ISR_FUNCTIONS;i++){
		ISRFunction[i] = 0; //supongo 0 = null
	}
	ISRListeners=0;							
}

BOOL addISRFunction(void (*ISRFun) (void)){
	byte i = 0;
	BOOL termine = FALSE;
	while (i<MAX_ISR_FUNCTIONS && !termine){
		if ( ISRFunction[i] == 0) { 
			termine = TRUE;
			ISRFunction[i] = ISRFun;
		}
		i++;
	}
	if (!termine) return FALSE;
	if ((ISRListeners++)== (byte) 0){
		INTCONbits.GIE = 1; //cuando se agrega la primer funcion listener prendo ints globales 
	}
	return TRUE;
} 		

BOOL removeISRFunction(void (*ISRFun) (void)){
	byte i=0;
	BOOL termine=FALSE;
	while (i<MAX_ISR_FUNCTIONS && !termine){
		if ( ISRFunction[i] == ISRFun) {
			termine = TRUE;
			ISRFunction [i] = 0;
		}
		i++;
	}
	if (!termine) return FALSE;
	if ((--ISRListeners)== (byte) 0) {
		INTCONbits.GIE = 0; //si se va el ultimo listener apago ints globales 
	}
	return TRUE;
}
//save is not necessary: http://www.xargs.com/pic/c18-isr-optim.pdf (page 7)
#pragma interrupt interruption //save=section(".tmpdata")
void interruption(void){
	volatile byte i=0;
	while (i<MAX_ISR_FUNCTIONS){
		if(ISRFunction[i] != 0){
			ISRFunction[i]();
		}
		i++;
	}
}

