EESchema Schematic File Version 2  date mar 30 jul 2013 19:17:07 UYT
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
LIBS:sensor_ir-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Sensor Infra-Rojo"
Date "30 jul 2013"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LM358N U1
U 1 1 51F068BE
P 6850 3700
F 0 "U1" H 6800 3900 60  0000 L CNN
F 1 "LM358N" H 6800 3450 60  0000 L CNN
	1    6850 3700
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 51F068E8
P 6750 4350
F 0 "R3" V 6830 4350 40  0000 C CNN
F 1 "1M" V 6757 4351 40  0000 C CNN
F 2 "~" V 6680 4350 30  0000 C CNN
F 3 "~" H 6750 4350 30  0000 C CNN
	1    6750 4350
	0    -1   -1   0   
$EndComp
Text GLabel 6000 3600 0    60   Input ~ 0
GND
Wire Wire Line
	6000 3600 6350 3600
Wire Wire Line
	6350 3800 6350 4600
Wire Wire Line
	6350 4350 6500 4350
Wire Wire Line
	7350 3700 7350 4350
Wire Wire Line
	7350 4350 7000 4350
Text GLabel 6900 4100 2    60   Input ~ 0
GND
Wire Wire Line
	6900 4100 6750 4100
Text GLabel 6950 3100 2    60   Input ~ 0
Vcc
Wire Wire Line
	6950 3100 6750 3100
Wire Wire Line
	6750 3100 6750 3300
$Comp
L PHOTO_DETECTOR PHD1
U 1 1 51F069B4
P 6350 4800
F 0 "PHD1" H 6250 4900 40  0000 C CNN
F 1 "PHOTO_DETECTOR" H 6350 4700 40  0000 C CNN
	1    6350 4800
	0    -1   -1   0   
$EndComp
Connection ~ 6350 4350
Text GLabel 5600 5300 0    60   Input ~ 0
GND
$Comp
L LED D1
U 1 1 51F06AA4
P 5800 4800
F 0 "D1" H 5800 4900 50  0000 C CNN
F 1 "LED" H 5800 4700 50  0000 C CNN
F 2 "~" H 5800 4800 60  0000 C CNN
F 3 "~" H 5800 4800 60  0000 C CNN
	1    5800 4800
	0    -1   1    0   
$EndComp
Wire Wire Line
	5600 5300 6350 5300
Wire Wire Line
	6350 5300 6350 5000
Wire Wire Line
	5800 5000 5800 5450
Connection ~ 5800 5300
$Comp
L R R2
U 1 1 51F06B8D
P 5800 4200
F 0 "R2" V 5880 4200 40  0000 C CNN
F 1 "390R" V 5807 4201 40  0000 C CNN
F 2 "~" V 5730 4200 30  0000 C CNN
F 3 "~" H 5800 4200 30  0000 C CNN
	1    5800 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4450 5800 4600
Text GLabel 5550 3950 0    60   Input ~ 0
Vcc
Wire Wire Line
	5550 3950 5800 3950
$Comp
L RJ45 J1
U 1 1 51F06D93
P 3900 3550
F 0 "J1" H 4100 4050 60  0000 C CNN
F 1 "RJ45" H 3750 4050 60  0000 C CNN
F 2 "~" H 3900 3550 60  0000 C CNN
F 3 "~" H 3900 3550 60  0000 C CNN
	1    3900 3550
	1    0    0    -1  
$EndComp
NoConn ~ 4450 3200
NoConn ~ 4250 4000
NoConn ~ 4150 4000
NoConn ~ 3650 4000
NoConn ~ 3550 4000
Text GLabel 3750 4200 3    60   Input ~ 0
Vcc
Text GLabel 3950 4200 3    60   Input ~ 0
GND
Wire Wire Line
	3750 4200 3750 4000
Wire Wire Line
	3950 4200 3950 4000
Text GLabel 3850 4600 3    60   Input ~ 0
idAN
Text GLabel 4050 4600 3    60   Input ~ 0
AN
Wire Wire Line
	3850 4600 3850 4000
Wire Wire Line
	4050 4600 4050 4000
$Comp
L R R1
U 1 1 51F070DD
P 3850 5300
F 0 "R1" V 3930 5300 40  0000 C CNN
F 1 "4K7" V 3857 5301 40  0000 C CNN
F 2 "~" V 3780 5300 30  0000 C CNN
F 3 "~" H 3850 5300 30  0000 C CNN
	1    3850 5300
	0    -1   -1   0   
$EndComp
Text GLabel 4350 5300 2    60   Input ~ 0
idAN
Text GLabel 3300 5300 0    60   Input ~ 0
Vcc
Wire Wire Line
	3300 5300 3600 5300
Wire Wire Line
	4100 5300 4350 5300
Text GLabel 7700 3700 2    60   Input ~ 0
AN
Wire Wire Line
	7700 3700 7350 3700
Text GLabel 5550 4600 0    60   Input ~ 0
LED
Wire Wire Line
	5800 4600 5550 4600
Text GLabel 6650 4600 2    60   Input ~ 0
PHD
Wire Wire Line
	6350 4600 6650 4600
$Comp
L PWR_FLAG #FLG01
U 1 1 51F0841E
P 6750 3100
F 0 "#FLG01" H 6750 3195 30  0001 C CNN
F 1 "PWR_FLAG" H 6750 3280 30  0000 C CNN
	1    6750 3100
	1    0    0    -1  
$EndComp
Connection ~ 6750 3100
$Comp
L GND #PWR02
U 1 1 51F084A4
P 5800 5450
F 0 "#PWR02" H 5800 5450 30  0001 C CNN
F 1 "GND" H 5800 5380 30  0001 C CNN
	1    5800 5450
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 51F08550
P 6150 3600
F 0 "#FLG03" H 6150 3695 30  0001 C CNN
F 1 "PWR_FLAG" H 6150 3780 30  0000 C CNN
	1    6150 3600
	1    0    0    -1  
$EndComp
Connection ~ 6150 3600
$EndSCHEMATC
