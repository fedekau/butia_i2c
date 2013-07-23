EESchema Schematic File Version 2  date jue 02 may 2013 11:32:49 UYT
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
LIBS:boton-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "2 may 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3200 3000 3100 3000
Wire Wire Line
	3300 2600 3550 2600
Wire Wire Line
	3300 2400 3550 2400
Wire Wire Line
	3550 2100 3300 2100
Wire Wire Line
	3300 1900 3550 1900
Wire Wire Line
	4550 1950 4550 1800
Wire Wire Line
	1650 2200 1650 2400
Wire Wire Line
	2200 1950 2200 2350
Wire Wire Line
	2300 1950 2300 2650
Wire Wire Line
	2500 1950 2500 2650
Wire Wire Line
	2400 2150 2400 1950
Wire Wire Line
	1650 3100 1650 2900
Wire Wire Line
	4550 2450 4550 2600
Wire Wire Line
	3250 1600 3550 1600
Wire Wire Line
	3250 1700 3550 1700
Wire Wire Line
	3250 1800 3550 1800
Wire Wire Line
	3550 2000 3300 2000
Wire Wire Line
	3300 2300 3550 2300
Wire Wire Line
	3300 2500 3550 2500
Wire Wire Line
	3800 3000 3900 3000
Text GLabel 3900 3000 2    60   Input ~ 0
GND
Text GLabel 3100 3000 0    60   Input ~ 0
AN
$Comp
L SW_PUSH SW1
U 1 1 51826E72
P 3500 3000
F 0 "SW1" H 3650 3110 50  0000 C CNN
F 1 "SW_PUSH" H 3500 2920 50  0000 C CNN
	1    3500 3000
	1    0    0    -1  
$EndComp
Text GLabel 3300 2600 0    60   Input ~ 0
AN
Text GLabel 3300 2400 0    60   Input ~ 0
AN
Text GLabel 3300 2500 0    60   Input ~ 0
GND
Text GLabel 3300 2300 0    60   Input ~ 0
GND
$Comp
L CONN_4 P3
U 1 1 4FE36678
P 3900 2450
F 0 "P3" V 3850 2450 50  0000 C CNN
F 1 "CONN_4" V 3950 2450 50  0000 C CNN
	1    3900 2450
	1    0    0    -1  
$EndComp
Text GLabel 3300 2100 0    60   Input ~ 0
GND
Text GLabel 3300 2000 0    60   Input ~ 0
GND
Text GLabel 3250 1800 0    60   Input ~ 0
AN
Text GLabel 3250 1700 0    60   Input ~ 0
AN
Text GLabel 3250 1600 0    60   Input ~ 0
AN
$Comp
L CONN_6 P1
U 1 1 4FB11C28
P 3900 1850
F 0 "P1" V 3850 1850 60  0000 C CNN
F 1 "CONN_6" V 3950 1850 60  0000 C CNN
	1    3900 1850
	1    0    0    -1  
$EndComp
Text GLabel 3300 1900 0    60   Input ~ 0
GND
Text GLabel 1650 3100 3    60   Input ~ 0
AN
Text GLabel 1650 2200 1    60   Input ~ 0
VDD
$Comp
L R R2
U 1 1 4FAC1BA4
P 4550 2200
F 0 "R2" V 4630 2200 50  0000 C CNN
F 1 "R" V 4550 2200 50  0000 C CNN
	1    4550 2200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4FAC1B98
P 1650 2650
F 0 "R1" V 1730 2650 50  0000 C CNN
F 1 "R" V 1650 2650 50  0000 C CNN
	1    1650 2650
	1    0    0    -1  
$EndComp
Text GLabel 2900 1150 2    60   Input ~ 0
GND
NoConn ~ 2700 1950
NoConn ~ 2600 1950
NoConn ~ 2100 1950
NoConn ~ 2000 1950
Text GLabel 4550 1800 1    60   Input ~ 0
idAN
Text GLabel 4550 2600 3    60   Input ~ 0
VDD
Text GLabel 2400 2150 3    60   Input ~ 0
GND
Text GLabel 2200 2350 3    60   Input ~ 0
VDD
Text GLabel 2500 2650 3    60   Input ~ 0
AN
Text GLabel 2300 2650 3    60   Input ~ 0
idAN
$Comp
L RJ45 J1
U 1 1 4F68816E
P 2350 1500
F 0 "J1" H 2550 2000 60  0000 C CNN
F 1 "RJ45" H 2200 2000 60  0000 C CNN
	1    2350 1500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
