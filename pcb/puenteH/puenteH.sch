EESchema Schematic File Version 2  date vie 21 dic 2012 21:28:10 UYST
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
LIBS:puenteH-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title "Puente H para motores CC"
Date "21 dec 2012"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1900 4300 1100 4300
Wire Notes Line
	9120 470  9120 7200
Wire Wire Line
	6450 3100 6450 3200
Wire Wire Line
	5950 3100 5800 3100
Wire Wire Line
	6450 4300 6450 4450
Wire Wire Line
	5800 4800 5800 4450
Wire Wire Line
	3150 4300 3150 4450
Wire Wire Line
	4300 4800 4300 4650
Wire Wire Line
	3800 4450 3650 4450
Wire Wire Line
	1100 3500 1900 3500
Wire Wire Line
	3800 2750 3650 2750
Wire Wire Line
	3650 2750 3650 3100
Wire Wire Line
	5100 2750 4500 2750
Wire Wire Line
	7700 3500 8550 3500
Wire Wire Line
	6450 3500 6450 3650
Wire Wire Line
	3150 3500 3150 3650
Wire Wire Line
	7700 4000 7850 4000
Wire Wire Line
	1750 4000 1900 4000
Wire Wire Line
	1750 3200 1900 3200
Wire Wire Line
	5400 3300 5100 3300
Wire Wire Line
	5100 3300 5100 4250
Wire Wire Line
	4500 4250 4500 3300
Wire Wire Line
	4700 5400 4900 5400
Connection ~ 4800 4800
Wire Wire Line
	4800 4900 4800 4800
Wire Wire Line
	4500 4800 5100 4800
Wire Wire Line
	4500 4800 4500 4650
Wire Wire Line
	5100 2750 5100 2900
Wire Wire Line
	5100 4650 5300 4650
Wire Wire Line
	4500 4250 4200 4250
Wire Wire Line
	4500 2900 4300 2900
Wire Wire Line
	5100 2900 5300 2900
Wire Wire Line
	4500 3300 4200 3300
Wire Wire Line
	5100 4250 5400 4250
Wire Wire Line
	4500 4650 4300 4650
Wire Wire Line
	5100 4650 5100 4800
Wire Wire Line
	4500 2900 4500 2750
Wire Wire Line
	4800 2600 4800 2750
Connection ~ 4800 2750
Wire Wire Line
	4700 5600 4900 5600
Wire Wire Line
	4600 3750 4500 3750
Connection ~ 4500 3750
Wire Wire Line
	5000 3750 5100 3750
Connection ~ 5100 3750
Wire Wire Line
	7700 3200 7850 3200
Wire Wire Line
	3150 3900 3150 4000
Wire Wire Line
	6450 3900 6450 4000
Wire Wire Line
	8550 4000 8350 4000
Wire Wire Line
	1100 4000 1250 4000
Wire Wire Line
	8350 3200 8550 3200
Wire Wire Line
	3650 3100 3800 3100
Wire Wire Line
	1100 3200 1250 3200
Wire Wire Line
	3650 4450 3650 4800
Wire Wire Line
	3650 4800 3800 4800
Wire Wire Line
	4300 2900 4300 2750
Wire Wire Line
	5800 4450 5950 4450
Wire Wire Line
	5300 4650 5300 4800
Wire Wire Line
	5800 3100 5800 2750
Wire Wire Line
	5300 2900 5300 2750
Wire Wire Line
	3150 3100 3150 3200
Wire Wire Line
	7700 4300 8550 4300
