/******************************************************************************/
/*Autor: Aylen Ricca, Andres Aguirre, John Pereira                            */
/*Autor: 12/04/2012                                                           */
/******************************************************************************/

#ifndef USB4BUTIA_H
#define USB4BUTIA_H

#include <p18cxxx.h>
#include "typedefs.h"

#define MAX_PORTS   (byte) 6
#define DISCONECTED (byte) 0

typedef enum _direction {
    _OUT = 0,
    _IN = 1
} direction;

/*structure to describe a USB4butia port*/
typedef struct _port_descriptor{
    byte (*get_data_digital) (void); /*get data of pin from a port, digital*/
    WORD (*get_data_analog) (void); /*get data of pin from a port, analog*/ 
    void (*set_data) (byte); /*set data of pin in a port, digital*/
    WORD (*get_val_detection_pin)(void); /*pic pin used to identify the connected device*/
    void (*change_port_direction) (direction);/*callback function to change port direction*/
} port_descriptor;

/*mapping between idPort and the port descriptor*/
extern const port_descriptor board_ports[MAX_PORTS];

/*void initSensorsTable(void);*/

byte get_device_type(WORD resistValue);

const void initPorts(byte motors_cc);

const port_descriptor * getPortDescriptor(byte handler);

#endif // USB4BUTIA_H
