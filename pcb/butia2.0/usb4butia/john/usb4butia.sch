EESchema Schematic File Version 2  date mié 06 jun 2012 23:04:25 UYT
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
LIBS:usb4butia-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title "USB4butia"
Date "7 jun 2012"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 6200 7300 0    60   Input ~ 0
VDD
Text GLabel 6200 7100 0    60   Input ~ 0
VDD
Wire Wire Line
	6200 7300 6300 7300
Wire Wire Line
	6200 7100 6300 7100
$Comp
L CONN_2 P11
U 1 1 4FD00BFB
P 6650 7200
F 0 "P11" V 6600 7200 40  0000 C CNN
F 1 "BRIDGE" V 6700 7200 40  0000 C CNN
	1    6650 7200
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P10
U 1 1 4FD00BAA
P 6650 6800
F 0 "P10" V 6600 6800 40  0000 C CNN
F 1 "BRIDGE" V 6700 6800 40  0000 C CNN
	1    6650 6800
	1    0    0    -1  
$EndComp
Text GLabel 6200 6700 0    60   Input ~ 0
GND
Text GLabel 6200 6900 0    60   Input ~ 0
GND
Wire Wire Line
	6200 6700 6300 6700
Wire Wire Line
	6200 6900 6300 6900
Wire Wire Line
	7150 6900 7250 6900
Wire Wire Line
	7150 6700 7250 6700
Text GLabel 7150 6900 0    60   Input ~ 0
GND
Text GLabel 7150 6700 0    60   Input ~ 0
GND
$Comp
L CONN_2 P13
U 1 1 4FD00BA9
P 7600 6800
F 0 "P13" V 7550 6800 40  0000 C CNN
F 1 "BRIDGE" V 7650 6800 40  0000 C CNN
	1    7600 6800
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P12
U 1 1 4FD00B9E
P 7600 6400
F 0 "P12" V 7550 6400 40  0000 C CNN
F 1 "BRIDGE" V 7650 6400 40  0000 C CNN
	1    7600 6400
	1    0    0    -1  
$EndComp
Text GLabel 7150 6300 0    60   Input ~ 0
GND
Text GLabel 7150 6500 0    60   Input ~ 0
GND
Wire Wire Line
	7150 6300 7250 6300
Wire Wire Line
	7150 6500 7250 6500
Wire Wire Line
	6200 6500 6300 6500
Wire Wire Line
	5300 4900 5050 4900
Wire Wire Line
	5100 1900 5300 1900
Wire Wire Line
	5100 1700 5300 1700
Wire Wire Line
	4300 2200 4150 2200
Wire Wire Line
	5400 2650 5550 2650
Wire Wire Line
	1900 4000 2050 4000
Wire Wire Line
	5400 2800 5550 2800
Wire Wire Line
	5400 3000 5550 3000
Wire Wire Line
	1900 2500 2050 2500
Wire Wire Line
	7350 4350 7500 4350
Wire Wire Line
	7350 4250 7500 4250
Wire Wire Line
	7350 4450 7500 4450
Wire Wire Line
	7350 4550 7500 4550
Wire Wire Line
	4300 4100 4150 4100
Wire Wire Line
	4300 4000 4150 4000
Wire Wire Line
	4300 3900 4150 3900
Wire Wire Line
	4300 3800 4150 3800
Wire Wire Line
	1800 2600 2050 2600
Wire Wire Line
	2050 2800 1900 2800
Wire Wire Line
	7550 5550 7700 5550
Connection ~ 7050 6050
Wire Wire Line
	6800 6050 7550 6050
Wire Wire Line
	6000 5350 6250 5350
Wire Wire Line
	6250 5450 6000 5450
Wire Wire Line
	6000 5550 6250 5550
Wire Wire Line
	6000 5650 6250 5650
Wire Wire Line
	4300 4200 4150 4200
Wire Wire Line
	4300 4300 4150 4300
Wire Wire Line
	4300 4400 4150 4400
Wire Wire Line
	4300 4500 4150 4500
Wire Wire Line
	6400 3800 6550 3800
Wire Wire Line
	6400 3600 6550 3600
Wire Wire Line
	1800 2900 2050 2900
Wire Wire Line
	2050 3000 1800 3000
Wire Wire Line
	7800 2450 7650 2450
Wire Wire Line
	6100 2250 6350 2250
Wire Wire Line
	6100 2550 6350 2550
Wire Wire Line
	6350 2350 6100 2350
Wire Wire Line
	6100 2450 6350 2450
Wire Wire Line
	6900 2950 7650 2950