Text Notes 9250 2300 0    60   ~ 0
Nota: Con esta configuración de pines, \nobservar que no hay estados prohibidos, \no sea que nunca conducen a la vez un \ntransitor PNP con uno NPN que pongan \nen corto circutito fuente con tierra.
Text Notes 10500 1600 0    60   ~ 0
Freno motor
Text Notes 9400 1600 0    60   ~ 0
1
Text Notes 9750 1600 0    60   ~ 0
1
Text Notes 10100 1600 0    60   ~ 0
0
Text Notes 10500 1900 0    60   ~ 0
Fijo
Text Notes 10100 1900 0    60   ~ 0
1
Text Notes 9750 1900 0    60   ~ 0
X
Text Notes 9400 1900 0    60   ~ 0
X
Text Notes 10500 1750 0    60   ~ 0
Fijo
Text Notes 10100 1750 0    60   ~ 0
X
Text Notes 9750 1750 0    60   ~ 0
0
Text Notes 9400 1750 0    60   ~ 0
0
Text Notes 10500 1450 0    60   ~ 0
Atrás
Text Notes 10100 1450 0    60   ~ 0
0
Text Notes 9750 1450 0    60   ~ 0
1
Text Notes 9400 1450 0    60   ~ 0
0
Text Notes 10500 1300 0    60   ~ 0
Adelante
Text Notes 10100 1300 0    60   ~ 0
0
Text Notes 9750 1300 0    60   ~ 0
0
Text Notes 9400 1300 0    60   ~ 0
1
Text Notes 10430 1130 0    60   ~ 0
Movimiento
Text Notes 10080 1130 0    60   ~ 0
En
Text Notes 9720 1130 0    60   ~ 0
Inv
Text Notes 9350 1140 0    60   ~ 0
Dir
Text Notes 9350 770  0    60   ~ 0
Tabla de verdad
Text GLabel 1100 3500 0    60   Input ~ 0
Inv
Text GLabel 8550 3500 2    60   Input ~ 0
Dir
Text GLabel 1100 4000 0    60   Input ~ 0
Inv
Text GLabel 8550 4300 2    60   Input ~ 0
En
Text GLabel 8550 3200 2    60   Input ~ 0
Inv
Text GLabel 8550 4000 2    60   Input ~ 0
Dir
Text GLabel 1100 4300 0    60   Input ~ 0
En
Text GLabel 1100 3200 0    60   Input ~ 0
Dir
$Comp
L VCC #PWR01
U 1 1 50C7B069
P 6450 3900
F 0 "#PWR01" H 6450 4000 30  0001 C CNN
F 1 "VCC" H 6450 4000 30  0000 C CNN
	1    6450 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 50C7B05F
P 6450 3650
F 0 "#PWR02" H 6450 3650 30  0001 C CNN
F 1 "GND" H 6450 3580 30  0001 C CNN
	1    6450 3650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 50C7B04C
P 3150 3900
F 0 "#PWR03" H 3150 4000 30  0001 C CNN
F 1 "VCC" H 3150 4000 30  0000 C CNN
	1    3150 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 50C7B034
P 3150 3650
F 0 "#PWR04" H 3150 3650 30  0001 C CNN
F 1 "GND" H 3150 3580 30  0001 C CNN
	1    3150 3650
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 50C7AECB
P 8100 4000
F 0 "R12" V 8180 4000 50  0000 C CNN
F 1 "470" V 8100 4000 50  0000 C CNN
	1    8100 4000
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 50C7AEBA
P 8100 3200
F 0 "R11" V 8180 3200 50  0000 C CNN
F 1 "470" V 8100 3200 50  0000 C CNN
	1    8100 3200
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 50C7A976
P 1500 3200
F 0 "R1" V 1580 3200 50  0000 C CNN
F 1 "470" V 1500 3200 50  0000 C CNN
	1    1500 3200
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 50C7A94E
P 1500 4000
F 0 "R2" V 1580 4000 50  0000 C CNN
F 1 "470" V 1500 4000 50  0000 C CNN
	1    1500 4000
	0    -1   -1   0   
$EndComp
$Comp
L OPTO-TRANSISTOR4 U3
U 1 1 50C7A839
P 7050 3350
F 0 "U3" H 7250 3600 60  0000 C CNN
F 1 "OPTO-TRANSISTOR4" H 7050 3100 60  0000 C CNN
	1    7050 3350
	-1   0    0    -1  
$EndComp
$Comp
L OPTO-TRANSISTOR4 U1
U 1 1 50C7A810
P 2550 3350
F 0 "U1" H 2750 3600 60  0000 C CNN
F 1 "OPTO-TRANSISTOR4" H 2550 3100 60  0000 C CNN
	1    2550 3350
	1    0    0    -1  
$EndComp
Text GLabel 4600 3750 2    39   Output ~ 0
M+
Text GLabel 4700 5600 0    39   Output ~ 0
M-
Text GLabel 4700 5400 0    39   Output ~ 0
M+
$Comp
L CONN_2 P1
U 1 1 50C7A575
P 5250 5500
F 0 "P1" V 5200 5500 40  0000 C CNN
F 1 "CONN_2" V 5300 5500 40  0000 C CNN
	1    5250 5500
	1    0    0    -1  
$EndComp
Text GLabel 5000 3750 0    39   Output ~ 0
M-
$Comp
L OPTO-TRANSISTOR4 U4
U 1 1 50C79F62
P 7050 4150
F 0 "U4" H 7250 4400 60  0000 C CNN
F 1 "OPTO-TRANSISTOR4" H 7050 3900 60  0000 C CNN
	1    7050 4150
	-1   0    0    -1  
