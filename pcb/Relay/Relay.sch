EESchema Schematic File Version 2  date mié 26 dic 2012 18:48:54 UYST
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:relay
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "26 dec 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 2050 1850
NoConn ~ 1950 1850
NoConn ~ 1450 1850
NoConn ~ 1350 1850
Wire Wire Line
	3250 1800 3400 1800
Wire Wire Line
	3850 1400 4000 1400
Wire Wire Line
	3800 1300 4000 1300
Wire Wire Line
	4050 2400 3850 2400
Wire Wire Line
	2900 2300 3050 2300
Wire Wire Line
	2900 2500 3050 2500
Wire Wire Line
	1850 2350 1850 1850
Wire Wire Line
	1750 2100 1750 1850
Wire Wire Line
	1550 2100 1550 1850
Wire Wire Line
	1650 2350 1650 1850
Wire Wire Line
	2250 1050 2500 1050
Wire Wire Line
	2650 2600 3050 2600
Wire Wire Line
	4050 2200 3850 2200
Wire Wire Line
	3850 1200 4000 1200
Wire Wire Line
	2650 1800 2750 1800
Text GLabel 3400 1800 2    60   Input ~ 0
id
Text GLabel 2650 1800 0    60   Input ~ 0
VDD
$Comp
L R R1
U 1 1 50DB50DF
P 3000 1800
F 0 "R1" V 3080 1800 50  0000 C CNN
F 1 "R" V 3000 1800 50  0000 C CNN
	1    3000 1800
	0    -1   -1   0   
$EndComp
Text GLabel 3850 1400 0    60   Input ~ 0
NC
Text GLabel 3850 1200 0    60   Input ~ 0
NA
Text GLabel 3800 1300 0    60   Input ~ 0
C
Text GLabel 2900 2300 0    60   Input ~ 0
C
Text GLabel 4050 2200 2    60   Input ~ 0
NC
Text GLabel 4050 2400 2    60   Input ~ 0
NA
Text GLabel 2650 2600 0    60   Input ~ 0
GND
Text GLabel 2900 2500 0    60   Input ~ 0
data
$Comp
L CONN_3 K2
U 1 1 50DB4E3B
P 4350 1300
F 0 "K2" V 4300 1300 50  0000 C CNN
F 1 "CONN_3" V 4400 1300 40  0000 C CNN
	1    4350 1300
	1    0    0    -1  
$EndComp
Text GLabel 2500 1050 2    60   Input ~ 0
GND
Text GLabel 1850 2350 3    60   Input ~ 0
data
Text GLabel 1650 2350 3    60   Input ~ 0
id
Text GLabel 1750 2100 3    60   Input ~ 0
GND
Text GLabel 1550 2100 3    60   Input ~ 0
VDD
$Comp
L RJ45 J1
U 1 1 50DB4BA2
P 1700 1400
F 0 "J1" H 1900 1900 60  0000 C CNN
F 1 "RJ45" H 1550 1900 60  0000 C CNN
	1    1700 1400
	1    0    0    -1  
$EndComp
$Comp
L RELAY K1
U 1 1 50DB4B3E
P 3450 2250
F 0 "K1" H 3400 2400 70  0000 C CNN
F 1 "RELAY" H 3600 1750 70  0000 C CNN
	1    3450 2250
	1    0    0    -1  
$EndComp
$EndSCHEMATC
