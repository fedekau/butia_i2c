EESchema Schematic File Version 2  date vie 19 oct 2012 11:17:30 UYST
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
LIBS:lector_recistancia-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "19 oct 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 4200 3300
NoConn ~ 2250 2000
NoConn ~ 2150 2000
NoConn ~ 1650 2000
NoConn ~ 1550 2000
Wire Wire Line
	4200 3400 4550 3400
Wire Wire Line
	3600 1200 3600 1550
Wire Wire Line
	3600 2050 3600 2350
Wire Wire Line
	1150 4150 1150 4450
Wire Wire Line
	2750 1200 2450 1200
Wire Wire Line
	1950 2000 1950 2350
Wire Wire Line
	1750 2000 1750 2400
Wire Wire Line
	1850 2000 1850 2800
Wire Wire Line
	2050 2000 2050 2700
Wire Wire Line
	1150 3300 1150 3650
Wire Wire Line
	4200 3150 4500 3150
Text GLabel 4550 3400 2    60   Input ~ 0
AN
Text GLabel 4500 3150 2    60   Input ~ 0
GND
Text GLabel 3600 2350 3    60   Input ~ 0
idAN
$Comp
L R R2
U 1 1 50814D04
P 3600 1800
F 0 "R2" V 3680 1800 50  0000 C CNN
F 1 "R" V 3600 1800 50  0000 C CNN
	1    3600 1800
	1    0    0    -1  
$EndComp
Text GLabel 3600 1200 1    60   Input ~ 0
VDD
Text GLabel 1150 4450 3    60   Input ~ 0
AN
Text GLabel 1150 3300 1    60   Input ~ 0
VDD
Text GLabel 2750 1200 2    60   Input ~ 0
GND
Text GLabel 2050 2700 3    60   Input ~ 0
AN
Text GLabel 1950 2350 3    60   Input ~ 0
GND
Text GLabel 1850 2800 3    60   Input ~ 0
idAN
Text GLabel 1750 2400 3    60   Input ~ 0
VDD
$Comp
L R R1
U 1 1 50814352
P 1150 3900
F 0 "R1" V 1230 3900 50  0000 C CNN
F 1 "6K8" V 1150 3900 50  0000 C CNN
	1    1150 3900
	1    0    0    -1  
$EndComp
$Comp
L JACK_2P J2
U 1 1 508142CB
P 3750 3300
F 0 "J2" H 3400 3100 60  0000 C CNN
F 1 "JACK_2P" H 3600 3550 60  0000 C CNN
	1    3750 3300
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J1
U 1 1 50814171
P 1900 1550
F 0 "J1" H 2100 2050 60  0000 C CNN
F 1 "RJ45" H 1750 2050 60  0000 C CNN
	1    1900 1550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
