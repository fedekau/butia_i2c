/******************************************************************************/
/*Autor:                                                          */
/*Autor: 12/04/2012                                                           */
/******************************************************************************/


#include "user/usb4butia.h"


/*------------ Port 1 ------------------*/
void changeDirectionPort1(direction io){
    TRISAbits.RA1 = io;
}

byte getData1(){
    return PORTAbits.RA1;
}

void setData1(byte data){
    PORTAbits.RA1 = data;
}

WORD getDetectionPinValue1(void){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 0, AN0*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  0;
    ADCON0bits.CHS1 =  0;
    ADCON0bits.CHS0 =  0;

    ADCON0bits.ADON = 1;/*Enable Analogic*/

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    ADCON0bits.ADON = 0;/*Disable Analogic*/

    return res;
}

/*------------ Port 2 ------------------*/
void changeDirectionPort2(direction io){
    TRISAbits.RA3 = io;
}

byte getData2(){
    return PORTAbits.RA3;
}

void setData2(byte data){
    PORTAbits.RA3 = data;
}

WORD getDetectionPinValue2(void){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 2, AN2*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  0;
    ADCON0bits.CHS1 =  1;
    ADCON0bits.CHS0 =  0;

    ADCON0bits.ADON = 1;/*Enable Analogic*/

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    ADCON0bits.ADON = 0;/*Disable Analogic*/

    return res;
}

/*------------ Port 3 ------------------*/
void changeDirectionPort3(direction io){
    TRISEbits.RE1 = io;
}

byte getData3(){
    return PORTEbits.RE1;
}

void setData3(byte data){
    PORTEbits.RE1 = data;
}

WORD getDetectionPinValue3(void){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 7, AN7*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  1;
    ADCON0bits.CHS1 =  1;
    ADCON0bits.CHS0 =  1;

    ADCON0bits.ADON = 1;/*Enable Analogic*/

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    ADCON0bits.ADON = 0;/*Disable Analogic*/

    return res;
}

/*------------ Port 4 ------------------*/
void changeDirectionPort4(direction io){
    TRISAbits.RA5 = io;
}

byte getData4(){
    return PORTAbits.RA5;
}

void setData4(byte data){
    PORTAbits.RA5 = data;
}

WORD getDetectionPinValue4(void){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 5, AN5*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  1;
    ADCON0bits.CHS1 =  0;
    ADCON0bits.CHS0 =  1;

    ADCON0bits.ADON = 1;/*Enable Analogic*/

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    ADCON0bits.ADON = 0;/*Disable Analogic*/

    return res;
}

/*------------ Port 5 ------------------*/
void changeDirectionPort5(direction io){
    TRISBbits.RB1 = io;
}

byte getData5(){
    return PORTBbits.RB1;
}

void setData5(byte data){
    PORTBbits.RB1 = data;
}

WORD getDetectionPinValue5(void){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 12, AN12*/
    ADCON0bits.CHS3 =  1;
    ADCON0bits.CHS2 =  1;
    ADCON0bits.CHS1 =  0;
    ADCON0bits.CHS0 =  0;

    ADCON0bits.ADON = 1;/*Enable Analogic*/

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    ADCON0bits.ADON = 0;/*Disable Analogic*/

    return res;
}

/*------------ Port 6 ------------------*/
void changeDirectionPort6(direction io){
    TRISBbits.RB3 = io;
}

byte getData6(){
    return PORTBbits.RB3;
}

void setData6(byte data){
    PORTBbits.RB3 = data;
}

WORD getDetectionPinValue6(void){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 8, AN8*/
    ADCON0bits.CHS3 =  1;
    ADCON0bits.CHS2 =  0;
    ADCON0bits.CHS1 =  0;
    ADCON0bits.CHS0 =  0;

    ADCON0bits.ADON = 1;/*Enable Analogic*/

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    ADCON0bits.ADON = 0;/*Disable Analogic*/

    return res;
}

/******************************************************************************/


/******************************************************************************/
/* FALTA ARREGLAR LA DEFINICION DE PORT DESCRIPTOR Y SU CONFIGURACION PARA    */
/* CUANDO LA LECTURA DE UN SENSOR ES ANALOGICA                                */
/******************************************************************************/

port_descriptor* getBoardPortDescriptor(byte port){
    port_descriptor new_port_dsc;
    // El puerto mas sercano a la para 1 del PIC es el puerto 1, luego a partir de este contando en sentido antihorario definimos los demas puertos ... 2, 3, 4 ...
    switch(port){

        case 1: //Puerto N1
           // new_port_dsc.data_pin = PORTAbits.RA1; // Pin 3, Analogica 1
            new_port_dsc.get_data = &getData1;
            new_port_dsc.set_data = &setData1;
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue1; //Pin 2, Analogica 0
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort1; //

        break;
        case 2: //Puerto N2
            new_port_dsc.get_data = &getData2;
            new_port_dsc.set_data = &setData2;
            //new_port_dsc.data_pin = PORTAbits.RA3; // Pin 5, Analogica 3
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue2; //Pin 4, Analogica 2
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort2; //
        break;
        case 3: //Puerto N3
            new_port_dsc.get_data = &getData3;
            new_port_dsc.set_data = &setData3;
            //new_port_dsc.data_pin = PORTEbits.RE1; // Pin 9, Analogica 6
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue3; //Pin 10, Analogica 7
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort3;

        break;
        case 4: //Puerto N4
            new_port_dsc.get_data = &getData4;
            new_port_dsc.set_data = &setData4;
            //new_port_dsc.data_pin = PORTAbits.RA5; // Pin 7, Analogica 4
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue4; //Pin 8, Analogica 5
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort4;

        break;
        case 5: //Puerto N5
            new_port_dsc.get_data = &getData5;
            new_port_dsc.set_data = &setData5;
            //new_port_dsc.data_pin = PORTBbits.RB1; // Pin 34, Analogica 10
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue5; //Pin 33, Analogica 12
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort5;

        break;
        case 6: //Puerto N6
            new_port_dsc.get_data = &getData6;
            new_port_dsc.set_data = &setData6;
            //new_port_dsc.data_pin = PORTBbits.RB3; // Pin 36, Analogica 9
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue6; //Pin 35, Analogica 8
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort6;
        break;
    }
    return &new_port_dsc;
}

void board_ports_popullate(){
    byte port;
    for(port=1;port<=MAX_PORTS;port++){
        board_ports[port]=getBoardPortDescriptor(port);
    }
}

port_descriptor* getPortDescriptor(byte handler_id){
    return board_ports[handler_id];
}