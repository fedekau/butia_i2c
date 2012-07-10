EESchema Schematic File Version 2  date mar 15 may 2012 10:41:56 UYT
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
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "15 may 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3350 1450 3350 1300
Wire Wire Line
	3350 1950 3350 2100
Wire Wire Line
	4300 1050 4700 1050
Wire Wire Line
	3900 2500 3900 2650
Wire Wire Line
	1650 3100 1650 2900
Wire Wire Line
	2400 2150 2400 1950
Wire Wire Line
	2500 1950 2500 2650
Wire Wire Line
	2300 1950 2300 2650
Wire Wire Line
	2200 1950 2200 2350
Wire Wire Line
	1650 2200 1650 2400
Wire Wire Line
	3900 2000 3900 1850
Wire Wire Line
	5100 1050 5450 1050
Wire Wire Line
	4300 1750 4300 1550
Text GLabel 5450 1050 2    60   Input ~ 0
GND
Text GLabel 4300 1750 3    60   Input ~ 0
VDD
Text GLabel 3350 1300 1    60   Input ~ 0
GND
Text GLabel 3350 2100 3    60   Input ~ 0
AN
$Comp
L VR VR1
U 1 1 4FAC35A8
P 3350 1700
F 0 "VR1" V 3430 1700 50  0000 C CNN
F 1 "VR" V 3350 1700 50  0000 C CNN
	1    3350 1700
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 4FAC358A
P 4900 1050
F 0 "D1" H 4900 1150 50  0000 C CNN
F 1 "LED" H 4900 950 50  0000 C CNN
	1    4900 1050
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4FAC3460
P 4300 1300
F 0 "R3" V 4380 1300 50  0000 C CNN
F 1 "R" V 4300 1300 50  0000 C CNN
	1    4300 1300
	1    0    0    -1  
$EndComp
Text GLabel 1650 3100 3    60   Input ~ 0
AN
Text GLabel 1650 2200 1    60   Input ~ 0
VDD
$Comp
L R R2
U 1 1 4FAC1BA4
P 3900 2250
F 0 "R2" V 3980 2250 50  0000 C CNN
F 1 "R" V 3900 2250 50  0000 C CNN
	1    3900 2250
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
Text GLabel 3900 1850 1    60   Input ~ 0
idAN
Text GLabel 3900 2650 3    60   Input ~ 0
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