Connection ~ 7150 2950
Wire Wire Line
	4950 3600 5100 3600
Connection ~ 3300 5150
Wire Wire Line
	3500 5150 2950 5150
Wire Wire Line
	2950 5150 2950 5450
Wire Wire Line
	1100 5350 2800 5350
Wire Wire Line
	2800 5350 2800 5550
Wire Wire Line
	2800 5550 2950 5550
Connection ~ 1350 4500
Wire Wire Line
	2050 4500 1250 4500
Wire Wire Line
	1850 4400 2050 4400
Wire Wire Line
	5000 4350 5150 4350
Wire Wire Line
	8600 6300 8850 6300
Wire Wire Line
	10150 4700 10300 4700
Connection ~ 9650 5200
Wire Wire Line
	9400 5200 10150 5200
Connection ~ 9650 3700
Wire Wire Line
	9400 3700 10150 3700
Connection ~ 9650 2250
Wire Wire Line
	9400 2250 10150 2250
Wire Wire Line
	8600 6200 8850 6200
Wire Wire Line
	8600 4700 8850 4700
Wire Wire Line
	8600 1750 8850 1750
Wire Wire Line
	8600 3300 8850 3300
Wire Wire Line
	8600 3200 8850 3200
Wire Wire Line
	8850 6100 8600 6100
Wire Wire Line
	8850 4600 8600 4600
Wire Wire Line
	8850 3100 8600 3100
Wire Wire Line
	8850 1650 8600 1650
Wire Wire Line
	4100 5650 4250 5650
Wire Wire Line
	1100 6150 1250 6150
Wire Wire Line
	3650 1350 3800 1350
Wire Wire Line
	6900 1500 6150 1500
Wire Wire Line
	6150 1500 6150 1100
Wire Wire Line
	2050 2000 1850 2000
Wire Wire Line
	5100 5650 5000 5650
Wire Wire Line
	1850 4300 2050 4300
Connection ~ 1250 5350
Connection ~ 1250 5750
Wire Wire Line
	6250 4600 6050 4600
Wire Wire Line
	2050 4100 1850 4100
Wire Wire Line
	2950 5650 2950 5750
Wire Wire Line
	2950 5750 1100 5750
Connection ~ 1900 5750
Connection ~ 2400 5350
Connection ~ 1550 5350
Connection ~ 1100 6750
Wire Wire Line
	1300 6750 950  6750
Wire Wire Line
	1850 3650 2050 3650
Connection ~ 1350 1250
Wire Wire Line
	2100 1250 1200 1250
Wire Wire Line
	6900 1400 6250 1400
Wire Wire Line
	6250 1400 6250 1100
Wire Wire Line
	6450 1100 6450 1200
Wire Wire Line
	6450 1200 6900 1200
Wire Wire Line
	4050 1350 3950 1350
Wire Wire Line
	4350 3000 4150 3000
Wire Wire Line
	1850 3800 2050 3800
Wire Wire Line
	5250 6750 5050 6750
Wire Wire Line
	4150 6850 4150 7050
Wire Wire Line
	4150 6850 4250 6850
Wire Wire Line
	4150 7050 3950 7050
Wire Wire Line
	1850 2400 2050 2400
Wire Wire Line
	1850 2200 2050 2200
Wire Wire Line
	4150 2100 4350 2100
Wire Wire Line
	4350 2500 4150 2500
Wire Wire Line
	4350 2700 4150 2700
Connection ~ 2100 850 
Wire Wire Line
	5050 1250 5050 850 
Connection ~ 3950 850 
Wire Wire Line
	1100 6750 1100 7050
Wire Wire Line
	2000 6750 2000 7050
Wire Wire Line
	1100 7050 1250 7050
Wire Wire Line
	1350 850  1350 1250
Wire Wire Line
	3800 850  4450 850 
Connection ~ 4250 850 
Connection ~ 2500 850 
Wire Wire Line
	4350 2600 4150 2600
Wire Wire Line
	4350 2400 4150 2400
Wire Wire Line
	4150 2000 4350 2000
Wire Wire Line
	1850 2100 2050 2100
Wire Wire Line
	1850 2300 2050 2300
Wire Wire Line
	3350 7050 3150 7050
Wire Wire Line
	4250 6750 3150 6750
Wire Wire Line
	3150 6750 3150 7050
Wire Wire Line
	4150 7450 2850 7450
Connection ~ 3150 7450
Wire Wire Line
	5250 6850 5050 6850
Wire Wire Line
	1850 3900 2050 3900
Wire Wire Line
	1850 3200 2050 3200
