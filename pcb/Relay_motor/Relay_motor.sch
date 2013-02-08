EESchema Schematic File Version 2  date mié 26 dic 2012 19:05:56 UYST
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
LIBS:Relay_motor-cache
EELAYER 25  0
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
Wire Wire Line
	4300 5650 4100 5650
Wire Wire Line
	4350 4450 4100 4450
Wire Wire Line
	4100 3450 4200 3450
Wire Wire Line
	4200 3450 4200 3650
Wire Wire Line
	4200 3650 1550 3650
Wire Wire Line
	2550 2600 4050 2600
Wire Wire Line
	2600 3850 2600 4900
Wire Wire Line
	2600 3850 1650 3850
Wire Wire Line
	6200 4550 5750 4550
Wire Wire Line
	5750 4550 5750 4250
Wire Wire Line
	5750 4250 4100 4250
Wire Wire Line
	6100 2500 6100 1950
Wire Wire Line
	4100 3150 6100 3150
Wire Wire Line
	6100 2500 6250 2500
Wire Wire Line
	3000 1850 3250 1850
Wire Wire Line
	1550 3850 1600 3850
Wire Wire Line
	1850 2400 1600 2400
Wire Wire Line
	1850 2600 1600 2600
Wire Wire Line
	1550 3750 1650 3750
Wire Wire Line
	1650 3750 1650 3850
Wire Wire Line
	3000 2050 3250 2050
Wire Wire Line
	3050 3250 3300 3250
Wire Wire Line
	3050 3050 3300 3050
Wire Wire Line
	3050 4150 3300 4150
Wire Wire Line
	3050 4350 3300 4350
Wire Wire Line
	3050 5550 3300 5550
Wire Wire Line
	3050 5350 3300 5350
Wire Wire Line
	6250 2700 6100 2700
Wire Wire Line
	6100 1950 4050 1950
Wire Wire Line
	6100 2700 6100 3150
Wire Wire Line
	1550 3550 2550 3550
Wire Wire Line
	2550 3550 2550 2600
Wire Wire Line
	4100 5450 5750 5450
Wire Wire Line
	5750 5450 5750 4750
Wire Wire Line
	5750 4750 6200 4750
Wire Wire Line
	1600 3850 1600 6050
Wire Wire Line
	4050 2600 4050 2250
Wire Wire Line
	4400 2150 4050 2150
Wire Wire Line
	4100 3350 4400 3350
Wire Wire Line
	2600 4900 4200 4900
Wire Wire Line
	4200 4900 4200 4550
Wire Wire Line
	4200 4550 4100 4550
Wire Wire Line
	1600 6050 4200 6050
Wire Wire Line
	4200 6050 4200 5750
Wire Wire Line
	4200 5750 4100 5750
$Comp
L CONN_2 P3
U 1 1 50DB46A8
P 6550 4650
F 0 "P3" V 6500 4650 40  0000 C CNN
F 1 "CONN_2" V 6600 4650 40  0000 C CNN
	1    6550 4650
	1    0    0    -1  
$EndComp
Text GLabel 3050 4150 0    60   Input ~ 0
VCC
Text GLabel 3050 4350 0    60   Input ~ 0
GND
Text GLabel 3050 5550 0    60   Input ~ 0
GND
Text GLabel 3050 5350 0    60   Input ~ 0
VCC
Text GLabel 3050 3050 0    60   Input ~ 0
VCC
Text GLabel 3050 3250 0    60   Input ~ 0
GND
Text GLabel 1850 2400 2    60   Input ~ 0
VCC
Text GLabel 1850 2600 2    60   Input ~ 0
GND
$Comp
L CONN_2 P4
U 1 1 50DB4542
P 6600 2600
F 0 "P4" V 6550 2600 40  0000 C CNN
F 1 "CONN_2" V 6650 2600 40  0000 C CNN
	1    6600 2600
	1    0    0    -1  
$EndComp
Text GLabel 4400 2150 2    60   Input ~ 0
GND
$Comp
L CONN_4 P1
U 1 1 50DB426C
P 1200 3700
F 0 "P1" V 1150 3700 50  0000 C CNN
F 1 "CONN_4" V 1250 3700 50  0000 C CNN
	1    1200 3700
	-1   0    0    -1  
$EndComp
$Comp
L CONN_2 P2
U 1 1 50DB4209
P 1250 2500
F 0 "P2" V 1200 2500 40  0000 C CNN
F 1 "CONN_2" V 1300 2500 40  0000 C CNN
	1    1250 2500
	-1   0    0    1   
$EndComp
Text GLabel 4400 3350 2    60   Input ~ 0
GND
Text GLabel 4350 4450 2    60   Input ~ 0
GND
Text GLabel 4300 5650 2    60   Input ~ 0
GND
Text GLabel 3000 2050 0    60   Input ~ 0
GND
Text GLabel 3000 1850 0    60   Input ~ 0
VCC
$Comp
L RELAY K3
U 1 1 50DB3D98
P 3700 5400
F 0 "K3" H 3650 5550 70  0000 C CNN
F 1 "RELAY" H 3850 4900 70  0000 C CNN
	1    3700 5400
	-1   0    0    -1  
$EndComp
$Comp
L RELAY K2
U 1 1 50DB3D95
P 3700 4200
F 0 "K2" H 3650 4350 70  0000 C CNN
F 1 "RELAY" H 3850 3700 70  0000 C CNN
	1    3700 4200
	-1   0    0    -1  
$EndComp
$Comp
L RELAY K1
U 1 1 50DB3D92
P 3700 3100
F 0 "K1" H 3650 3250 70  0000 C CNN
F 1 "RELAY" H 3850 2600 70  0000 C CNN
	1    3700 3100
	-1   0    0    -1  
$EndComp
$Comp
L RELAY K4
U 1 1 50DB3D87
P 3650 1900
F 0 "K4" H 3600 2050 70  0000 C CNN
F 1 "RELAY" H 3800 1400 70  0000 C CNN
	1    3650 1900
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
