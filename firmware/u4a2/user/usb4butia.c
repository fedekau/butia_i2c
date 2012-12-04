/******************************************************************************/
/*Autor: Aylen Ricca, Andres Aguirre, John Pereira, Guillermo Reisch          */
/*Autor: 12/04/2012                                                           */
/******************************************************************************/


#include "user/usb4butia.h"


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
        { &getDataD1 , &getDataA1 , &setData1, &getDetectionPinValue1 , &changeDirectionPort1 },
        { &getDataD2 , &getDataA2 , &setData2, &getDetectionPinValue2 , &changeDirectionPort2 },
        { &getDataD3 , &getDataA3 , &setData3, &getDetectionPinValue3 , &changeDirectionPort3 },
        { &getDataD4 , &getDataA4 , &setData4, &getDetectionPinValue4 , &changeDirectionPort4 },
        { &getDataD5 , &getDataA5 , &setData5, &getDetectionPinValue5 , &changeDirectionPort5 },
        { &getDataD6 , &getDataA6 , &setData6, &getDetectionPinValue6 , &changeDirectionPort6 }
    };



#pragma code module

/*------------ Port 1 ------------------*/
void changeDirectionPort1(direction io){
    TRISAbits.RA1 = io;
}

WORD getDataA1(){

    WORD res = 0;
    byte counter = 255;
    /*Configure Analogic Chanel 1, AN1 _ PIN 3*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  0;
    ADCON0bits.CHS1 =  0;
    ADCON0bits.CHS0 =  1;

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

byte getDataD1(){
    WORD res;
    res = getDataA1();
    if (res.HighB.b7)
        return 0x01;
    return 0x00;
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

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

/*------------ Port 2 ------------------*/
void changeDirectionPort2(direction io){
    TRISAbits.RA3 = io;
}

WORD getDataA2(){

    WORD res = 0;
    byte counter = 255;
    /*Configure Analogic Chanel 3, AN3 _ PIN 5*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  0;
    ADCON0bits.CHS1 =  1;
    ADCON0bits.CHS0 =  1;

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

byte getDataD2(){
    WORD res;
    res = getDataA2();
    if (res.HighB.b7)
        return 0x01;
    return 0x00;
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

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

/*------------ Port 3 ------------------*/
void changeDirectionPort3(direction io){
    TRISEbits.RE1 = io;
}

WORD getDataA3(){

    WORD res = 0;
    byte counter = 255;
    /*Configure Analogic Chanel 6, AN6 _ PIN 9*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  1;
    ADCON0bits.CHS1 =  1;
    ADCON0bits.CHS0 =  0;

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while((ADCON0bits.NOT_DONE) && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

byte getDataD3(){
    WORD res;
    res = getDataA3();
    if (res.HighB.b7)
        return 0x01;
    return 0x00;
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

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

/*------------ Port 4 ------------------*/
void changeDirectionPort4(direction io){
    TRISAbits.RA5 = io;
}

WORD getDataA4(){

    WORD res = 0;
    byte counter = 255;
    /*Configure Analogic Chanel 4, AN4 _ PIN 7*/
    ADCON0bits.CHS3 =  0;
    ADCON0bits.CHS2 =  1;
    ADCON0bits.CHS1 =  0;
    ADCON0bits.CHS0 =  0;

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

byte getDataD4(){
    WORD res;
    res = getDataA4();
    if (res.HighB.b7)
        return 0x01;
    return 0x00;
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

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

/*------------ Port 5 ------------------*/
void changeDirectionPort5(direction io){
    TRISBbits.RB1 = io;
}

WORD getDataA5(){

    WORD res = 0;
    byte counter = 255;
    /*Configure Analogic Chanel 10, AN10 _ PIN 34*/
    ADCON0bits.CHS3 =  1;
    ADCON0bits.CHS2 =  0;
    ADCON0bits.CHS1 =  1;
    ADCON0bits.CHS0 =  0;

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

byte getDataD5(){
    WORD res;
    res = getDataA5();
    if (res.HighB.b7)
        return 0x01;
    return 0x00;
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

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

/*------------ Port 6 ------------------*/
void changeDirectionPort6(direction io){
    TRISBbits.RB3 = io;
}

WORD getDataA6(){

    WORD res;
    byte counter = 255;
    /*Configure Analogic Chanel 9, AN9 _ PIN 36*/
    ADCON0bits.CHS3 =  1;
    ADCON0bits.CHS2 =  0;
    ADCON0bits.CHS1 =  0;
    ADCON0bits.CHS0 =  1;

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

byte getDataD6(){
    WORD res = 0;
    res = getDataA6();
    if (res.HighB.b7)
        return 0x01;
    return 0x00;
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

    ADCON0bits.GO =  1; /*Start Reading Analogic pin*/
    while(ADCON0bits.NOT_DONE && counter-->0);
    LSB(res) = ADRESL;
    MSB(res) = ADRESH;

    return res;
}

/******************************************************************************/


const void initPorts(void){
    byte i;

    /*Confiugures pins to be analogic*/
    ADCON1bits.VCFG = 0; /*Voltage reference higth 5v = Vss and low 0v = Vdd*/
    ADCON1bits.PCFG = 0x00;

    /*ADCON register configuration*/
    ADCON2bits.ADFM = 0x00; /*Left justified*/
    ADCON2bits.ACQT = 0x07; /*Acquisition Time Select*/
    ADCON2bits.ADCS = 0x04; /*Acquisition Time Select Fosc/4*/

    PORTD = 0x00;
    TRISD = 0xFF;
    for(i = 0; i < MAX_PORTS; i++)
        board_ports[i].change_port_direction(_IN);
}

const port_descriptor * getPortDescriptor(byte handler){
    return &board_ports[handler-1]; /*Internally ports are mapped 0..5*/
    //return board_ports[handler_id];
}