Wire Wire Line
	1850 3300 2050 3300
Wire Wire Line
	4350 2900 4150 2900
Wire Wire Line
	4250 1250 5200 1250
Connection ~ 5050 1250
Wire Wire Line
	6900 1100 6550 1100
Wire Wire Line
	6350 1100 6350 1300
Wire Wire Line
	6350 1300 6900 1300
Wire Wire Line
	2500 1350 2350 1350
Wire Wire Line
	1850 3550 2050 3550
Wire Wire Line
	2000 7050 1850 7050
Wire Wire Line
	1800 6750 2150 6750
Connection ~ 2000 6750
Wire Wire Line
	1100 7450 2200 7450
Connection ~ 2000 7450
Wire Wire Line
	5000 5400 5000 5300
Wire Wire Line
	5000 5300 4250 5300
Wire Wire Line
	4100 5500 4250 5500
Wire Wire Line
	3900 6050 4100 6050
Connection ~ 1900 5350
Connection ~ 1550 5750
Connection ~ 2400 5750
Wire Wire Line
	4250 5500 4250 5300
Connection ~ 4250 5400
Wire Wire Line
	6450 4200 6250 4200
Wire Wire Line
	1850 4200 2050 4200
Wire Wire Line
	5100 5500 5000 5500
Wire Wire Line
	2850 1350 2650 1350
Wire Wire Line
	4350 2300 4150 2300
Wire Wire Line
	1950 850  2650 850 
Wire Wire Line
	1750 6150 1900 6150
Wire Wire Line
	1100 5850 1250 5850
Wire Wire Line
	1250 5850 1250 5750
Wire Wire Line
	8600 1850 8850 1850
Wire Wire Line
	8600 1550 8850 1550
Wire Wire Line
	8600 3000 8850 3000
Wire Wire Line
	8600 4500 8850 4500
Wire Wire Line
	8600 6000 8850 6000
Wire Wire Line
	10300 1750 10150 1750
Wire Wire Line
	10150 3200 10300 3200
Wire Wire Line
	9400 6700 10150 6700
Connection ~ 9650 6700
Wire Wire Line
	8600 4800 8850 4800
Wire Wire Line
	10150 6200 10300 6200
Wire Wire Line
	5000 4450 5150 4450
Wire Wire Line
	1350 4400 1350 4500
Wire Wire Line
	5000 4550 5150 4550
Connection ~ 3050 5150
Wire Wire Line
	4950 3800 5100 3800
Wire Wire Line
	4400 4900 4550 4900
Wire Wire Line
	6200 6300 6300 6300
Text GLabel 6200 6500 0    60   Input ~ 0
GND
Text GLabel 6200 6300 0    60   Input ~ 0
GND
$Comp
L CONN_2 P9
U 1 1 4FD00A52
P 6650 6400
F 0 "P9" V 6600 6400 40  0000 C CNN
F 1 "BRIDGE" V 6700 6400 40  0000 C CNN
	1    6650 6400
	1    0    0    -1  
$EndComp
Text GLabel 5300 4900 2    60   Output ~ 0
data
Text GLabel 5000 4550 0    60   Output ~ 0
data
Text GLabel 4400 4900 0    60   Input ~ 0
VDD
$Comp
L R R14
U 1 1 4F91F453
P 4800 4900
F 0 "R14" V 4700 4900 50  0000 C CNN
F 1 "1K" V 4800 4900 50  0000 C CNN
	1    4800 4900
	0    -1   -1   0   
$EndComp
NoConn ~ 5300 1800
Text GLabel 5100 1900 0    60   Input ~ 0
VDD
Text GLabel 5100 1700 0    60   Input ~ 0
VSS
$Comp
L CONN_3 K3
U 1 1 4F1D9A77
P 5650 1800
F 0 "K3" V 5600 1800 50  0000 C CNN
F 1 "CONN_3" V 5700 1800 40  0000 C CNN
	1    5650 1800
	1    0    0    -1  
$EndComp
Text GLabel 4300 2200 2    60   Input ~ 0
HK38
$Comp
L CONN_1 P7
U 1 1 4F187057
P 5700 2650
F 0 "P7" H 5780 2650 40  0000 L CNN
F 1 "CONN_1" H 5700 2705 30  0001 C CNN
	1    5700 2650
	1    0    0    -1  
$EndComp
Text GLabel 5400 2650 0    60   Input ~ 0
HK38
Text GLabel 1900 4000 0    60   Input ~ 0
HK17
Text GLabel 5400 2800 0    60   Input ~ 0
HK17
$Comp
L CONN_1 P8
U 1 1 4F187034
P 5700 2800
F 0 "P8" H 5780 2800 40  0000 L CNN
F 1 "CONN_1" H 5700 2855 30  0001 C CNN
	1    5700 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P6
