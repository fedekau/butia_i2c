EESchema Schematic File Version 2  date Thu 20 Jun 2013 06:34:06 PM UYT
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
LIBS:l298hn-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "H-Bridge L298HN"
Date "20 jun 2013"
Rev "1.0"
Comp "Butia 2.0"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DIODE D8
U 1 1 513961AA
P 8850 4200
F 0 "D8" H 8850 4300 40  0000 C CNN
F 1 "DIODE" H 8850 4100 40  0000 C CNN
F 2 "" H 8850 4200 60  0001 C CNN
F 3 "" H 8850 4200 60  0001 C CNN
	1    8850 4200
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D7
U 1 1 513961A8
P 8600 4200
F 0 "D7" H 8600 4300 40  0000 C CNN
F 1 "DIODE" H 8600 4100 40  0000 C CNN
F 2 "" H 8600 4200 60  0001 C CNN
F 3 "" H 8600 4200 60  0001 C CNN
	1    8600 4200
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D5
U 1 1 513961A6
P 8600 2900
F 0 "D5" H 8600 3000 40  0000 C CNN
F 1 "DIODE" H 8600 2800 40  0000 C CNN
F 2 "" H 8600 2900 60  0001 C CNN
F 3 "" H 8600 2900 60  0001 C CNN
	1    8600 2900
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D6
U 1 1 513961A3
P 8850 2900
F 0 "D6" H 8850 3000 40  0000 C CNN
F 1 "DIODE" H 8850 2800 40  0000 C CNN
F 2 "" H 8850 2900 60  0001 C CNN
F 3 "" H 8850 2900 60  0001 C CNN
	1    8850 2900
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D4
U 1 1 5139617E
P 8050 4200
F 0 "D4" H 8050 4300 40  0000 C CNN
F 1 "DIODE" H 8050 4100 40  0000 C CNN
F 2 "" H 8050 4200 60  0001 C CNN
F 3 "" H 8050 4200 60  0001 C CNN
	1    8050 4200
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D3
U 1 1 5139617B
P 7800 4200
F 0 "D3" H 7800 4300 40  0000 C CNN
F 1 "DIODE" H 7800 4100 40  0000 C CNN
F 2 "" H 7800 4200 60  0001 C CNN
F 3 "" H 7800 4200 60  0001 C CNN
	1    7800 4200
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D1
U 1 1 51396178
P 7800 2900
F 0 "D1" H 7800 3000 40  0000 C CNN
F 1 "DIODE" H 7800 2800 40  0000 C CNN
F 2 "" H 7800 2900 60  0001 C CNN
F 3 "" H 7800 2900 60  0001 C CNN
	1    7800 2900
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D2
U 1 1 51396175
P 8050 2900
F 0 "D2" H 8050 3000 40  0000 C CNN
F 1 "DIODE" H 8050 2800 40  0000 C CNN
F 2 "" H 8050 2900 60  0001 C CNN
F 3 "" H 8050 2900 60  0001 C CNN
	1    8050 2900
	0    -1   -1   0   
$EndComp
Text GLabel 5700 4750 0    60   Input ~ 0
GND
Text GLabel 6250 2300 0    60   Input ~ 0
GND
$Comp
L CONN_2 P2
U 1 1 51395CA9
P 3950 1550
F 0 "P2" V 3900 1550 40  0000 C CNN
F 1 "PWR" V 4000 1550 40  0000 C CNN
F 2 "" H 3950 1550 60  0001 C CNN
F 3 "" H 3950 1550 60  0001 C CNN
	1    3950 1550
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 MOT2
U 1 1 51395CA6
P 3700 4750
F 0 "MOT2" V 3650 4750 40  0000 C CNN
F 1 "CONN_2" V 3750 4750 40  0000 C CNN
F 2 "" H 3700 4750 60  0001 C CNN
F 3 "" H 3700 4750 60  0001 C CNN
	1    3700 4750
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 MOT1
U 1 1 51395C9B
P 3700 4350
F 0 "MOT1" V 3650 4350 40  0000 C CNN
F 1 "CONN_2" V 3750 4350 40  0000 C CNN
F 2 "" H 3700 4350 60  0001 C CNN
F 3 "" H 3700 4350 60  0001 C CNN
	1    3700 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_2X2 P1
U 1 1 5141B785
P 3350 5550
F 0 "P1" H 3350 5700 50  0000 C CNN
F 1 "CONN_2X2" H 3360 5420 40  0000 C CNN
F 2 "" H 3350 5550 60  0001 C CNN
F 3 "" H 3350 5550 60  0001 C CNN
	1    3350 5550
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 5141B794
P 2850 2400
F 0 "K1" V 2800 2400 50  0000 C CNN
F 1 "CONN_3" V 2900 2400 40  0000 C CNN
F 2 "" H 2850 2400 60  0001 C CNN
F 3 "" H 2850 2400 60  0001 C CNN
	1    2850 2400
	-1   0    0    1   
