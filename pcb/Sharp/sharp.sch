EESchema Schematic File Version 2  date mié 23 may 2012 10:33:15 UYT
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
LIBS:sharp-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "23 may 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3250 3300 3400 3300
Wire Wire Line
	3200 3200 3400 3200
Wire Wire Line
	3900 2000 3900 1850
Wire Wire Line
	2200 1950 2200 2350
Wire Wire Line
	2300 1950 2300 2650
Wire Wire Line
	2500 1950 2500 2650
Wire Wire Line
	2400 2150 2400 1950
Wire Wire Line
	3900 2500 3900 2650
Wire Wire Line
	3250 3100 3400 3100
Text GLabel 3250 3300 0    60   Input ~ 0
VDD
$Comp
L CONN_3 K1
U 1 1 4F91ECE3
P 3750 3200
F 0 "K1" V 3700 3200 50  0000 C CNN
F 1 "CONN_3" V 3800 3200 40  0000 C CNN
	1    3750 3200
	1    0    0    -1  
$EndComp
Text GLabel 3250 3100 0    60   Input ~ 0
GND
Text GLabel 3200 3200 0    60   Input ~ 0
AN
$Comp
L R R2
U 1 1 4FAC1BA4
P 3900 2250
F 0 "R2" V 3980 2250 50  0000 C CNN
F 1 "R" V 3900 2250 50  0000 C CNN
	1    3900 2250
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