U 1 1 4F186E55
P 5700 3000
F 0 "P6" H 5780 3000 40  0000 L CNN
F 1 "CONN_1" H 5700 3055 30  0001 C CNN
	1    5700 3000
	1    0    0    -1  
$EndComp
Text GLabel 5400 3000 0    60   Input ~ 0
HK6
Text GLabel 1900 2500 0    60   Input ~ 0
HK6
$Comp
L CONN_4 P5
U 1 1 4F1868B4
P 7850 4400
F 0 "P5" V 7800 4400 50  0000 C CNN
F 1 "CONN_4" V 7900 4400 50  0000 C CNN
	1    7850 4400
	1    0    0    -1  
$EndComp
Text GLabel 7350 4250 0    60   Input ~ 0
HK29
Text GLabel 7350 4350 0    60   Input ~ 0
HK30
Text GLabel 7350 4550 0    60   Input ~ 0
HK27
Text GLabel 7350 4450 0    60   Input ~ 0
HK28
Text GLabel 4300 4000 2    60   Input ~ 0
HK28
Text GLabel 4300 4100 2    60   Input ~ 0
HK27
Text GLabel 4300 3800 2    60   Input ~ 0
HK30
Text GLabel 4300 3900 2    60   Input ~ 0
HK29
Text GLabel 6100 2350 0    60   Input ~ 0
idAN7
Text GLabel 1800 2600 0    60   Input ~ 0
AN4
Text GLabel 1900 2800 0    60   Input ~ 0
idAN5
$Comp
L RJ45 J7
U 1 1 4F171600
P 6700 5500
F 0 "J7" H 6900 6000 60  0000 C CNN
F 1 "RJ45" H 6550 6000 60  0000 C CNN
	1    6700 5500
	0    1    1    0   
$EndComp
$Comp
L R R13
U 1 1 4F1715FF
P 7550 5800
F 0 "R13" V 7450 5800 50  0000 C CNN
F 1 "10K" V 7550 5800 50  0000 C CNN
	1    7550 5800
	-1   0    0    1   
$EndComp
Text GLabel 6000 5550 0    60   Input ~ 0
GND
Text GLabel 6800 6050 0    60   Input ~ 0
GND
NoConn ~ 6250 5150
NoConn ~ 6250 5250
NoConn ~ 6250 5750
NoConn ~ 6250 5850
Text GLabel 6000 5350 0    60   Input ~ 0
VDD
Text GLabel 6000 5450 0    60   Input ~ 0
idAN5
Text GLabel 6000 5650 0    60   Input ~ 0
AN4
Text GLabel 7700 5550 2    60   Input ~ 0
idAN5
Text Notes 9200 4200 0    60   ~ 0
SENSOR6
Text GLabel 4300 4300 2    60   Input ~ 0
HK21
Text GLabel 4300 4200 2    60   Input ~ 0
HK22
Text GLabel 4300 4500 2    60   Input ~ 0
HK19
Text GLabel 4300 4400 2    60   Input ~ 0
HK20
$Comp
L CONN_2 P4
U 1 1 4F170606
P 6900 3700
F 0 "P4" V 6850 3700 40  0000 C CNN
F 1 "CONN_2" V 6950 3700 40  0000 C CNN
	1    6900 3700
	1    0    0    -1  
$EndComp
Text Notes 7100 3450 2    60   ~ 0
Test Point x 2
Text GLabel 6400 3600 0    60   Input ~ 0
HK20
Text GLabel 6400 3800 0    60   Input ~ 0
HK19
Text GLabel 1800 2900 0    60   Input ~ 0
AN6
Text GLabel 1800 3000 0    60   Input ~ 0
idAN7
$Comp
L RJ45 J6
U 1 1 4F15C817
P 6800 2400
F 0 "J6" H 7000 2900 60  0000 C CNN
F 1 "RJ45" H 6650 2900 60  0000 C CNN
	1    6800 2400
	0    1    1    0   
$EndComp
$Comp
L R R12
U 1 1 4F15C816
P 7650 2700
F 0 "R12" V 7550 2700 50  0000 C CNN
F 1 "10K" V 7650 2700 50  0000 C CNN
	1    7650 2700
	-1   0    0    1   
