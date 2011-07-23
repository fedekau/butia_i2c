/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Andres Aguirre y Viterbo Rodriguez                      10/08/10    Original
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>			
#include "system\typedefs.h"
#include "user\topList.h"

/** V A R I A B L E S ********************************************************/



/** P R I V A T E  P R O T O T Y P E S ***************************************/

/* Crea la estructura inicializando a valores conocidos los campos*/
void create(topList* newList);
/* Inserta un nuevo mensaje msg en la lista list, dependiendo del campo isCiclic el mensaje se mostrara de forma ciclica o normal*/
byte insert(byte* msg, int length, topList* list, byte isCilic);
/* Retorna la pantalla screen a mostrar en el display, correspondiente a la pantalla actual de la lista list, en caso de llegar al final de la lista endList vale 1, de lo contrario vale 0*/
void getNextScreen(byte* screen, topList* list, byte* isEndList);
#pragma code
/** D E C L A R A T I O N S **************************************************/
#pragma code module
void create(topList* newList) {
    int i;
    (*newList).empty             = 0;
    (*newList).full              = 0;
    (*newList).mark              = 0;
    (*newList).space             = LIST_SIZE;
    (*newList).space_mark        = 0;
    for(i=0; i<LIST_SIZE; i++) {
        (*newList).list[i] = '0' + (i % 10);
    }  
}

void startCommitiableInsert(topList* list) {
    (*list).mark = -1;
}


byte insertCommitiable(byte* msg, int length, topList* list, byte isCilic){

    int i,j,empty;
    if ((*list).space < length) {
        return 1;
    }
    (*list).temp = 0;
    if ((*list).mark == -1) {
        (*list).mark = (*list).empty;
        (*list).space_mark = LIST_SIZE;
    }
    empty = (*list).empty;

    for(i=0; i<length; i++) {
        (*list).list[empty] = msg[i];
        empty=(empty+1) % LIST_SIZE;           
    }
    (*list).space -= length;
    (*list).space_mark -= length;
    (*list).empty = empty;
    (*list).isCiclic = isCilic;

    return 0;               
}

void commit(topList* list) {
}

void getNextScreen(byte* screen, topList* list, byte* isEndList){
    int i;
    int space = (*list).space;
    int full  = (*list).full;
    *isEndList = 0;

    //inicializo el buffer con blancos
    for(i=0;i<32;i++) screen[i] = ' ';

    //voy a ir armando el buffer de retorno correspondiente a una pantalla
    for(i=0; (i<32) && (space < LIST_SIZE); i++, space++) {
        screen[i] = (*list).list[full];
        full = (full + 1) % LIST_SIZE;
    }

    (*list).space = space;
    (*list).full  = full;

    if (space == LIST_SIZE) {
        if ((*list).isCiclic && (*list).mark != -1) {
            (*list).full = (*list).mark;
            (*list).space = (*list).space_mark;
            (*list).temp++;
        } else {
            *isEndList = 1; 
        }
    }
}

void getNextLine(byte* screen, topList* list, byte* isEndList){
    int i;
    int space = (*list).space;
    int full  = (*list).full;
    *isEndList = 0;

    //inicializo el buffer con blancos
    for(i=0;i<16;i++) screen[i] = ' ';

    //voy a ir armando el buffer de retorno correspondiente a una linea de pantalla
    for(i=0; (i<16) && (space < LIST_SIZE); i++, space++) {
        screen[i] = (*list).list[full];
        full = (full + 1) % LIST_SIZE;
    }

    (*list).space = space;
    (*list).full  = full;

    if (space == LIST_SIZE) {
        if ((*list).isCiclic && (*list).mark != -1) {
            (*list).full = (*list).mark;
            (*list).space = (*list).space_mark;
            (*list).temp++;
        } else {
            *isEndList = 1;
        }
    }
}
/** EOF topList.c ***************************************************************/
