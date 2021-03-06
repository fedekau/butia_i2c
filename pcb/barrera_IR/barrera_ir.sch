EESchema Schematic File Version 2  date mar 25 jun 2013 20:22:33 UYT
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
LIBS:barrera_ir-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Barrera infrarojo para detectar movimiento"
Date "25 jun 2013"
Rev "1.2"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DIN_5 P1
U 1 1 518C1FAA
P 4350 3850
F 0 "P1" H 4350 3850 70  0000 C CNN
F 1 "DIN_5" H 4350 3700 70  0000 C CNN
	1    4350 3850
	1    0    0    -1  
$EndComp
Text GLabel 4900 2650 0    60   Input ~ 0
Vcc
$Comp
L +5V #PWR01
U 1 1 518C2B09
P 5400 2650
F 0 "#PWR01" H 5400 2740 20  0001 C CNN
F 1 "+5V" H 5400 2740 30  0000 C CNN
	1    5400 2650
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 518C2B28
P 5150 2650
F 0 "#FLG02" H 5150 2745 30  0001 C CNN
F 1 "PWR_FLAG" H 5150 2830 30  0000 C CNN
	1    5150 2650
	1    0    0    -1  
$EndComp
Text GLabel 2600 3850 0    60   Input ~ 0
GND
Text GLabel 2600 3650 0    60   Input ~ 0
Vcc
$Comp
L R R1
U 1 1 518C3124
P 3100 3650
F 0 "R1" V 3180 3650 50  0000 C CNN
F 1 "390" V 3100 3650 50  0000 C CNN
	1    3100 3650
	0    1    1    0   
$EndComp
NoConn ~ 4950 3650
NoConn ~ 4950 3850
$Comp
L R R3
U 1 1 518C45A4
P 6150 3750
F 0 "R3" V 6230 3750 50  0000 C CNN
F 1 "1K" V 6150 3750 50  0000 C CNN
	1    6150 3750
	0    1    -1   0   
$EndComp
Text GLabel 8300 3050 2    60   Input ~ 0
AN
$Comp
L DIODE D1
U 1 1 518C46CB
P 7450 3050
F 0 "D1" H 7450 3150 40  0000 C CNN
F 1 "1N4148" H 7450 2950 40  0000 C CNN
	1    7450 3050
	1    0    0    -1  
$EndComp
$Comp
L LM358N U1
U 1 1 519572D9
P 6200 3050
F 0 "U1" H 6150 3250 60  0000 L CNN
F 1 "LM358N" H 6150 2800 60  0000 L CNN
	1    6200 3050
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 51957D6C
P 5700 4000
F 0 "R2" V 5780 4000 50  0000 C CNN
F 1 "1K" V 5700 4000 50  0000 C CNN
	1    5700 4000
	-1   0    0    -1  
$EndComp
Text GLabel 5400 4250 0    60   Input ~ 0
GND
Text GLabel 6200 3450 2    60   Input ~ 0
GND
$Comp
L DIN_5 P2
U 1 1 51957F51
P 4350 5900
F 0 "P2" H 4350 5900 70  0000 C CNN
F 1 "DIN_5" H 4350 5750 70  0000 C CNN
	1    4350 5900
	1    0    0    -1  
$EndComp
Text GLabel 4900 4700 0    60   Input ~ 0
Vcc
Text GLabel 2600 5900 0    60   Input ~ 0
GND
Text GLabel 2600 5700 0    60   Input ~ 0
Vcc
$Comp
L R R4
U 1 1 51957F68
P 3100 5700
F 0 "R4" V 3180 5700 50  0000 C CNN
F 1 "390" V 3100 5700 50  0000 C CNN
	1    3100 5700
	0    1    1    0   
$EndComp
NoConn ~ 4950 5700
NoConn ~ 4950 5900
$Comp
L R R6
U 1 1 51957F70
P 6150 5800
F 0 "R6" V 6230 5800 50  0000 C CNN
F 1 "1K" V 6150 5800 50  0000 C CNN
	1    6150 5800
	0    1    -1   0   
$EndComp
$Comp
L DIODE D2
U 1 1 51957F77
P 7450 5100
F 0 "D2" H 7450 5200 40  0000 C CNN
F 1 "1N4148" H 7450 5000 40  0000 C CNN
	1    7450 5100
	1    0    0    -1  
$EndComp
$Comp
L LM358N U1
U 2 1 51957F82
P 6200 5100
F 0 "U1" H 6150 5300 60  0000 L CNN
F 1 "LM358N" H 6150 4850 60  0000 L CNN
	2    6200 5100
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 51957F88
P 5700 6050
F 0 "R5" V 5780 6050 50  0000 C CNN
F 1 "1K" V 5700 6050 50  0000 C CNN
	1    5700 6050
	-1   0    0    -1  