$EndComp
NoConn ~ 3200 2400
Text GLabel 2950 1650 0    60   Input ~ 0
Vcc_12
$Comp
L +5V #PWR01
U 1 1 5141C3E0
P 3600 2300
F 0 "#PWR01" H 3600 2390 20  0001 C CNN
F 1 "+5V" H 3600 2390 30  0000 C CNN
F 2 "" H 3600 2300 60  0001 C CNN
F 3 "" H 3600 2300 60  0001 C CNN
	1    3600 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5141C437
P 3650 2600
F 0 "#PWR02" H 3650 2600 30  0001 C CNN
F 1 "GND" H 3650 2530 30  0001 C CNN
F 2 "" H 3650 2600 60  0001 C CNN
F 3 "" H 3650 2600 60  0001 C CNN
	1    3650 2600
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 5141C97A
P 3400 2500
F 0 "#FLG03" H 3400 2595 30  0001 C CNN
F 1 "PWR_FLAG" H 3400 2680 30  0000 C CNN
F 2 "" H 3400 2500 60  0001 C CNN
F 3 "" H 3400 2500 60  0001 C CNN
	1    3400 2500
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 5141CEF1
P 3400 2300
F 0 "#FLG04" H 3400 2395 30  0001 C CNN
F 1 "PWR_FLAG" H 3400 2480 30  0000 C CNN
F 2 "" H 3400 2300 60  0001 C CNN
F 3 "" H 3400 2300 60  0001 C CNN
	1    3400 2300
	1    0    0    -1  
$EndComp
Text GLabel 6250 2700 0    60   Input ~ 0
Vcc
Text GLabel 3800 2300 2    60   Input ~ 0
Vcc
Text GLabel 9200 2700 2    60   Input ~ 0
Vcc_12
$Comp
L PWR_FLAG #FLG05
U 1 1 51435B1B
P 3350 1650
F 0 "#FLG05" H 3350 1745 30  0001 C CNN
F 1 "PWR_FLAG" H 3350 1830 30  0000 C CNN
F 2 "" H 3350 1650 60  0001 C CNN
F 3 "" H 3350 1650 60  0001 C CNN
	1    3350 1650
	-1   0    0    1   
$EndComp
Text GLabel 3200 1450 0    60   Input ~ 0
GND
Text GLabel 3800 2500 2    60   Input ~ 0
GND
Text GLabel 2700 5450 0    60   Input ~ 0
IN1
Text GLabel 3950 5450 2    60   Input ~ 0
IN2
Text GLabel 2700 5650 0    60   Input ~ 0
IN3
Text GLabel 3950 5650 2    60   Input ~ 0
IN4
Text GLabel 5700 3300 0    60   Input ~ 0
IN1
Text GLabel 5700 3400 0    60   Input ~ 0
IN2
Text GLabel 5700 3500 0    60   Input ~ 0
IN3
Text GLabel 5700 3600 0    60   Input ~ 0
IN4
$Comp
L CONN_2 P3
U 1 1 515DD4A6
P 3750 6200
F 0 "P3" V 3700 6200 40  0000 C CNN
F 1 "CONN_2" V 3800 6200 40  0000 C CNN
F 2 "" H 3750 6200 60  0001 C CNN
F 3 "" H 3750 6200 60  0001 C CNN
	1    3750 6200
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P4
U 1 1 515DD4BA
P 3750 6650
F 0 "P4" V 3700 6650 40  0000 C CNN
F 1 "CONN_2" V 3800 6650 40  0000 C CNN
F 2 "" H 3750 6650 60  0001 C CNN
F 3 "" H 3750 6650 60  0001 C CNN
	1    3750 6650
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K2
U 1 1 515DD4E0
P 3900 3250
F 0 "K2" V 3850 3250 50  0000 C CNN
F 1 "CONN_3" V 3950 3250 40  0000 C CNN
F 2 "" H 3900 3250 60  0001 C CNN
F 3 "" H 3900 3250 60  0001 C CNN
	1    3900 3250
	1    0    0    -1  
$EndComp
Text GLabel 3200 3350 0    60   Input ~ 0
HK17
Text GLabel 3200 3250 0    60   Input ~ 0
HK16
Text GLabel 3200 3150 0    60   Input ~ 0
HK15
$Comp
L L298 U1
U 1 1 515DD8EC
P 6950 3600
F 0 "U1" H 6468 4335 50  0000 L BNN
F 1 "L298" H 6491 2952 50  0000 L BNN
F 2 "drivers_motor" H 6950 3750 50  0001 C CNN
F 3 "~" H 6950 3600 60  0000 C CNN
	1    6950 3600
	1    0    0    -1  
$EndComp
NoConn ~ 3400 6550
$Comp
L C C2
U 1 1 516968B9
P 7550 2500
F 0 "C2" H 7550 2600 40  0000 L CNN
F 1 "100nF" H 7556 2415 40  0000 L CNN
F 2 "~" H 7588 2350 30  0000 C CNN
F 3 "~" H 7550 2500 60  0000 C CNN
	1    7550 2500
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 516968DD
P 6500 2500
F 0 "C1" H 6500 2600 40  0000 L CNN
F 1 "100nF" H 6506 2415 40  0000 L CNN
F 2 "~" H 6538 2350 30  0000 C CNN
F 3 "~" H 6500 2500 60  0000 C CNN
	1    6500 2500
	1    0    0    -1  
