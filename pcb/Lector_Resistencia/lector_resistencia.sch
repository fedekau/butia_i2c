EESchema Schematic File Version 2  date jue 08 nov 2012 19:04:57 UYST
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
LIBS:lector_resistencia-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title "Módulo medidor de resistencias "
Date "7 nov 2012"
Rev "1.0"
Comp "Butiá"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3350 4850 3350 5000
Connection ~ 3350 4350
Connection ~ 3900 4350
Wire Wire Line
	3350 4350 3900 4350
Wire Wire Line
	7000 4550 7350 4550
Wire Wire Line
	4300 3350 4300 3700
Wire Wire Line
	4300 4200 4300 4500
Wire Wire Line
	3900 4200 3900 4500
Wire Wire Line
	6050 3200 5750 3200
Wire Wire Line
	5250 4000 5250 4350
Wire Wire Line
	5050 4000 5050 4400
Wire Wire Line
	5150 4000 5150 4800
Wire Wire Line
	5350 4000 5350 4700
Wire Wire Line
	3900 3350 3900 3700
Wire Wire Line
	7000 4450 7300 4450
Wire Wire Line
	3350 4250 3350 4450
Wire Wire Line
	3350 3850 3350 3700
Wire Wire Line
	3350 3700 3900 3700
Text GLabel 3350 5000 3    60   Input ~ 0
GND
$Comp
L DIODE D2
U 1 1 50998BA7
P 3350 4650
F 0 "D2" H 3350 4750 40  0000 C CNN
F 1 "1N4148" H 3350 4550 40  0000 C CNN
	1    3350 4650
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D1
U 1 1 50998B85
P 3350 4050
F 0 "D1" H 3350 4150 40  0000 C CNN
F 1 "1N4148" H 3350 3950 40  0000 C CNN
	1    3350 4050
	0    -1   -1   0   
$EndComp
NoConn ~ 7000 4350
NoConn ~ 7000 4650
NoConn ~ 7000 4250
$Comp
L JACK_5P J2
U 1 1 50998707
P 6550 4450
F 0 "J2" H 6200 4250 60  0000 C CNN
F 1 "JACK_5P" H 6400 4750 60  0000 C CNN
	1    6550 4450
	1    0    0    -1  
$EndComp
NoConn ~ 5550 4000
NoConn ~ 5450 4000
NoConn ~ 4950 4000
NoConn ~ 4850 4000
Text GLabel 7350 4550 2    50   Input ~ 0
AN
Text GLabel 7300 4450 2    60   Input ~ 0
GND
Text GLabel 4300 4500 3    60   Input ~ 0
idAN
$Comp
L R R2
U 1 1 50814D04
P 4300 3950
F 0 "R2" V 4380 3950 50  0000 C CNN
F 1 "22k" V 4300 3950 50  0000 C CNN
	1    4300 3950
	1    0    0    -1  
$EndComp
Text GLabel 4300 3350 1    60   Input ~ 0
VDD
Text GLabel 3900 4500 3    60   Input ~ 0
AN
Text GLabel 3900 3350 1    60   Input ~ 0
VDD
Text GLabel 6050 3200 2    60   Input ~ 0
GND
Text GLabel 5350 4700 3    60   Input ~ 0
AN
Text GLabel 5250 4350 3    60   Input ~ 0
GND
Text GLabel 5150 4800 3    60   Input ~ 0
idAN
Text GLabel 5050 4400 3    60   Input ~ 0
VDD
$Comp
L R R1
U 1 1 50814352
P 3900 3950
F 0 "R1" V 3980 3950 50  0000 C CNN
F 1 "6K8" V 3900 3950 50  0000 C CNN
	1    3900 3950
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J1
U 1 1 50814171
P 5200 3550
F 0 "J1" H 5400 4050 60  0000 C CNN
F 1 "RJ45" H 5050 4050 60  0000 C CNN
	1    5200 3550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