$EndComp
$Comp
L OPTO-TRANSISTOR4 U2
U 1 1 50C79F19
P 2550 4150
F 0 "U2" H 2750 4400 60  0000 C CNN
F 1 "OPTO-TRANSISTOR4" H 2550 3900 60  0000 C CNN
	1    2550 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 50C79DFE
P 4800 4900
F 0 "#PWR05" H 4800 4900 30  0001 C CNN
F 1 "GND" H 4800 4830 30  0001 C CNN
	1    4800 4900
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR06
U 1 1 50C79CA1
P 4800 2600
F 0 "#PWR06" H 4800 2700 30  0001 C CNN
F 1 "VCC" H 4800 2700 30  0000 C CNN
	1    4800 2600
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 50B6917D
P 4050 4800
F 0 "R6" V 4130 4800 50  0000 C CNN
F 1 "10K" V 4050 4800 50  0000 C CNN
	1    4050 4800
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 50B69176
P 4050 2750
F 0 "R5" V 4130 2750 50  0000 C CNN
F 1 "10K" V 4050 2750 50  0000 C CNN
	1    4050 2750
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 50B6915C
P 5550 4800
F 0 "R8" V 5630 4800 50  0000 C CNN
F 1 "10K" V 5550 4800 50  0000 C CNN
	1    5550 4800
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 50B69138
P 5550 2750
F 0 "R7" V 5630 2750 50  0000 C CNN
F 1 "10K" V 5550 2750 50  0000 C CNN
	1    5550 2750
	0    1    1    0   
$EndComp
$Comp
L R R10
U 1 1 50B6908A
P 6200 4450
F 0 "R10" V 6280 4450 50  0000 C CNN
F 1 "1K" V 6200 4450 50  0000 C CNN
	1    6200 4450
	0    1    1    0   
$EndComp
$Comp
L R R9
U 1 1 50B69089
P 6200 3100
F 0 "R9" V 6280 3100 50  0000 C CNN
F 1 "1K" V 6200 3100 50  0000 C CNN
	1    6200 3100
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 50B69053
P 3400 3100
F 0 "R3" V 3480 3100 50  0000 C CNN
F 1 "1K" V 3400 3100 50  0000 C CNN
	1    3400 3100
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 50B69034
P 3400 4450
F 0 "R4" V 3480 4450 50  0000 C CNN
F 1 "1K" V 3400 4450 50  0000 C CNN
	1    3400 4450
	0    1    1    0   
$EndComp
$Comp
L DARL_P Q3
U 1 1 50B68FD6
P 5550 3050
F 0 "Q3" H 5550 3300 50  0000 C CNN
F 1 "DARL_P" H 5350 2950 50  0000 C CNN
	1    5550 3050
	-1   0    0    1   
$EndComp
$Comp
L DARL_P Q1
U 1 1 50B68FBD
P 4050 3050
F 0 "Q1" H 4050 3300 50  0000 C CNN
F 1 "DARL_P" H 3850 2950 50  0000 C CNN
	1    4050 3050
	1    0    0    1   
$EndComp
$Comp
L DARL_N Q4
U 1 1 50B68A06
P 5550 4500
F 0 "Q4" H 5550 4750 50  0000 C CNN
F 1 "DARL_N" H 5350 4400 50  0000 C CNN
	1    5550 4500
	-1   0    0    -1  
$EndComp
$Comp
L DARL_N Q2
U 1 1 50B689ED
P 4050 4500
F 0 "Q2" H 4050 4750 50  0000 C CNN
F 1 "DARL_N" H 3850 4400 50  0000 C CNN
	1    4050 4500
	1    0    0    -1  
$EndComp
$Comp
L DIODE D2
U 1 1 50B53F36
P 4500 4450
F 0 "D2" H 4500 4550 40  0000 C CNN
F 1 "DIODE" H 4500 4350 40  0000 C CNN
	1    4500 4450
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D4
U 1 1 50B53F35
P 5100 4450
F 0 "D4" H 5100 4550 40  0000 C CNN
F 1 "DIODE" H 5100 4350 40  0000 C CNN
	1    5100 4450
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D3
U 1 1 50B53F1B
P 5100 3100
F 0 "D3" H 5100 3200 40  0000 C CNN
F 1 "DIODE" H 5100 3000 40  0000 C CNN
	1    5100 3100
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D1
U 1 1 50B53F09
P 4500 3100
F 0 "D1" H 4500 3200 40  0000 C CNN
F 1 "DIODE" H 4500 3000 40  0000 C CNN
	1    4500 3100
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