$EndComp
Text GLabel 5700 3700 0    60   Input ~ 0
EnA
Text GLabel 5700 3800 0    60   Input ~ 0
EnB
Text GLabel 3050 6300 0    60   Input ~ 0
EnA
Text GLabel 3050 6750 0    60   Input ~ 0
EnB
Connection ~ 8600 4750
Wire Wire Line
	8850 4750 8850 4400
Connection ~ 7800 4750
Wire Wire Line
	8050 4750 8050 4400
Wire Wire Line
	7800 3100 7800 4000
Wire Wire Line
	8600 3100 8600 4000
Connection ~ 8850 3800
Connection ~ 8050 3400
Wire Wire Line
	7050 4750 7050 4500
Wire Wire Line
	7650 3200 9100 3200
Wire Wire Line
	7650 3600 9100 3600
Wire Wire Line
	7650 3800 9100 3800
Wire Wire Line
	7650 3400 9100 3400
Wire Wire Line
	7250 4750 7250 4500
Connection ~ 7050 4750
Connection ~ 7800 3200
Connection ~ 8600 3600
Wire Wire Line
	8850 3100 8850 4000
Wire Wire Line
	8050 3100 8050 4000
Wire Wire Line
	7800 4750 7800 4400
Connection ~ 7250 4750
Wire Wire Line
	8600 4750 8600 4400
Connection ~ 8050 4750
Connection ~ 8850 2700
Connection ~ 8600 2700
Connection ~ 8050 2700
Connection ~ 7800 2700
Wire Wire Line
	7350 2700 9200 2700
Wire Wire Line
	3200 2300 3800 2300
Connection ~ 3600 2300
Wire Wire Line
	3400 2300 3600 2300
Connection ~ 3400 2300
Wire Wire Line
	2950 1650 3600 1650
Connection ~ 3350 1650
Wire Wire Line
	5700 4750 8850 4750
Wire Wire Line
	3200 1450 3600 1450
Wire Wire Line
	3200 2500 3800 2500
Connection ~ 3400 2500
Wire Wire Line
	3650 2600 3650 2500
Connection ~ 3650 2500
Wire Wire Line
	2700 5450 2950 5450
Wire Wire Line
	2950 5450 2950 5500
Wire Wire Line
	2700 5650 2950 5650
Wire Wire Line
	2950 5650 2950 5600
Wire Wire Line
	3950 5450 3750 5450
Wire Wire Line
	3750 5450 3750 5500
Wire Wire Line
	3950 5650 3750 5650
Wire Wire Line
	3750 5650 3750 5600
Wire Wire Line
	5700 3300 6250 3300
Wire Wire Line
	5700 3400 6250 3400
Wire Wire Line
	5700 3500 6250 3500
Wire Wire Line
	5700 3600 6250 3600
Wire Wire Line
	3200 3250 3550 3250
Wire Wire Line
	3200 3350 3550 3350
Wire Wire Line
	3350 3700 3200 3700
Connection ~ 3350 3350
Wire Wire Line
	6250 2700 6850 2700
Connection ~ 6500 2700
Wire Wire Line
	6250 2300 7550 2300
Wire Wire Line
	7050 2300 7050 2700
Connection ~ 6500 2300
Connection ~ 7550 2700
Connection ~ 7050 2300
Wire Wire Line
	5700 3700 6250 3700
Wire Wire Line
	5700 3800 6250 3800
Wire Wire Line
	3050 6750 3400 6750
Wire Wire Line
	3050 6300 3400 6300
Wire Wire Line
	3200 3150 3550 3150
Wire Wire Line
	3350 3350 3350 3700
NoConn ~ 3400 6100
Text GLabel 3200 4250 0    60   Input ~ 0
OUT1
Text GLabel 9100 3200 2    60   Input ~ 0
OUT1
Wire Wire Line
	3200 4250 3350 4250
Text GLabel 9100 3400 2    60   Input ~ 0
OUT2
Text GLabel 9100 3600 2    60   Input ~ 0
OUT3
Text GLabel 9100 3800 2    60   Input ~ 0
OUT4
Text GLabel 3200 4450 0    60   Input ~ 0
OUT2
Text GLabel 3200 4650 0    60   Input ~ 0
OUT3
Text GLabel 3200 4850 0    60   Input ~ 0
OUT4
Wire Wire Line
	3200 4450 3350 4450
Wire Wire Line
	3200 4650 3350 4650
Wire Wire Line
	3200 4850 3350 4850
Text GLabel 3200 3700 0    60   Input ~ 0
Vcc
Text GLabel 3200 2950 0    60   Input ~ 0
GND
Wire Wire Line
	3200 2950 3350 2950
Wire Wire Line
	3350 2950 3350 3250
Connection ~ 3350 3150
Connection ~ 3350 3250
$EndSCHEMATC
