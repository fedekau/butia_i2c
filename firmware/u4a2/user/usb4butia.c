/******************************************************************************/
/*Autor: Aylen Ricca, Andres Aguirre, John Pereira                            */
/*Autor: 12/04/2012                                                           */
/******************************************************************************/


#include "user/usb4butia.h"
//#include "user/pnp.h"



/** PROTOTIPES **/
/*------------ Port 1 ------------------*/
void changeDirectionPort1(direction io);

byte getDataD1();

WORD getDataA1();

void setData1(byte data);

WORD getDetectionPinValue1(void);

/*------------ Port 2 ------------------*/
void changeDirectionPort2(direction io);

byte getDataD2();

WORD getDataA2();

void setData2(byte data);

WORD getDetectionPinValue2(void);

/*------------ Port 3 ------------------*/
void changeDirectionPort3(direction io);

byte getDataD3();

WORD getDataA3();

void setData3(byte data);

WORD getDetectionPinValue3(void);

/*------------ Port 4 ------------------*/
void changeDirectionPort4(direction io);

byte getDataD4();

WORD getDataA4();

void setData4(byte data);

WORD getDetectionPinValue4(void);

/*------------ Port 5 ------------------*/
void changeDirectionPort5(direction io);

byte getDataD5();

WORD getDataA5();

void setData5(byte data);

WORD getDetectionPinValue5(void);

/*------------ Port 6 ------------------*/
void changeDirectionPort6(direction io);

byte getDataD6();

WORD getDataA6();

void setData6(byte data);

WORD getDetectionPinValue6(void);



/** INITIALIZED DATA **/


#pragma romdata
const port_descriptor board_ports[MAX_PORTS]=
    {
        { getDataD1 , getDataA1 , setData1, getDetectionPinValue1 , changeDirectionPort1 },
        { getDataD2 , getDataA2 , setData2, getDetectionPinValue2 , changeDirectionPort2 },
        { getDataD3 , getDataA3 , setData3, getDetectionPinValue3 , changeDirectionPort3 },
        { getDataD4 , getDataA4 , setData4, getDetectionPinValue4 , changeDirectionPort4 },
        { getDataD5 , getDataA5 , setData5, getDetectionPinValue5 , changeDirectionPort5 },
        { getDataD6 , getDataA6 , setData6, getDetectionPinValue6 , changeDirectionPort6 }
    };



#pragma code module

/*------------ Port 1 ------------------*/
void changeDirectionPort1(direction io){
    TRISAbits.RA1 = io;
}

byte getDataD1(){
    return PORTAbits.RA1;
}

WORD getDataA1(){
    
    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 1, AN1 _ PIN 3*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  0;
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

byte getDataD2(){
    return PORTAbits.RA3;
}

WORD getDataA2(){
    
    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 3, AN3 _ PIN 5*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  0;
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

byte getDataD3(){
    return PORTEbits.RE1;
}

WORD getDataA3(){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 6, AN6 _ PIN 9*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  1;
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

byte getDataD4(){
    return PORTAbits.RA5;
}

WORD getDataA4(){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 4, AN4 _ PIN 7*/
    ADCON0bits.CHS3 =  0;
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

byte getDataD5(){
    return PORTBbits.RB1;
}

WORD getDataA5(){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 10, AN10 _ PIN 34*/
    ADCON0bits.CHS3 =  1;
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

byte getDataD6(){
    return PORTBbits.RB3;
}

WORD getDataA6(){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 9, AN9 _ PIN 36*/
    ADCON0bits.CHS3 =  1;
    ADCON0bits.CHS2 =  0;
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


const port_descriptor * getBoardPortDescriptor(byte port){
    port_descriptor new_port_dsc;
/*    // El puerto mas sercano a la para 1 del PIC es el puerto 1, luego a partir de este contando en sentido antihorario definimos los demas puertos ... 2, 3, 4 ...
    switch(port){

        case 1: //Puerto N1
           // new_port_dsc.data_pin = PORTAbits.RA1; // Pin 3, Analogica 1
            new_port_dsc.get_data_digital = &getData1;
            new_port_dsc.set_data = &setData1;
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue1; //Pin 2, Analogica 0
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort1; //

        break;
        case 2: //Puerto N2
            new_port_dsc.get_data_digital = &getData2;
            new_port_dsc.set_data = &setData2;
            //new_port_dsc.data_pin = PORTAbits.RA3; // Pin 5, Analogica 3
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue2; //Pin 4, Analogica 2
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort2; //
        break;
        case 3: //Puerto N3
            new_port_dsc.get_data_digital = &getData3;
            new_port_dsc.set_data = &setData3;
            //new_port_dsc.data_pin = PORTEbits.RE1; // Pin 9, Analogica 6
            new_port_dsc.get_val_detection_pin = &getDetectionPinValue3; //Pin 10, Analogica 7
            new_port_dsc.detected_device_type_id = DISCONECTED; // Nothing conected at Start
            new_port_dsc.change_port_direction = &changeDirectionPort3;

        break;
        case 4: //Puerto N4
            new_port_dsc.get_data_digital = &getData4;
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
 * * */
    return &new_port_dsc;
}

void board_ports_popullate(){
    byte port;
    for(port=1;port<=MAX_PORTS;port++){
//        board_ports[port]=getBoardPortDescriptor(port);
    }
}

const port_descriptor * getPortDescriptor(byte handler_id){
    return 0;  //FIXME
    //return board_ports[handler_id];
}