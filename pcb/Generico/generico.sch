EESchema Schematic File Version 2  date lun 05 ago 2013 18:30:27 UYT
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
LIBS:Sensores 2.0-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "20 mar 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 2900 1150 2    60   Input ~ 0
GND
NoConn ~ 2700 1950
NoConn ~ 2600 1950
NoConn ~ 2100 1950
NoConn ~ 2000 1950
Wire Wire Line
	2800 3450 2700 3450
Wire Wire Line
	2700 3450 2700 3500
Wire Wire Line
	2700 3500 2500 3500
Wire Wire Line
	3300 2300 3500 2300
Wire Wire Line
	2400 2150 2400 1950
Wire Wire Line
	2500 1950 2500 2650
Wire Wire Line
	2300 1950 2300 2650
Wire Wire Line
	2200 1950 2200 2350
Wire Wire Line
	2500 3350 2800 3350
Wire Wire Line
	3350 2100 3500 2100
Wire Wire Line
	2500 3200 2750 3200
Wire Wire Line
	2750 3200 2750 3250
Wire Wire Line
	2750 3250 2800 3250
Text GLabel 2500 3500 0    60   Input ~ 0
VDD
Text GLabel 2500 3200 0    60   Input ~ 0
GND
Text GLabel 3350 2100 0    60   Input ~ 0
idAN
Text GLabel 3300 2300 0    60   Input ~ 0
VDD
Text GLabel 2400 2150 3    60   Input ~ 0
GND
Text GLabel 2200 2350 3    60   Input ~ 0
VDD
Text GLabel 2500 3350 0    60   Input ~ 0
AN
$Comp
L CONN_3 K1
U 1 1 4F6888FE
P 3150 3350
F 0 "K1" V 3100 3350 50  0000 C CNN
F 1 "Conn_Sensor" V 3200 3350 40  0000 C CNN
F 2 "" H 3150 3350 60  0001 C CNN
F 3 "" H 3150 3350 60  0001 C CNN
	1    3150 3350
	1    0    0    -1  
$EndComp
Text GLabel 2500 2650 3    60   Input ~ 0
AN
Text GLabel 2300 2650 3    60   Input ~ 0
idAN
$Comp
L CONN_2 P1
U 1 1 4F688199
P 3850 2200
F 0 "P1" V 3800 2200 40  0000 C CNN
F 1 "Conn_ID" V 3900 2200 40  0000 C CNN
F 2 "" H 3850 2200 60  0001 C CNN
F 3 "" H 3850 2200 60  0001 C CNN
	1    3850 2200
	1    0    0    -1  
$EndComp
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
$EndSCHEMATC
