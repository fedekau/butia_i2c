/* Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Andres Aguirre	   03/04/07		Original
 *****************************************************************************/

#ifndef LOADER_MODULE_H
#define LOADER_MODULE_H

/** I N C L U D E S **********************************************************/
#include "system/typedefs.h"
/** D E F I N I T I O N S ****************************************************/
// Ver que la constante DIRECTION_TABLE tiene relacion con la seccion que esta definida en 18f4550.lkr correspondiente a user_sec
#define DIRECTION_TABLE 0x33AB
#define MEM_VACIO 0xFFFF
#define TAM_U_TAB 12
#define NULLTYPE 0xFF

/** S T R U C T U R E S ******************************************************/

typedef void(*pUserFunc)(byte);  // defino el tipo que representa las funciones init del usuario

typedef rom struct uTab{         // struct para mapear en rom los datos que identifican a las funciones init del usuario
	pUserFunc pfI;				// puntero a la funcion Init del usuario
	pUserFunc pfR;				// puntero a la funcion Release del usuario
	byte id[8];				// identificador del modulo usuario
} uTab;


/** P U B L I C  P R O T O T Y P E S *****************************************/

// Para cargar el modulo se le pasa el binaryStream que es el .hex a cargar
// y un identificador de modulo
//void loadModule(byte idModule, byte* binaryStream);
rom near char* getUserTableDirection(byte moduleId[8]);
byte getUserTableSize(void);
void getModuleName(byte line, char* modName);
pUserFunc getModuleInitDirection(rom near char* direction);
pUserFunc getModuleReleaseDirection(rom near char* direction);
byte getModuleType(rom near char* uTableDirection);
#endif //LOADER_MODULE_H
