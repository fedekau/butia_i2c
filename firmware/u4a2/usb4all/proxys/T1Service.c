/******************************************************************************
 * Author - Date - Comment
 *----------------------------------------------------------------------------
 * Ayle - 03/2013 - new module.
 ******************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "system/typedefs.h"
#include "system/usb/usb.h"
#include "io_cfg.h"

#include "usb4all/dynamicISR/dynamicISR.h"
#include "usb4all/proxys/T1Service.h"
#include "system/usb/usb_compile_time_validation.h"

/** V A R I A B L E S ********************************************************/
#pragma udata

#define TIMER1H_VAL 0xFF
#define TIMER1L_VAL 0x2B

/* 100Hz at 20MHz Fosc */
/*#define TIMER1H_VAL 0x3C
#define TIMER1L_VAL 0xAF
 */
#define TMR1 (unsigned int)(TMR1L | (unsigned int)(TMR1H)<<8)

volatile byte duty_cycle = 0;

//This struct contains a registration
//typedef struct  {
//    unsigned int timestamp;
//    void (*callback)(void);
//} Entry;

//storage for the registrations
//volatile Entry queue[MAX_T0CALLS];

//sliding circular window
//volatile byte first = 0;
//volatile byte next = 0;

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void interrupt_TMR1_handler(void);

#pragma code sys

/////////////////////////////////////////////////////////////////

//index of the next entry in the array
//byte next_entry(byte n) {
//    n++;
//    if (n==MAX_T0CALLS) n=0;
//    return n;
//}

//index of the previous entry in the array
//byte prev_entry(byte n) {
//    if (n==0) n=MAX_T0CALLS;
//    n--;
//    return n;
//}

//wether the queue is empty
//byte is_empty(void) {
//    return (first == next);
//}

//index of the first entry in the queue, or NULL if empty
//Entry *get_first(void) {
//    if (is_empty()) {
//        return NULL;
//    } else {
//        return &(queue[first]);
//    }
//}

//Removes the first entrye in the queue (doesn't check for empty)
//void pop_first(void) {
//    first=next_entry(first);
//}

//Adds a element to the end of the queue, and returns a pointer to it 
//(or NULL, if the queue was full)
//Entry *push_end(void) {
//    byte next1=next_entry(next);
//    Entry *entry=&(queue[next]);
//
//    if (next1==first) return NULL; //buffer full
//
//    next=next1;
//    return entry;
//}
/////////////////////////////////////////////////////////////////

/* initializes the service */
void initT1Service(void) {
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

    T1CONbits.TMR1ON = 0; /* enable timer1 */

    TRISDbits.RD2 = 0;
    addISRFunction(&interrupt_TMR1_handler);

    //    byte i;
    //    for (i=0; i<MAX_T0CALLS;i++){
    //        queue[i].timestamp = 0;
    //        queue[i].callback = 0;
    //    }

    //    #ifdef DEFAULT_CLOCK_CONFIG
    //    T0CON = DEFAULT_CLOCK_CONFIG;
    //    #endif

    //register the ISR interrupt handler (we're waiting for clock interrupts)
    //    addISRFunction(&interrupt_handler);
}

/*
    Registers a new event callback, to be called t time units in the future.
    This function must not be called from a callback handler.
 */
//BOOL registerT0event(unsigned int t, void (*callback)(void)) {
//    unsigned int timestamp;
//    unsigned int currtime;
//    byte pos;
//    byte prevpos;
//    Entry *entry;

//stop clock.
//TODO este servicio atrasa cada vez que se registra o procesa un evento.
//    T0CONbits.TMR0ON  = FALSE;

//we will calculate
//    if (is_empty()) {
//         // first in queue, nobody counting
//        timestamp=t;
//    } else {
//        //there's someone counting, must count from "now".
//        //(0xFFFF-TMR0) is the remaining time in clock to queue[first] event.
//        currtime  = queue[first].timestamp - (0xFFFF-TMR0);
//        timestamp = currtime + t;
//
//        //As we advance the clock marks, we will finally reach the max int. Then we must reduce
//        //all the marks down.
//        if (timestamp < currtime) { // overflow!
//            pos=first;
//            while (pos!=next) {
//                queue[pos].timestamp -= currtime;
//                pos=next_entry(pos);
//            }
//            timestamp=t;
//        }
//    }

//we will insert the new event at the end, and then reorder up until it find
//it's place in the queue

//add new event
//    pos=next;
//    prevpos=prev_entry(pos);
//    entry=push_end();
//    if (entry==NULL) { return FALSE; } //error adding an entry
//    entry->timestamp=timestamp;
//    entry->callback=callback;

//"buble-up" while out of order.
//    while (pos!=first && queue[pos].timestamp < queue[prevpos].timestamp) {
//        //swap
//        Entry t_entry=queue[prevpos];
//        queue[prevpos]=queue[pos];
//        queue[pos]=t_entry;
//
//        //go back 1
//        pos=prevpos;
//        prevpos=prev_entry(pos);
//    } ;