$EndComp
Text GLabel 6100 2550 0    60   Input ~ 0
AN6
Text GLabel 6100 2450 0    60   Input ~ 0
GND
Text GLabel 6900 2950 0    60   Input ~ 0
GND
NoConn ~ 6350 2050
NoConn ~ 6350 2150
NoConn ~ 6350 2650
NoConn ~ 6350 2750
Text GLabel 6100 2250 0    60   Input ~ 0
VDD
Text GLabel 7800 2450 2    60   Input ~ 0
idAN7
Text Notes 9150 5700 0    60   ~ 0
SENSOR5
Text GLabel 4950 3800 0    60   Input ~ 0
HK22
Text GLabel 4950 3600 0    60   Input ~ 0
HK21
Text Notes 5650 3450 2    60   ~ 0
Test Point x 2
$Comp
L CONN_2 P3
U 1 1 4F14716E
P 5450 3700
F 0 "P3" V 5400 3700 40  0000 C CNN
F 1 "CONN_2" V 5500 3700 40  0000 C CNN
	1    5450 3700
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR01
U 1 1 4EFB55B3
P 3300 5150
F 0 "#PWR01" H 3300 5250 30  0001 C CNN
F 1 "VCC" H 3300 5250 30  0000 C CNN
	1    3300 5150
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 4EFB556E
P 3050 5150
F 0 "#FLG02" H 3050 5420 30  0001 C CNN
F 1 "PWR_FLAG" H 3050 5380 30  0000 C CNN
	1    3050 5150
	1    0    0    -1  
$EndComp
Text GLabel 3500 5150 2    60   Output ~ 0
VDC10
$Comp
L CONN_3 K2
U 1 1 4EFB535E
P 3300 5550
F 0 "K2" V 3250 5550 50  0000 C CNN
F 1 "V_5_10" V 3350 5550 40  0000 C CNN
	1    3300 5550
	1    0    0    1   
$EndComp
Text Notes 6700 1950 0    60   ~ 0
SENSOR4
Text Notes 6550 5050 0    60   ~ 0
SENSOR3
Text Notes 9150 2700 0    60   ~ 0
SENSOR2
Text Notes 9150 1250 0    60   ~ 0
SENSOR1
Text Notes 4800 4200 0    60   ~ 0
SERVO AX-12
Text GLabel 1250 4500 0    60   Input ~ 0
data
$Comp
L R R11
U 1 1 4EFB5095
P 1600 4400
F 0 "R11" V 1500 4400 50  0000 C CNN
F 1 "100R" V 1600 4400 50  0000 C CNN
	1    1600 4400
	0    -1   -1   0   
$EndComp
Text GLabel 5000 4450 0    60   Input ~ 0
VDC10
Text GLabel 5000 4350 0    60   Input ~ 0
GND
$Comp
L CONN_3 K1
U 1 1 4EFB4F25
P 5500 4450
F 0 "K1" V 5450 4450 50  0000 C CNN
F 1 "AX-12" V 5550 4450 40  0000 C CNN
	1    5500 4450
	1    0    0    -1  
$EndComp
Text GLabel 10300 6200 2    60   Input ~ 0
idAN12
Text GLabel 8600 6300 0    60   Input ~ 0
AN10
Text GLabel 8600 6100 0    60   Input ~ 0
idAN12
Text GLabel 8600 4800 0    60   Input ~ 0
AN9
Text GLabel 10300 4700 2    60   Input ~ 0
idAN8
Text GLabel 8600 4600 0    60   Input ~ 0
idAN8
Text GLabel 8600 3300 0    60   Input ~ 0
AN3
Text GLabel 1850 2300 0    60   Input ~ 0
idAN2
Text GLabel 10300 3200 2    60   Input ~ 0
idAN2
Text GLabel 10300 1750 2    60   Input ~ 0
idAN0
Text GLabel 1850 2100 0    60   Input ~ 0
idAN0
Text GLabel 8600 6000 0    60   Input ~ 0
VDD
Text GLabel 8600 4500 0    60   Input ~ 0
VDD
Text GLabel 8600 3000 0    60   Input ~ 0
VDD
Text GLabel 8600 1550 0    60   Input ~ 0
VDD
NoConn ~ 8850 6500
NoConn ~ 8850 6400
NoConn ~ 8850 5900
NoConn ~ 8850 5800
NoConn ~ 8850 5000
NoConn ~ 8850 4900
NoConn ~ 8850 4400
NoConn ~ 8850 4300
NoConn ~ 8850 3500
NoConn ~ 8850 3400
NoConn ~ 8850 2900
NoConn ~ 8850 2800
NoConn ~ 8850 2050
NoConn ~ 8850 1950
NoConn ~ 8850 1450
NoConn ~ 8850 1350
Text GLabel 9400 2250 0    60   Input ~ 0
GND
Text GLabel 9400 3700 0    60   Input ~ 0
GND
Text GLabel 9400 5200 0    60   Input ~ 0
GND
Text GLabel 9400 6700 0    60   Input ~ 0
GND
Text GLabel 8600 6200 0    60   Input ~ 0
GND
Text GLabel 8600 4700 0    60   Input ~ 0
GND
Text GLabel 8600 1750 0    60   Input ~ 0
GND
Text GLabel 8600 1850 0    60   Input ~ 0
AN1
Text GLabel 8600 3200 0    60   Input ~ 0
GND
Text GLabel 1100 5850 0    60   Output ~ 0
GND
$Comp
L R R10
U 1 1 4EFB2A89
P 10150 6450
F 0 "R10" V 10050 6450 50  0000 C CNN
F 1 "10K" V 10150 6450 50  0000 C CNN
	1    10150 6450
	-1   0    0    1   
