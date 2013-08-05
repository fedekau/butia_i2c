EESchema Schematic File Version 2  date lun 05 ago 2013 18:19:11 UYT
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
LIBS:lm35
LIBS:temperatura-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "5 aug 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LM35 U1
U 1 1 51FFF87D
P 4050 1400
F 0 "U1" H 4000 1600 60  0000 L CNN
F 1 "LM35" H 4000 1150 60  0000 L CNN
F 2 "" H 4050 1400 60  0000 C CNN
F 3 "" H 4050 1400 60  0000 C CNN
	1    4050 1400
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 51FFF896
P 2050 2550
F 0 "R1" V 2130 2550 40  0000 C CNN
F 1 "1.2 kΩ" V 2057 2551 40  0000 C CNN
F 2 "~" V 1980 2550 30  0000 C CNN
F 3 "~" H 2050 2550 30  0000 C CNN
	1    2050 2550
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J1
U 1 1 51FFF8A5
P 2200 1450
F 0 "J1" H 2400 1950 60  0000 C CNN
F 1 "RJ45" H 2050 1950 60  0000 C CNN
F 2 "~" H 2200 1450 60  0000 C CNN
F 3 "~" H 2200 1450 60  0000 C CNN
	1    2200 1450
	1    0    0    -1  
$EndComp
$Comp
L CAPAPOL C1
U 1 1 51FFFDA5
P 2900 1500
F 0 "C1" H 2950 1600 40  0000 L CNN
F 1 "0.01uf" H 2950 1400 40  0000 L CNN
F 2 "~" H 3000 1350 30  0000 C CNN
F 3 "~" H 2900 1500 300 0000 C CNN
	1    2900 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1300 2900 1300
Wire Wire Line
	2900 1700 3550 1700
Wire Wire Line
	3550 1700 3550 1500
Wire Wire Line
	2050 1900 2050 2300
Connection ~ 2050 2050
Wire Wire Line
	1900 2050 2050 2050
Text GLabel 1900 2050 0    60   Input ~ 0
Vcc
Text GLabel 3300 1100 1    60   Input ~ 0
Vcc
Wire Wire Line
	3300 1100 3300 1300
Connection ~ 3300 1300
Text GLabel 2250 2150 3    60   Input ~ 0
GND
Wire Wire Line
	2250 1900 2250 2150
Text GLabel 3300 1950 3    60   Input ~ 0
GND
Wire Wire Line
	3300 1950 3300 1700
Connection ~ 3300 1700
Text GLabel 2350 2000 3    60   Input ~ 0
AN
Text GLabel 4700 1400 2    60   Input ~ 0
AN
Wire Wire Line
	4700 1400 4550 1400
Wire Wire Line
	2350 2000 2350 1900
Wire Wire Line
	2150 1900 2150 2900
Wire Wire Line
	2050 2800 2050 3050
Text GLabel 2050 3050 3    60   Input ~ 0
idAN
Wire Wire Line
	2150 2900 2050 2900
Connection ~ 2050 2900
$EndSCHEMATC