//the new entry is the first in the queue.
//this runs for either a new event that replaces a current event already
//in queue,or the first event in an empty queue.
//    if (pos==first) {
//        //configure interrupt for the (new) head event
//        INTCONbits.TMR0IF = 0; //apago bandera de interrupcion de timer0 por las dudas
//        INTCONbits.TMR0IE = 1; //cuando se agrega la primer funcion listener prendo ints de Timer0
//        timestamp=0xFFFF-timestamp;
//        TMR0H = (byte)(timestamp>>8);
//        TMR0L = (byte)timestamp;
//    }

//(re)start clock
//    T0CONbits.TMR0ON  = TRUE;
//    return TRUE;
//}

/*
    Registers a new event callback, to be called t time units in the future.
    This function only can be called from a callback handler.
 */
//BOOL registerT0eventInEvent(unsigned int t, void (*callback)(void)) {
//    unsigned int timestamp;
//    unsigned int currtime;
//    byte pos;
//    byte prevpos;
//    Entry *entry;
//
//    //this is called from an event handler, so the head event is the one being processed,
//    //and it timestamp is the current time.
//    currtime = queue[first].timestamp;
//    timestamp = currtime+t;//we're in the fist event handler
//
//    //As we advance the clock marks, we will finally reach the max int. Then we must reduce
//    //all the marks down.
//    //TODO hacer esto en el register normal
//    if (timestamp < currtime) { // overflow!
//        pos=first;
//        while (pos!=next) {
//            queue[pos].timestamp -= currtime;
//            pos=next_entry(pos);
//        }
//        timestamp=t;
//    }
//
//    //we will insert the new event at the end, and then reorder up until it find
//    //it's place in the queue
//
//    //add new event
//    pos=next;
//    prevpos=prev_entry(pos);
//    entry=push_end();
//    if (entry==NULL) { return FALSE; } //error adding an entry
//    entry->timestamp=timestamp;
//    entry->callback=callback;
//
//    //"buble-up" while out of order. stop before replacing the first event (the one being
//    //from whose handler called us)
//    while (prevpos!=first && pos!=first && queue[pos].timestamp < queue[prevpos].timestamp) {
//        //swap
//        Entry t_entry=queue[prevpos];
//        queue[prevpos]=queue[pos];
//        queue[pos]=t_entry;
//
//        //go back 1
//        pos=prevpos;
//        prevpos=prev_entry(pos);
//    } ;
//
//    return TRUE;
//}

/*
    Unregister a event callback. No pending event(s) will invoke it.
 */
//BOOL unregisterT0event(void (*callback)(void)) {
//    byte pos=first;
//
//    //iterate all events, NULLying all instances of given callback.
//    //we don't actually remove anything here, the entries will be processed normally
//    //and theyr calbacks calls simply skipped when theyr turn arrives.
//    while (pos!=next) {
//        if (queue[pos].callback==callback) {
//            queue[pos].callback=NULL;
//        }
//        pos=next_entry(pos);
//    }
//
//    return TRUE;
//}

//interrupt handler to be registered in ISR.

void interrupt_TMR1_handler(void) {/* called in ISR at timer1 interrupt */
    if (PIR1bits.TMR1IF) {
        /* reset timer initial value */
//        TMR1H = TIMER1H_VAL;
//        TMR1L = TIMER1L_VAL;
//        T1CONbits.TMR1ON = 0; /* disable timer1 */
//        PIR1bits.TMR1IF = 0;
        if (duty_cycle++ == 7) {
            duty_cycle = 0;
            LATDbits.LATD2 = 1;
        } else if (duty_cycle == 3 ){
            duty_cycle = 0;
            LATDbits.LATD2 = 0;
        }
        PIR1bits.TMR1IF = 0; /* clear interrupt flag */
//        T1CONbits.TMR1ON = 1; /* enable timer1 */
    }


    //    Entry *e;
    //    unsigned int currtime;
    //    unsigned int nexttime;
    //    void (*callback)(void);

    /* we need clock interrupts */
    //    if (INTCONbits.TMR0IF){
    //TODO este servicio atrasa cada vez que se registra o procesa un evento.
    //disable interrupts
    //        T0CONbits.TMR0ON  = FALSE;
    //        INTCONbits.TMR0IF = 0; //reset overflow

    //get head event in queue and process the callback
    //        e=get_first();
    //        callback=e->callback;
    //        if (callback) callback();
    //        currtime=e->timestamp;

    //advance the queue
    //        pop_first();
    //        e=get_first();

    //if there's a new head event, configure the clock
    //        if (e!=NULL) {
    //            nexttime = 0xFFFF - (e->timestamp - currtime);
    //            TMR0H = (byte)(nexttime>>8);
    //            TMR0L = (byte)nexttime;
    //            INTCONbits.TMR0IF = 0; //apago bandera de overflow de timer0 por las dudas
    //            T0CONbits.TMR0ON  = TRUE; //prendo timer0
    //        }
    //    }
}