$EndComp
$Comp
L R R9
U 1 1 4EFB2A7F
P 10150 4950
F 0 "R9" V 10050 4950 50  0000 C CNN
F 1 "10K" V 10150 4950 50  0000 C CNN
	1    10150 4950
	-1   0    0    1   
$EndComp
$Comp
L R R8
U 1 1 4EFB2A73
P 10150 3450
F 0 "R8" V 10050 3450 50  0000 C CNN
F 1 "10K" V 10150 3450 50  0000 C CNN
	1    10150 3450
	-1   0    0    1   
$EndComp
$Comp
L R R7
U 1 1 4EFB2A54
P 10150 2000
F 0 "R7" V 10050 2000 50  0000 C CNN
F 1 "10K" V 10150 2000 50  0000 C CNN
	1    10150 2000
	-1   0    0    1   
$EndComp
Text GLabel 8600 1650 0    60   Input ~ 0
idAN0
Text GLabel 8600 3100 0    60   Input ~ 0
idAN2
$Comp
L RJ45 J5
U 1 1 4EFB1B08
P 9300 6150
F 0 "J5" H 9500 6650 60  0000 C CNN
F 1 "RJ45" H 9150 6650 60  0000 C CNN
	1    9300 6150
	0    1    1    0   
$EndComp
$Comp
L RJ45 J4
U 1 1 4EFB1B05
P 9300 4650
F 0 "J4" H 9500 5150 60  0000 C CNN
F 1 "RJ45" H 9150 5150 60  0000 C CNN
	1    9300 4650
	0    1    1    0   
$EndComp
$Comp
L RJ45 J3
U 1 1 4EFB1B01
P 9300 3150
F 0 "J3" H 9500 3650 60  0000 C CNN
F 1 "RJ45" H 9150 3650 60  0000 C CNN
	1    9300 3150
	0    1    1    0   
$EndComp
$Comp
L RJ45 J2
U 1 1 4EFB1AFC
P 9300 1700
F 0 "J2" H 9500 2200 60  0000 C CNN
F 1 "RJ45" H 9150 2200 60  0000 C CNN
	1    9300 1700
	0    1    1    0   
$EndComp
Text GLabel 3650 1350 0    60   Input ~ 0
RB4
Text GLabel 4350 2300 2    60   Input ~ 0
RB4
Text GLabel 2850 1350 2    60   Input ~ 0
Vpp
Text GLabel 1850 2000 0    60   Input ~ 0
Vpp
Text GLabel 6900 1500 2    60   Input ~ 0
Vpp
Text GLabel 1850 4300 0    60   Input ~ 0
D+
Text GLabel 5100 5650 2    60   Input ~ 0
D+
Text GLabel 5100 5500 2    60   Input ~ 0
D-
Text GLabel 1850 4200 0    60   Input ~ 0
D-
$Comp
L PWR_FLAG #FLG03
U 1 1 4CA35E08
P 1250 5750
F 0 "#FLG03" H 1250 6020 30  0001 C CNN
F 1 "PWR_FLAG" H 1250 5980 30  0000 C CNN
	1    1250 5750
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D2
U 1 1 4CA35CFE
P 4100 5850
F 0 "D2" H 4100 5950 40  0000 C CNN
F 1 "1N5819" H 4100 5750 40  0000 C CNN
	1    4100 5850
	0    1    1    0   
