/******************************************************************************/
/*              */
/*Autor:                                                          */
/*Autor: 12/04/2012                                                           */
/******************************************************************************/

#define MAX_PORTS 6
#define DISCONECTED 0

typedef enum _DIRECTION {
    OUT = 0, 
    IN  = 1
} direction ;


/*structure to describe a USB4butia port*/
typedef struct _port_descriptor{
    byte (*get_data) (void); /*get data of pin from a port*/
    void (*set_data) (byte); /*set data of pin in a port*/
    byte detection_pin; /*pic pin used to identify the connected device*/
    byte detected_device_type_id; /*the device_type_id of the device connected*/
    void (*change_port_direction) (direction);/*callback function to change port direction*/
} port_descriptor;

/*mapping between idPort and the port descriptor*/
port_descriptor* board_ports[MAX_PORTS];

/*******************************************************************************/
//Port 1
void changeDirectionPort1(direction io){
    TRISAbits.RA1 = io;
}

byte getData1(){
    return PORTAbits.RA1;
}

void setData1(byte data){
    PORTAbits.RA1 = data;
}



//Port 2
void changeDirectionPort2(direction io){
    TRISAbits.RA3 = io;
}

byte getData2(){
    return PORTAbits.RA3;
}

void setData2(byte data){
    PORTAbits.RA3 = data;
}

//Port 3
void changeDirectionPort3(direction io){
    TRISEbits.RE1 = io;
}

byte getData3(){
    return PORTEbits.RE1;
}

void setData3(byte data){
    PORTEbits.RE1 = data;
}

//Port 4
void changeDirectionPort4(direction io){
    TRISAbits.RA5 = io;
}

byte getData4(){
    return PORTAbits.RA5;
}

void setData4(byte data){
    PORTAbits.RA5 = data;
}

//Port 5
void changeDirectionPort5(direction io){
    TRISBbits.RB1 = io;
}

byte getData5(){
    return PORTBbits.RB1;
}

void setData5(byte data){
    PORTBbits.RB1 = data;
}

//Port 6
void changeDirectionPort6(direction io){
    TRISBbits.RB3 = io;
}

byte getData6(){
    return PORTBbits.RB3;
}

void setData6(byte data){
    PORTBbits.RB3 = data;
}

/******************************************************************************/


port_descriptor* getBoardPortDescriptor(byte port){
    port_descriptor new_port_dsc;
    // El puerto mas sercano a la para 1 del PIC es el puerto 1, luego a partir de este contando en sentido antihorario definimos los demas puertos ... 2, 3, 4 ...
    switch(port){

        case 1: //Puerto N1
           // new_port_dsc.data_pin = PORTAbits.RA1; // Pin 3, Analogica 1
            new_port_dsc.get_data = &getData1;
            new_port_dsc.set_data = &setData1;
            new_port_dsc.detection_pin = PORTAbits.RA0; //Pin 2, Analogica 0 //Cambiar por una funcion
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort1; //

        break;
        case 2: //Puerto N2
            new_port_dsc.get_data = &getData2;
            new_port_dsc.set_data = &setData2;
            //new_port_dsc.data_pin = PORTAbits.RA3; // Pin 5, Analogica 3
            new_port_dsc.detection_pin = PORTAbits.RA2; //Pin 4, Analogica 2 //Cambiar por una funcion
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort2; //
        break;
        case 3: //Puerto N3
            new_port_dsc.get_data = &getData3;
            new_port_dsc.set_data = &setData3;
            //new_port_dsc.data_pin = PORTEbits.RE1; // Pin 9, Analogica 6
            new_port_dsc.detection_pin = PORTEbits.RE2; //Pin 10, Analogica 7 //Cambiar por una funcion
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort3;

        break;
        case 4: //Puerto N4
            new_port_dsc.get_data = &getData4;
            new_port_dsc.set_data = &setData4;
            //new_port_dsc.data_pin = PORTAbits.RA5; // Pin 7, Analogica 4
            new_port_dsc.detection_pin = PORTEbits.RE0; //Pin 8, Analogica 5 //Cambiar por una funcion
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort4;

        break;
        case 5: //Puerto N5
            new_port_dsc.get_data = &getData5;
            new_port_dsc.set_data = &setData5;
            //new_port_dsc.data_pin = PORTBbits.RB1; // Pin 34, Analogica 10
            new_port_dsc.detection_pin = PORTBbits.RB0; //Pin 33, Analogica 12 //Cambiar por una funcion
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort5;

        break;
        case 6: //Puerto N6
            new_port_dsc.get_data = &getData6;
            new_port_dsc.set_data = &setData6;
            //new_port_dsc.data_pin = PORTBbits.RB3; // Pin 36, Analogica 9
            new_port_dsc.detection_pin = PORTBbits.RB2; //Pin 35, Analogica 8 //Cambiar por una funcion
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start

        break;
    }
    return &new_port_dsc;
}

void board_ports_popullate(void){
    byte port;
    for(port=1;port<=MAX_PORTS;port++){
        board_ports[port]=getBoardPortDescriptor(port);
    }
}