/******************************************************************************
 * Author - Date - Comment
 *----------------------------------------------------------------------------
 * Ayle - 03/2013 - new module.
 ******************************************************************************/

/** I N C L U D E S ***********************************************************/
#include <p18cxxx.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "io_cfg.h"

#include "usb4all/dynamicISR/dynamicISR.h"
#include "usb4all/proxys/T1Service.h"
#include "system/usb/usb_compile_time_validation.h"

/** V A R I A B L E S *********************************************************/
#pragma udata

#define TIMER1H_VAL 0xEC    /* 1000 Hz at 20MHz Fosc*/
#define TIMER1L_VAL 0x77
#define NULL 0
#define POS 1               /* top state */
#define NEG 2               /* down state*/
#define RESOLUTION 100      /* resolution of pwm duty cycle */

volatile int clock = 0;
volatile int duty_cycle = 0;
volatile int state = 0;

/** P R I V A T E  P R O T O T Y P E S ****************************************/
void interrupt_TMR1_handler(void);

#pragma code module

/* initializes the service */
void initT1Service() {
    /* Init Timer1 */
    T1CONbits.RD16 = 1; /* read/write 16 bit values */
    T1CONbits.T1CKPS1 = 0; /* prescaler 1:1 */
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1OSCEN = 0; /* oscillator shut off */
    T1CONbits.TMR1CS = 0; /* user internal clock (Fosc/4) */
    PIE1bits.TMR1IE = 1; /* enable timer1 interrupt on overflow */
    IPR1bits.TMR1IP = 0; /* non high priority interrupt */
    PIR1bits.TMR1IF = 0; /* clear interrupt flag */

    TMR1H = TIMER1H_VAL; /* 100Hz at 20MHz Fosc */
    TMR1L = TIMER1L_VAL;

    T1CONbits.TMR1ON = 0; /* disable timer1 */
    addISRFunction(&interrupt_TMR1_handler); /* agregar función para manejar interrupciones del timer1 */
}

void startPWM(int value) {
    state = POS;
    duty_cycle = value; /* set duty cycle of cc pwm */
    TRISDbits.RD2 = 0; /* setear pines CC como salida */
    PIR1bits.TMR1IF = 0; /* clear interrupt flag */
    T1CONbits.TMR1ON = 1; /* enable timer1 */
    return;
}

void finishPWM() {
    duty_cycle = 0;
    state = NULL;
    T1CONbits.TMR1ON = 0; /* disable timer1 */
    return;
}

/* Pulse width - pre: value > 0 */
void setDutyCycleCC(int value) {
    duty_cycle = value;
}

/* called in ISR at timer1 interrupt */
void interrupt_TMR1_handler() {
    if (PIR1bits.TMR1IF) {
        clock++;
        switch (state) {
            case POS:
                if (clock >= duty_cycle) {
                    LATDbits.LATD2 = 0;
                    clock = 0;
                    state = NEG;
                }
                break;
            case NEG:
                if (clock >= (RESOLUTION - duty_cycle)) {
                    LATDbits.LATD2 = 1;
                    clock = 0;
                    state = POS;
                }
                break;
            default:
                break;
        }
        PIR1bits.TMR1IF = 0; /* clear interrupt flag */
    }
}
/** EOF T1Service.c *******************************************************/
