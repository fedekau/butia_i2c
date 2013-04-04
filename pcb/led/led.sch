EESchema Schematic File Version 2  date jue 21 mar 2013 10:20:34 UYT
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
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "21 mar 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1550 2200 1550 2050
Wire Wire Line
	2200 1950 2200 2350
Wire Wire Line
	2300 1950 2300 2650
Wire Wire Line
	2500 1950 2500 2650
Wire Wire Line
	2400 2150 2400 1950
Wire Wire Line
	1550 2700 1550 2850
Text GLabel 3150 1550 0    60   Input ~ 0
VDD
$Comp
L R R2
U 1 1 4FAC1BA4
P 1550 2450
F 0 "R2" V 1630 2450 50  0000 C CNN
F 1 "R" V 1550 2450 50  0000 C CNN
F 2 "" H 1550 2450 60  0001 C CNN
F 3 "" H 1550 2450 60  0001 C CNN
	1    1550 2450
	1    0    0    -1  
$EndComp
Text GLabel 2900 1150 2    60   Input ~ 0
GND
NoConn ~ 2700 1950
NoConn ~ 2600 1950
NoConn ~ 2100 1950
NoConn ~ 2000 1950
Text GLabel 1550 2050 1    60   Input ~ 0
idAN
Text GLabel 1550 2850 3    60   Input ~ 0
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
F 2 "" H 2350 1500 60  0001 C CNN
F 3 "" H 2350 1500 60  0001 C CNN
	1    2350 1500
	1    0    0    -1  
$EndComp
$Comp
L BC849 Q1
U 1 1 514B0110
P 4000 2450
F 0 "Q1" H 4000 2599 40  0000 R CNN
F 1 "BC849" H 4000 2300 40  0000 R CNN
F 2 "SOT-23" H 3900 2348 29  0000 C CNN
F 3 "~" H 4000 2450 60  0000 C CNN
	1    4000 2450
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 514B0133
P 3700 1550
F 0 "D1" H 3700 1450 50  0000 C CNN
F 1 "LED" H 3700 1650 50  0000 C CNN
F 2 "~" H 3700 1550 60  0000 C CNN
F 3 "~" H 3700 1550 60  0000 C CNN
	1    3700 1550
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4FAC1B98
P 3300 2450
F 0 "R1" V 3380 2450 50  0000 C CNN
F 1 "1k" V 3300 2450 50  0000 C CNN
F 2 "" H 3300 2450 60  0001 C CNN
F 3 "" H 3300 2450 60  0001 C CNN
	1    3300 2450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2500 2450 3050 2450
Connection ~ 2500 2450
Wire Wire Line
	3550 2450 3800 2450
Wire Wire Line
	3150 1550 3500 1550
$Comp
L R R3
U 1 1 514B01BB
P 4100 1900
F 0 "R3" V 4180 1900 40  0000 C CNN
F 1 "120" V 4107 1899 40  0000 C CNN
F 2 "~" V 4030 1900 30  0000 C CNN
F 3 "~" H 4100 1900 30  0000 C CNN
	1    4100 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 1550 4100 1550
Wire Wire Line
	4100 1550 4100 1650
Wire Wire Line
	4100 2150 4100 2250
Text GLabel 4100 2800 3    60   Input ~ 0
GND
Wire Wire Line
	4100 2800 4100 2650
$EndSCHEMATC