$EndComp
Text GLabel 5250 6300 0    60   Input ~ 0
GND
Text GLabel 6200 5500 2    60   Input ~ 0
GND
$Comp
L R R7
U 1 1 51957F9B
P 7950 5550
F 0 "R7" V 8030 5550 50  0000 C CNN
F 1 "1K" V 7950 5550 50  0000 C CNN
	1    7950 5550
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 519581B9
P 5450 6400
F 0 "#PWR03" H 5450 6400 30  0001 C CNN
F 1 "GND" H 5450 6330 30  0001 C CNN
	1    5450 6400
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 51958285
P 5450 6300
F 0 "#FLG04" H 5450 6395 30  0001 C CNN
F 1 "PWR_FLAG" H 5450 6480 30  0000 C CNN
	1    5450 6300
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J1
U 1 1 519588D1
P 9300 3950
F 0 "J1" H 9500 4450 60  0000 C CNN
F 1 "RJ45" H 9150 4450 60  0000 C CNN
F 2 "~" H 9300 3950 60  0000 C CNN
F 3 "~" H 9300 3950 60  0000 C CNN
	1    9300 3950
	1    0    0    -1  
$EndComp
Text GLabel 9150 4650 3    60   Input ~ 0
Vcc
Text GLabel 9350 4650 3    60   Input ~ 0
GND
Text GLabel 9250 5000 3    60   Input ~ 0
idAN
Text GLabel 9450 5000 3    60   Input ~ 0
AN
Connection ~ 5150 2650
Wire Wire Line
	7650 3050 8300 3050
Connection ~ 5400 2650
Wire Wire Line
	3350 3650 3750 3650
Wire Wire Line
	2600 3650 2850 3650
Wire Wire Line
	2600 3850 3750 3850
Wire Wire Line
	5700 3150 5700 3750
Wire Wire Line
	5700 3750 5900 3750
Wire Wire Line
	6400 3750 6700 3750
Wire Wire Line
	5400 4250 5700 4250
Wire Wire Line
	6700 3050 7250 3050
Wire Wire Line
	4900 4700 6100 4700
Wire Wire Line
	7950 5100 7650 5100
Wire Wire Line
	3350 5700 3750 5700
Wire Wire Line
	2600 5700 2850 5700
Wire Wire Line
	2600 5900 3750 5900
Wire Wire Line
	5700 5200 5700 5800
Wire Wire Line
	5700 5800 5900 5800
Wire Wire Line
	6400 5800 6700 5800
Wire Wire Line
	6100 5500 6200 5500
Wire Wire Line
	6700 5100 7250 5100
Wire Wire Line
	7950 3050 7950 5300
Connection ~ 7950 3050
Wire Wire Line
	6100 3450 6200 3450
Wire Wire Line
	5450 6400 5450 6300
Wire Wire Line
	5250 6300 5700 6300
Connection ~ 5450 6300
Wire Wire Line
	9150 4400 9150 4650
Wire Wire Line
	9350 4400 9350 4650
Wire Wire Line
	9250 4400 9250 5000
Wire Wire Line
	9450 4400 9450 5000
NoConn ~ 9850 3600
NoConn ~ 8950 4400
NoConn ~ 9050 4400
NoConn ~ 9550 4400
NoConn ~ 9650 4400
$Comp
L R R8
U 1 1 51958DF0
P 9300 5700
F 0 "R8" V 9380 5700 50  0000 C CNN
F 1 "4K7" V 9300 5700 50  0000 C CNN
	1    9300 5700
	0    1    -1   0   
$EndComp
Text GLabel 8850 5700 0    60   Input ~ 0
Vcc
Wire Wire Line
	8850 5700 9050 5700
Text GLabel 9750 5700 2    60   Input ~ 0
idAN
Wire Wire Line
	9750 5700 9550 5700
Wire Wire Line
	4350 5300 4350 5000
Wire Wire Line
	4350 5000 5700 5000
Wire Wire Line
	4350 2950 5700 2950
Wire Wire Line
	4350 2950 4350 3250
Wire Wire Line
	4900 2650 6100 2650
Connection ~ 7950 5100
Text GLabel 7750 5800 0    60   Input ~ 0
GND
Wire Wire Line
	7750 5800 7950 5800
Text GLabel 6700 3750 2    60   Input ~ 0
Vcc
Text GLabel 6700 5800 2    60   Input ~ 0
Vcc
$EndSCHEMATC