$EndComp
Text GLabel 6450 4200 2    60   Input ~ 0
Vusb
Text GLabel 1850 4100 0    60   Input ~ 0
Vusb
Text GLabel 1100 6150 0    60   Input ~ 0
VDD
Text GLabel 1100 5750 0    60   Output ~ 0
VSS
Text GLabel 1100 5350 0    60   Output ~ 0
VDD
$Comp
L PWR_FLAG #FLG04
U 1 1 4C72A654
P 1250 5350
F 0 "#FLG04" H 1250 5620 30  0001 C CNN
F 1 "PWR_FLAG" H 1250 5580 30  0000 C CNN
	1    1250 5350
	1    0    0    -1  
$EndComp
Text GLabel 3900 6050 0    60   Output ~ 0
VDD
Text GLabel 4100 5500 0    60   Output ~ 0
VSS
Text GLabel 6050 4600 0    60   Input ~ 0
VSS
Text GLabel 2200 7450 2    60   Input ~ 0
VSS
Text GLabel 2150 6750 2    60   Input ~ 0
OSC2
Text GLabel 950  6750 0    60   Input ~ 0
OSC1
Text GLabel 1850 3650 0    60   Input ~ 0
OSC2
Text GLabel 1850 3550 0    60   Input ~ 0
OSC1
Text GLabel 1200 1250 0    60   Input ~ 0
VSS
Text GLabel 2350 1350 0    60   Input ~ 0
VDD
Text GLabel 6900 1400 2    60   Input ~ 0
VDD
Text GLabel 6900 1300 2    60   Input ~ 0
VSS
Text GLabel 6900 1200 2    60   Input ~ 0
RB7
Text GLabel 6900 1100 2    60   Input ~ 0
RB6
Text GLabel 5200 1250 2    60   Input ~ 0
VSS
Text GLabel 4050 1350 2    60   Input ~ 0
VDD
Text GLabel 1850 3300 0    60   Input ~ 0
VSS
Text GLabel 1850 3200 0    60   Input ~ 0
VDD
Text GLabel 1850 3900 0    60   Input ~ 0
RC1
Text GLabel 1850 3800 0    60   Input ~ 0
RC0
Text GLabel 5250 6850 2    60   Input ~ 0
RC1
Text GLabel 5250 6750 2    60   Input ~ 0
RC0
Text GLabel 2850 7450 0    60   Input ~ 0
VSS
Text GLabel 4350 3000 2    60   Input ~ 0
VSS
Text GLabel 4350 2900 2    60   Input ~ 0
VDD
Text GLabel 1850 2400 0    60   Input ~ 0
AN3
Text GLabel 1850 2200 0    60   Input ~ 0
AN1
$Comp
L GND #PWR05
U 1 1 4C72A5CE
P 2400 5750
F 0 "#PWR05" H 2400 5750 30  0001 C CNN
F 1 "GND" H 2400 5680 30  0001 C CNN
	1    2400 5750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 4C72A5AF
P 2400 5350
F 0 "#PWR06" H 2400 5440 20  0001 C CNN
F 1 "+5V" H 2400 5440 30  0000 C CNN
	1    2400 5350
	1    0    0    -1  
$EndComp
Text GLabel 4350 2000 2    60   Input ~ 0
RB7
Text GLabel 4350 2100 2    60   Input ~ 0
RB6
Text GLabel 4350 2400 2    60   Input ~ 0
AN9
Text GLabel 4350 2500 2    60   Input ~ 0
idAN8
Text GLabel 4350 2600 2    60   Input ~ 0
AN10
Text GLabel 4350 2700 2    60   Input ~ 0
idAN12
$Comp
L PIC18F4550 U1
U 1 1 4C6EE08D
P 3100 3350
F 0 "U1" H 3100 3450 70  0000 C CNN
F 1 "PIC18F4550" H 3100 3250 70  0000 C CNN
	1    3100 3350
	1    0    0    -1  
$EndComp
$Comp
L CONN_2X2 P2
U 1 1 4C6EDE43
P 4650 6800
F 0 "P2" H 4650 6950 50  0000 C CNN
F 1 "CONN_2X2" H 4660 6670 40  0000 C CNN
	1    4650 6800
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X2
U 1 1 4C6EDDF7
P 3650 7050
F 0 "X2" H 3650 7200 60  0000 C CNN
F 1 "32.768KHz" H 3650 6900 60  0000 C CNN
	1    3650 7050
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X1
U 1 1 4C6EDDF1
P 1550 7050
F 0 "X1" H 1550 7200 60  0000 C CNN
F 1 "20MHz" H 1550 6900 60  0000 C CNN
	1    1550 7050
	-1   0    0    -1  
