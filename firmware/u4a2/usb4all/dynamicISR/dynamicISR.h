#ifndef DYNAMIC_ISR_H
#define DYNAMIC_ISR_H

/** D E F I N I T I O N S ****************************************************/
#define MAX_ISR_FUNCTIONS (byte) 5

/** I N C L U D E S **********************************************************/

/** P U B L I C  P R O T O T Y P E S *****************************************/
BOOL addISRFunction(void (*ISRFun) (void));
BOOL removeISRFunction(void (*ISRFun) (void));
void initISRFunctions(void);
void interruption(void);

#endif


