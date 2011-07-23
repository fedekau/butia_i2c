/* Author             									  Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Andres Aguirre Dorelo y Viterbo Rodriguez  			09/08/10    Original.
 *****************************************************************************/

#ifndef TOP_LIST_TAD_H
#define TOP_LIST_TAD_H

/** I N C L U D E S **********************************************************/
#include "system\typedefs.h" //byte definition

/** D E F I N I T I O N S ****************************************************/
#define LIST_SIZE   128 // 192 se pueden almacenar hasta 6 pantallas
#define SCREEN_SIZE 32

 
/** S T R U C T U R E S ******************************************************/

typedef struct{
        byte list[LIST_SIZE]; 
        int empty;          //puntero a la primer celda disponible del intervalo [empty - full) 
        int full;           //puntero a la primer celda no disponible del intervalo [full - empty) 
        int mark;           //puntero a la posición desde donde debe de comenzar a repetirse un mensaje
        int space;          //cantidad de celdas del intervalo [empty - full) disponibles
        int space_mark;     //espacio que debe quedar disponible cuando el puntero full vuelve hacia atras debido a que se debe repetir un mensaje
        int temp;           //debuging

/*
        int firstElement;
        int lastElement; 
        int firstElementDummy; //usado para insertar mensajes que vienen fragmentados y hasta que no se determine el principio y fin no se puede insertar
        int lastElementDummy;  //usado para insertar mensajes que vienen fragmentados y hasta que no se determine el principio y fin no se puede insertar
        int toPrint_ini;
        int toPrint_end;
*/
        byte isCiclic;
//        byte isCommited;
} topList;

/** P U B L I C  P R O T O T Y P E S *****************************************/

/* Crea la estructura inicializando a valores conocidos los campos*/
void create(topList* newList);
/* Inserta un nuevo mensaje msg en la lista list, dependiendo del campo isCiclic el mensaje se mostrara de forma ciclica o normal*/
byte insert(byte* msg, int length, topList* list, byte isCilic);
/* Retorna la pantalla screen a mostrar en el display, correspondiente a la pantalla actual de la lista list, en caso de llegar al final de la lista endList vale 1, de lo contrario vale 0*/
void getNextScreen(byte* screen, topList* list, byte* isEndList);
void getNextLine(byte* screen, topList* list, byte* isEndList);
void startCommitiableInsert(topList* list);
byte insertCommitiable(byte* msg, int length, topList* list, byte isCilic);
void commit(topList* list);


#endif //TOP_LIST_TAD_H