$EndComp
$Comp
L CONN_5 P1
U 1 1 4C6EDD0D
P 6350 700
F 0 "P1" V 6300 700 50  0000 C CNN
F 1 "PICkit2" V 6400 700 50  0000 C CNN
	1    6350 700 
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 4C6EDC1C
P 1900 5950
F 0 "D1" H 1900 6050 50  0000 C CNN
F 1 "LED" H 1900 5850 50  0000 C CNN
	1    1900 5950
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 4C6EDBEC
P 1550 6750
F 0 "R2" V 1450 6750 50  0000 C CNN
F 1 "1M" V 1550 6750 50  0000 C CNN
	1    1550 6750
	0    -1   1    0   
$EndComp
$Comp
L R R4
U 1 1 4C6EDBE9
P 2650 1100
F 0 "R4" V 2550 1100 50  0000 C CNN
F 1 "390R" V 2650 1100 50  0000 C CNN
	1    2650 1100
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 4C6EDBE6
P 2500 1100
F 0 "R3" V 2400 1100 50  0000 C CNN
F 1 "10K" V 2500 1100 50  0000 C CNN
	1    2500 1100
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4C6EDBE4
P 3800 1100
F 0 "R5" V 3900 1100 50  0000 C CNN
F 1 "390R" V 3800 1100 50  0000 C CNN
	1    3800 1100
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 4C6EDBE2
P 3950 1100
F 0 "R6" V 4030 1100 50  0000 C CNN
F 1 "10K" V 3950 1100 50  0000 C CNN
	1    3950 1100
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4C6EDBDF
P 1500 6150
F 0 "R1" V 1580 6150 50  0000 C CNN
F 1 "1K" V 1500 6150 50  0000 C CNN
	1    1500 6150
	0    1    1    0   
$EndComp
$Comp
L CP C10
U 1 1 4C6EDA8C
P 2400 5550
F 0 "C10" H 2450 5650 50  0000 L CNN
F 1 "10uF" H 2450 5450 50  0000 L CNN
	1    2400 5550
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 4C6EDA69
P 1900 5550
F 0 "C9" H 1950 5650 50  0000 L CNN
F 1 "0,1uF" H 1950 5450 50  0000 L CNN
	1    1900 5550
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4C6EDA5F
P 1100 7250
F 0 "C1" H 1150 7350 50  0000 L CNN
F 1 "22pF" H 1100 7150 50  0000 L CNN
	1    1100 7250
	-1   0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 4C6EDA5C
P 2000 7250
F 0 "C2" H 1850 7350 50  0000 L CNN
F 1 "22pF" H 1750 7150 50  0000 L CNN
	1    2000 7250
	-1   0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 4C6EDA5A
P 4150 7250
F 0 "C6" H 4200 7350 50  0000 L CNN
F 1 "22pF" H 4200 7150 50  0000 L CNN
	1    4150 7250
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 4C6EDA57
P 2100 1050
F 0 "C3" H 1950 1150 50  0000 L CNN
F 1 "0,1uF" H 1850 950 50  0000 L CNN
	1    2100 1050
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 4C6ED9FF
P 3150 7250
F 0 "C5" H 3200 7350 50  0000 L CNN
F 1 "22pF" H 3200 7150 50  0000 L CNN
	1    3150 7250
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 4C6ED9FC
P 4250 1050
F 0 "C7" H 4300 1150 50  0000 L CNN
F 1 "0,1uF" H 4300 950 50  0000 L CNN
	1    4250 1050
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 4C6ED9F9
P 6250 4400
F 0 "C4" H 6300 4500 50  0000 L CNN
F 1 "0,47uF" H 6300 4300 50  0000 L CNN
	1    6250 4400
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 4C6ED9F4
P 1550 5550
F 0 "C8" H 1600 5650 50  0000 L CNN
F 1 "0,1uF" H 1600 5450 50  0000 L CNN
	1    1550 5550
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 4C6ED95B
P 1650 850
F 0 "SW1" H 1800 960 50  0000 C CNN
F 1 "RST" H 1650 770 50  0000 C CNN
	1    1650 850 
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 4C6ED955
P 4750 850
F 0 "SW2" H 4900 960 50  0000 C CNN
F 1 "PROG" H 4750 770 50  0000 C CNN
	1    4750 850 
	1    0    0    -1  
$EndComp
$Comp
L USB_CONN J1
U 1 1 4C6ED928
P 4650 5850
F 0 "J1" H 4600 6250 60  0000 C CNN
F 1 "USB_B" V 4400 6000 60  0000 C CNN
	1    4650 5850
	1    0    0    1   
$EndComp
$EndSCHEMATC
