EESchema Schematic File Version 4
LIBS:micro-sci-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "MicroSci"
Date "2020-06-09"
Rev "1.0"
Comp "Paweł Kania"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:C C2
U 1 1 5EDD3C44
P 3950 2600
F 0 "C2" V 4202 2600 50  0000 C CNN
F 1 "22pF" V 4111 2600 50  0000 C CNN
F 2 "" H 3988 2450 50  0001 C CNN
F 3 "~" H 3950 2600 50  0001 C CNN
	1    3950 2600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C1
U 1 1 5EDD3D30
P 3950 2900
F 0 "C1" V 3790 2900 50  0000 C CNN
F 1 "22pF" V 3699 2900 50  0000 C CNN
F 2 "" H 3988 2750 50  0001 C CNN
F 3 "~" H 3950 2900 50  0001 C CNN
	1    3950 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:Crystal X1
U 1 1 5EDD3FCE
P 4300 2750
F 0 "X1" V 4346 2619 50  0000 R CNN
F 1 "12 MHz" V 4255 2619 50  0000 R CNN
F 2 "" H 4300 2750 50  0001 C CNN
F 3 "~" H 4300 2750 50  0001 C CNN
	1    4300 2750
	0    -1   -1   0   
$EndComp
$Comp
L Display_Character:WC1602A DS1
U 1 1 5EDD41B8
P 5250 3650
F 0 "DS1" H 5250 4628 50  0000 C CNN
F 1 "WC1602A" H 5250 4537 50  0000 C CNN
F 2 "Display:WC1602A" H 5250 2750 50  0001 C CIN
F 3 "http://www.wincomlcd.com/pdf/WC1602A-SFYLYHTC06.pdf" H 5950 3650 50  0001 C CNN
	1    5250 3650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_A1
U 1 1 5EDD44CE
P 7400 4050
F 0 "SW_A1" H 7550 4150 50  0000 C CNN
F 1 " " H 7400 4194 50  0000 C CNN
F 2 "" H 7400 4050 50  0001 C CNN
F 3 "" H 7400 4050 50  0001 C CNN
	1    7400 4050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_B1
U 1 1 5EDD5D7E
P 7900 4050
F 0 "SW_B1" H 8050 4150 50  0000 C CNN
F 1 " " H 7900 4194 50  0000 C CNN
F 2 "" H 7900 4050 50  0001 C CNN
F 3 "" H 7900 4050 50  0001 C CNN
	1    7900 4050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_C1
U 1 1 5EDD5DA2
P 8400 4050
F 0 "SW_C1" H 8550 4150 50  0000 C CNN
F 1 " " H 8400 4194 50  0000 C CNN
F 2 "" H 8400 4050 50  0001 C CNN
F 3 "" H 8400 4050 50  0001 C CNN
	1    8400 4050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_D1
U 1 1 5EDD5DC3
P 8900 4050
F 0 "SW_D1" H 9050 4150 50  0000 C CNN
F 1 " " H 8900 4194 50  0000 C CNN
F 2 "" H 8900 4050 50  0001 C CNN
F 3 "" H 8900 4050 50  0001 C CNN
	1    8900 4050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_E1
U 1 1 5EDD5DDB
P 9400 4050
F 0 "SW_E1" H 9550 4150 50  0000 C CNN
F 1 " " H 9400 4194 50  0000 C CNN
F 2 "" H 9400 4050 50  0001 C CNN
F 3 "" H 9400 4050 50  0001 C CNN
	1    9400 4050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_A2
U 1 1 5EDD5FA4
P 7400 4300
F 0 "SW_A2" H 7550 4400 50  0000 C CNN
F 1 " " H 7400 4444 50  0000 C CNN
F 2 "" H 7400 4300 50  0001 C CNN
F 3 "" H 7400 4300 50  0001 C CNN
	1    7400 4300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_B2
U 1 1 5EDD5FAB
P 7900 4300
F 0 "SW_B2" H 8050 4400 50  0000 C CNN
F 1 " " H 7900 4444 50  0000 C CNN
F 2 "" H 7900 4300 50  0001 C CNN
F 3 "" H 7900 4300 50  0001 C CNN
	1    7900 4300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_C2
U 1 1 5EDD5FB2
P 8400 4300
F 0 "SW_C2" H 8550 4400 50  0000 C CNN
F 1 " " H 8400 4444 50  0000 C CNN
F 2 "" H 8400 4300 50  0001 C CNN
F 3 "" H 8400 4300 50  0001 C CNN
	1    8400 4300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_D2
U 1 1 5EDD5FB9
P 8900 4300
F 0 "SW_D2" H 9050 4400 50  0000 C CNN
F 1 " " H 8900 4444 50  0000 C CNN
F 2 "" H 8900 4300 50  0001 C CNN
F 3 "" H 8900 4300 50  0001 C CNN
	1    8900 4300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_E2
U 1 1 5EDD5FC0
P 9400 4300
F 0 "SW_E2" H 9550 4400 50  0000 C CNN
F 1 " " H 9400 4444 50  0000 C CNN
F 2 "" H 9400 4300 50  0001 C CNN
F 3 "" H 9400 4300 50  0001 C CNN
	1    9400 4300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_A3
U 1 1 5EDD5FFE
P 7400 4550
F 0 "SW_A3" H 7550 4650 50  0000 C CNN
F 1 " " H 7400 4694 50  0000 C CNN
F 2 "" H 7400 4550 50  0001 C CNN
F 3 "" H 7400 4550 50  0001 C CNN
	1    7400 4550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_B3
U 1 1 5EDD6005
P 7900 4550
F 0 "SW_B3" H 8050 4650 50  0000 C CNN
F 1 " " H 7900 4694 50  0000 C CNN
F 2 "" H 7900 4550 50  0001 C CNN
F 3 "" H 7900 4550 50  0001 C CNN
	1    7900 4550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_C3
U 1 1 5EDD600C
P 8400 4550
F 0 "SW_C3" H 8550 4650 50  0000 C CNN
F 1 " " H 8400 4694 50  0000 C CNN
F 2 "" H 8400 4550 50  0001 C CNN
F 3 "" H 8400 4550 50  0001 C CNN
	1    8400 4550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_D3
U 1 1 5EDD6013
P 8900 4550
F 0 "SW_D3" H 9050 4650 50  0000 C CNN
F 1 " " H 8900 4694 50  0000 C CNN
F 2 "" H 8900 4550 50  0001 C CNN
F 3 "" H 8900 4550 50  0001 C CNN
	1    8900 4550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_E3
U 1 1 5EDD601A
P 9400 4550
F 0 "SW_E3" H 9550 4650 50  0000 C CNN
F 1 " " H 9400 4694 50  0000 C CNN
F 2 "" H 9400 4550 50  0001 C CNN
F 3 "" H 9400 4550 50  0001 C CNN
	1    9400 4550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_A4
U 1 1 5EDD60FD
P 7400 4800
F 0 "SW_A4" H 7550 4900 50  0000 C CNN
F 1 " " H 7400 4944 50  0000 C CNN
F 2 "" H 7400 4800 50  0001 C CNN
F 3 "" H 7400 4800 50  0001 C CNN
	1    7400 4800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_B4
U 1 1 5EDD6104
P 7900 4800
F 0 "SW_B4" H 8050 4900 50  0000 C CNN
F 1 " " H 7900 4944 50  0000 C CNN
F 2 "" H 7900 4800 50  0001 C CNN
F 3 "" H 7900 4800 50  0001 C CNN
	1    7900 4800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_C4
U 1 1 5EDD610B
P 8400 4800
F 0 "SW_C4" H 8550 4900 50  0000 C CNN
F 1 " " H 8400 4944 50  0000 C CNN
F 2 "" H 8400 4800 50  0001 C CNN
F 3 "" H 8400 4800 50  0001 C CNN
	1    8400 4800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_D4
U 1 1 5EDD6112
P 8900 4800
F 0 "SW_D4" H 9050 4900 50  0000 C CNN
F 1 " " H 8900 4944 50  0000 C CNN
F 2 "" H 8900 4800 50  0001 C CNN
F 3 "" H 8900 4800 50  0001 C CNN
	1    8900 4800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_E4
U 1 1 5EDD6119
P 9400 4800
F 0 "SW_E4" H 9550 4900 50  0000 C CNN
F 1 " " H 9400 4944 50  0000 C CNN
F 2 "" H 9400 4800 50  0001 C CNN
F 3 "" H 9400 4800 50  0001 C CNN
	1    9400 4800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_A5
U 1 1 5EDD631E
P 7400 5050
F 0 "SW_A5" H 7550 5150 50  0000 C CNN
F 1 " " H 7400 5194 50  0000 C CNN
F 2 "" H 7400 5050 50  0001 C CNN
F 3 "" H 7400 5050 50  0001 C CNN
	1    7400 5050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_B5
U 1 1 5EDD6325
P 7900 5050
F 0 "SW_B5" H 8050 5150 50  0000 C CNN
F 1 " " H 7900 5194 50  0000 C CNN
F 2 "" H 7900 5050 50  0001 C CNN
F 3 "" H 7900 5050 50  0001 C CNN
	1    7900 5050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_C5
U 1 1 5EDD632C
P 8400 5050
F 0 "SW_C5" H 8550 5150 50  0000 C CNN
F 1 " " H 8400 5194 50  0000 C CNN
F 2 "" H 8400 5050 50  0001 C CNN
F 3 "" H 8400 5050 50  0001 C CNN
	1    8400 5050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_D5
U 1 1 5EDD6333
P 8900 5050
F 0 "SW_D5" H 9050 5150 50  0000 C CNN
F 1 " " H 8900 5194 50  0000 C CNN
F 2 "" H 8900 5050 50  0001 C CNN
F 3 "" H 8900 5050 50  0001 C CNN
	1    8900 5050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_E5
U 1 1 5EDD633A
P 9400 5050
F 0 "SW_E5" H 9550 5150 50  0000 C CNN
F 1 " " H 9400 5194 50  0000 C CNN
F 2 "" H 9400 5050 50  0001 C CNN
F 3 "" H 9400 5050 50  0001 C CNN
	1    9400 5050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_A6
U 1 1 5EDD6341
P 7400 5300
F 0 "SW_A6" H 7550 5400 50  0000 C CNN
F 1 " " H 7400 5444 50  0000 C CNN
F 2 "" H 7400 5300 50  0001 C CNN
F 3 "" H 7400 5300 50  0001 C CNN
	1    7400 5300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_B6
U 1 1 5EDD6348
P 7900 5300
F 0 "SW_B6" H 8050 5400 50  0000 C CNN
F 1 " " H 7900 5444 50  0000 C CNN
F 2 "" H 7900 5300 50  0001 C CNN
F 3 "" H 7900 5300 50  0001 C CNN
	1    7900 5300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_C6
U 1 1 5EDD634F
P 8400 5300
F 0 "SW_C6" H 8550 5400 50  0000 C CNN
F 1 " " H 8400 5444 50  0000 C CNN
F 2 "" H 8400 5300 50  0001 C CNN
F 3 "" H 8400 5300 50  0001 C CNN
	1    8400 5300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_D6
U 1 1 5EDD6356
P 8900 5300
F 0 "SW_D6" H 9050 5400 50  0000 C CNN
F 1 " " H 8900 5444 50  0000 C CNN
F 2 "" H 8900 5300 50  0001 C CNN
F 3 "" H 8900 5300 50  0001 C CNN
	1    8900 5300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_E6
U 1 1 5EDD635D
P 9400 5300
F 0 "SW_E6" H 9550 5400 50  0000 C CNN
F 1 " " H 9400 5444 50  0000 C CNN
F 2 "" H 9400 5300 50  0001 C CNN
F 3 "" H 9400 5300 50  0001 C CNN
	1    9400 5300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_A7
U 1 1 5EDD6364
P 7400 5550
F 0 "SW_A7" H 7550 5650 50  0000 C CNN
F 1 " " H 7400 5694 50  0000 C CNN
F 2 "" H 7400 5550 50  0001 C CNN
F 3 "" H 7400 5550 50  0001 C CNN
	1    7400 5550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_B7
U 1 1 5EDD636B
P 7900 5550
F 0 "SW_B7" H 8050 5650 50  0000 C CNN
F 1 " " H 7900 5694 50  0000 C CNN
F 2 "" H 7900 5550 50  0001 C CNN
F 3 "" H 7900 5550 50  0001 C CNN
	1    7900 5550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_C7
U 1 1 5EDD6372
P 8400 5550
F 0 "SW_C7" H 8550 5650 50  0000 C CNN
F 1 " " H 8400 5694 50  0000 C CNN
F 2 "" H 8400 5550 50  0001 C CNN
F 3 "" H 8400 5550 50  0001 C CNN
	1    8400 5550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_D7
U 1 1 5EDD6379
P 8900 5550
F 0 "SW_D7" H 9050 5650 50  0000 C CNN
F 1 " " H 8900 5694 50  0000 C CNN
F 2 "" H 8900 5550 50  0001 C CNN
F 3 "" H 8900 5550 50  0001 C CNN
	1    8900 5550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_E7
U 1 1 5EDD6380
P 9400 5550
F 0 "SW_E7" H 9550 5650 50  0000 C CNN
F 1 " " H 9400 5694 50  0000 C CNN
F 2 "" H 9400 5550 50  0001 C CNN
F 3 "" H 9400 5550 50  0001 C CNN
	1    9400 5550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_A8
U 1 1 5EDD6387
P 7400 5800
F 0 "SW_A8" H 7550 5900 50  0000 C CNN
F 1 " " H 7400 5944 50  0000 C CNN
F 2 "" H 7400 5800 50  0001 C CNN
F 3 "" H 7400 5800 50  0001 C CNN
	1    7400 5800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_B8
U 1 1 5EDD638E
P 7900 5800
F 0 "SW_B8" H 8050 5900 50  0000 C CNN
F 1 " " H 7900 5944 50  0000 C CNN
F 2 "" H 7900 5800 50  0001 C CNN
F 3 "" H 7900 5800 50  0001 C CNN
	1    7900 5800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_C8
U 1 1 5EDD6395
P 8400 5800
F 0 "SW_C8" H 8550 5900 50  0000 C CNN
F 1 " " H 8400 5944 50  0000 C CNN
F 2 "" H 8400 5800 50  0001 C CNN
F 3 "" H 8400 5800 50  0001 C CNN
	1    8400 5800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_D8
U 1 1 5EDD639C
P 8900 5800
F 0 "SW_D8" H 9050 5900 50  0000 C CNN
F 1 " " H 8900 5944 50  0000 C CNN
F 2 "" H 8900 5800 50  0001 C CNN
F 3 "" H 8900 5800 50  0001 C CNN
	1    8900 5800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW_E8
U 1 1 5EDD63A3
P 9400 5800
F 0 "SW_E8" H 9550 5900 50  0000 C CNN
F 1 " " H 9400 5944 50  0000 C CNN
F 2 "" H 9400 5800 50  0001 C CNN
F 3 "" H 9400 5800 50  0001 C CNN
	1    9400 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 4050 7200 4300
Wire Wire Line
	7200 4300 7200 4550
Connection ~ 7200 4300
Wire Wire Line
	7200 4550 7200 4800
Connection ~ 7200 4550
Connection ~ 7200 4800
Wire Wire Line
	7200 4800 7200 5050
Connection ~ 7200 5050
Wire Wire Line
	7200 5050 7200 5300
Connection ~ 7200 5300
Wire Wire Line
	7200 5300 7200 5550
Connection ~ 7200 5550
Wire Wire Line
	7200 5550 7200 5800
Wire Wire Line
	7700 4050 7700 4300
Connection ~ 7700 4300
Wire Wire Line
	7700 4300 7700 4550
Connection ~ 7700 4550
Wire Wire Line
	7700 4550 7700 4800
Connection ~ 7700 4800
Wire Wire Line
	7700 4800 7700 5050
Connection ~ 7700 5050
Wire Wire Line
	7700 5050 7700 5300
Connection ~ 7700 5300
Wire Wire Line
	7700 5300 7700 5550
Connection ~ 7700 5550
Wire Wire Line
	7700 5550 7700 5800
Wire Wire Line
	8200 4050 8200 4300
Connection ~ 8200 4300
Wire Wire Line
	8200 4300 8200 4550
Connection ~ 8200 4550
Wire Wire Line
	8200 4550 8200 4800
Connection ~ 8200 4800
Wire Wire Line
	8200 4800 8200 5050
Connection ~ 8200 5050
Wire Wire Line
	8200 5050 8200 5300
Connection ~ 8200 5300
Wire Wire Line
	8200 5300 8200 5550
Connection ~ 8200 5550
Wire Wire Line
	8200 5550 8200 5800
Wire Wire Line
	8700 4050 8700 4300
Connection ~ 8700 4300
Wire Wire Line
	8700 4300 8700 4550
Connection ~ 8700 4550
Wire Wire Line
	8700 4550 8700 4800
Connection ~ 8700 4800
Wire Wire Line
	8700 4800 8700 5050
Connection ~ 8700 5050
Wire Wire Line
	8700 5050 8700 5300
Connection ~ 8700 5300
Wire Wire Line
	8700 5300 8700 5550
Connection ~ 8700 5550
Wire Wire Line
	8700 5550 8700 5800
Wire Wire Line
	9200 4050 9200 4300
Connection ~ 9200 4300
Wire Wire Line
	9200 4300 9200 4550
Connection ~ 9200 4550
Wire Wire Line
	9200 4550 9200 4800
Connection ~ 9200 4800
Wire Wire Line
	9200 4800 9200 5050
Connection ~ 9200 5050
Wire Wire Line
	9200 5050 9200 5300
Connection ~ 9200 5300
Wire Wire Line
	9200 5300 9200 5550
Connection ~ 9200 5550
Wire Wire Line
	9200 5550 9200 5800
Wire Wire Line
	7600 4050 7600 4150
Wire Wire Line
	7600 4150 8100 4150
Wire Wire Line
	8100 4150 8100 4050
Wire Wire Line
	8100 4150 8600 4150
Wire Wire Line
	8600 4150 8600 4050
Connection ~ 8100 4150
Wire Wire Line
	8600 4150 9100 4150
Wire Wire Line
	9100 4150 9100 4050
Connection ~ 8600 4150
Wire Wire Line
	9100 4150 9600 4150
Wire Wire Line
	9600 4150 9600 4050
Connection ~ 9100 4150
Wire Wire Line
	7200 4050 7200 3700
Wire Wire Line
	7200 3700 8050 3700
Connection ~ 7200 4050
Wire Wire Line
	7700 4050 7700 3800
Wire Wire Line
	7700 3800 8150 3800
Connection ~ 7700 4050
Wire Wire Line
	8200 4050 8200 3850
Wire Wire Line
	8200 3850 8250 3850
Connection ~ 8200 4050
Wire Wire Line
	8700 4050 8700 3850
Wire Wire Line
	8700 3850 8350 3850
Connection ~ 8700 4050
Wire Wire Line
	9200 4000 9200 3750
Wire Wire Line
	9200 3750 8450 3750
Wire Wire Line
	9600 4150 10000 4150
Wire Wire Line
	10000 4150 10000 4600
Connection ~ 9600 4150
Wire Wire Line
	7600 4300 7600 4400
Wire Wire Line
	7600 4400 8100 4400
Wire Wire Line
	8100 4400 8100 4300
Wire Wire Line
	8100 4400 8600 4400
Wire Wire Line
	8600 4400 8600 4300
Connection ~ 8100 4400
Wire Wire Line
	8600 4400 9100 4400
Wire Wire Line
	9100 4400 9100 4300
Connection ~ 8600 4400
Wire Wire Line
	9100 4400 9600 4400
Wire Wire Line
	9600 4400 9600 4300
Connection ~ 9100 4400
Wire Wire Line
	9600 4400 9900 4400
Wire Wire Line
	9900 4400 9900 4700
Connection ~ 9600 4400
Wire Wire Line
	7600 4550 7600 4650
Wire Wire Line
	7600 4650 8100 4650
Wire Wire Line
	8100 4650 8100 4550
Wire Wire Line
	8100 4650 8600 4650
Wire Wire Line
	8600 4650 8600 4550
Connection ~ 8100 4650
Wire Wire Line
	8600 4650 9100 4650
Wire Wire Line
	9100 4650 9100 4550
Connection ~ 8600 4650
Wire Wire Line
	9100 4650 9600 4650
Wire Wire Line
	9600 4650 9600 4550
Connection ~ 9100 4650
Wire Wire Line
	9600 4650 9800 4650
Wire Wire Line
	9800 4650 9800 4800
Connection ~ 9600 4650
Wire Wire Line
	7600 4800 7600 4900
Wire Wire Line
	7600 4900 8100 4900
Wire Wire Line
	8100 4900 8100 4800
Wire Wire Line
	8100 4900 8600 4900
Wire Wire Line
	8600 4900 8600 4800
Connection ~ 8100 4900
Wire Wire Line
	8600 4900 9100 4900
Wire Wire Line
	9100 4900 9100 4800
Connection ~ 8600 4900
Wire Wire Line
	9100 4900 9600 4900
Wire Wire Line
	9600 4900 9600 4800
Connection ~ 9100 4900
Wire Wire Line
	7600 5050 7600 5150
Wire Wire Line
	7600 5150 8100 5150
Wire Wire Line
	8100 5150 8100 5050
Wire Wire Line
	8100 5150 8600 5150
Wire Wire Line
	8600 5150 8600 5050
Connection ~ 8100 5150
Wire Wire Line
	8600 5150 9100 5150
Wire Wire Line
	9100 5150 9100 5050
Connection ~ 8600 5150
Wire Wire Line
	9100 5150 9600 5150
Wire Wire Line
	9600 5150 9600 5050
Connection ~ 9100 5150
Wire Wire Line
	7600 5300 7600 5400
Wire Wire Line
	7600 5400 8100 5400
Wire Wire Line
	8100 5400 8100 5300
Wire Wire Line
	8100 5400 8600 5400
Wire Wire Line
	8600 5400 8600 5300
Connection ~ 8100 5400
Wire Wire Line
	8600 5400 9100 5400
Wire Wire Line
	9100 5400 9100 5300
Connection ~ 8600 5400
Wire Wire Line
	9100 5400 9600 5400
Wire Wire Line
	9600 5400 9600 5300
Connection ~ 9100 5400
Wire Wire Line
	7600 5550 7600 5650
Wire Wire Line
	7600 5650 8100 5650
Wire Wire Line
	8100 5650 8100 5550
Wire Wire Line
	8100 5650 8600 5650
Wire Wire Line
	8600 5650 8600 5550
Connection ~ 8100 5650
Wire Wire Line
	8600 5650 9100 5650
Wire Wire Line
	9100 5650 9100 5550
Connection ~ 8600 5650
Wire Wire Line
	9100 5650 9600 5650
Wire Wire Line
	9600 5650 9600 5550
Connection ~ 9100 5650
Wire Wire Line
	7600 5800 7600 5900
Wire Wire Line
	7600 5900 8100 5900
Wire Wire Line
	8100 5900 8100 5800
Wire Wire Line
	8100 5900 8600 5900
Wire Wire Line
	8600 5900 8600 5800
Connection ~ 8100 5900
Wire Wire Line
	8600 5900 9100 5900
Wire Wire Line
	9100 5900 9100 5800
Connection ~ 8600 5900
Wire Wire Line
	9100 5900 9600 5900
Wire Wire Line
	9600 5900 9600 5800
Connection ~ 9100 5900
Connection ~ 9600 4900
Wire Wire Line
	9800 5000 9800 5150
Wire Wire Line
	9800 5150 9600 5150
Connection ~ 9600 5150
Wire Wire Line
	9600 5400 9900 5400
Wire Wire Line
	9900 5400 9900 5100
Connection ~ 9600 5400
Wire Wire Line
	9600 5900 10000 5900
Wire Wire Line
	10000 5900 10000 5300
Connection ~ 9600 5900
Wire Wire Line
	9600 5650 9950 5650
Wire Wire Line
	9950 5650 9950 5200
Connection ~ 9600 5650
Wire Wire Line
	4100 2600 4300 2600
Wire Wire Line
	4100 2900 4300 2900
Wire Wire Line
	3800 2600 3800 2700
Wire Wire Line
	3800 2700 3550 2700
Wire Wire Line
	3550 2800 3800 2800
Wire Wire Line
	3800 2800 3800 2900
Text GLabel 8050 3550 1    50   BiDi ~ 0
C1
Text GLabel 8150 3550 1    50   BiDi ~ 0
C2
Text GLabel 8250 3550 1    50   BiDi ~ 0
C3
Text GLabel 8350 3550 1    50   BiDi ~ 0
C4
Text GLabel 8450 3550 1    50   BiDi ~ 0
C5
Wire Wire Line
	8050 3700 8050 3550
Wire Wire Line
	8150 3550 8150 3800
Wire Wire Line
	8250 3550 8250 3850
Wire Wire Line
	8350 3550 8350 3850
Wire Wire Line
	8450 3550 8450 3750
Text GLabel 10150 4600 2    50   BiDi ~ 0
R1
Text GLabel 10150 4700 2    50   BiDi ~ 0
R2
Text GLabel 10150 4800 2    50   BiDi ~ 0
R3
Text GLabel 10150 4900 2    50   BiDi ~ 0
R4
Text GLabel 10150 5000 2    50   BiDi ~ 0
R5
Text GLabel 10150 5100 2    50   BiDi ~ 0
R6
Text GLabel 10150 5200 2    50   BiDi ~ 0
R7
Text GLabel 10150 5300 2    50   BiDi ~ 0
R8
Wire Wire Line
	10000 4600 10150 4600
Wire Wire Line
	9900 4700 10150 4700
Wire Wire Line
	9800 4800 10150 4800
Wire Wire Line
	9600 4900 10150 4900
Wire Wire Line
	9800 5000 10150 5000
Wire Wire Line
	9900 5100 10150 5100
Wire Wire Line
	9950 5200 10150 5200
Wire Wire Line
	10000 5300 10150 5300
$Comp
L power:+5V #PWR?
U 1 1 5EF6445F
P 2950 1450
F 0 "#PWR?" H 2950 1300 50  0001 C CNN
F 1 "+5V" H 2965 1623 50  0000 C CNN
F 2 "" H 2950 1450 50  0001 C CNN
F 3 "" H 2950 1450 50  0001 C CNN
	1    2950 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5EF644E9
P 5250 2550
F 0 "#PWR?" H 5250 2400 50  0001 C CNN
F 1 "+5V" H 5265 2723 50  0000 C CNN
F 2 "" H 5250 2550 50  0001 C CNN
F 3 "" H 5250 2550 50  0001 C CNN
	1    5250 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EF6460B
P 4100 5200
F 0 "#PWR?" H 4100 4950 50  0001 C CNN
F 1 "GND" H 4105 5027 50  0000 C CNN
F 2 "" H 4100 5200 50  0001 C CNN
F 3 "" H 4100 5200 50  0001 C CNN
	1    4100 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1800 2950 1700
Wire Wire Line
	3050 1800 3050 1700
Wire Wire Line
	3050 1700 2950 1700
Connection ~ 2950 1700
Wire Wire Line
	2350 2100 2350 1700
Wire Wire Line
	2350 1700 2950 1700
NoConn ~ 4850 3150
NoConn ~ 4850 3550
NoConn ~ 4850 3650
NoConn ~ 4850 3750
NoConn ~ 4850 3850
Wire Wire Line
	5250 2850 5250 2600
Wire Wire Line
	5650 3050 5650 2600
Wire Wire Line
	5650 2600 5250 2600
Connection ~ 5250 2600
Wire Wire Line
	5250 2600 5250 2550
Wire Wire Line
	5650 3350 5800 3350
Wire Wire Line
	5800 3350 5800 2600
Wire Wire Line
	5800 2600 5650 2600
Connection ~ 5650 2600
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5EFFF0D9
P 5150 1350
F 0 "J1" H 5230 1342 50  0000 L CNN
F 1 "ISP" H 5230 1251 50  0000 L CNN
F 2 "" H 5150 1350 50  0001 C CNN
F 3 "~" H 5150 1350 50  0001 C CNN
	1    5150 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1450 2950 1700
Wire Wire Line
	2950 4800 2950 4950
Wire Wire Line
	2950 4950 4100 4950
Wire Wire Line
	5250 4450 5250 4950
Wire Wire Line
	4100 5200 4100 4950
Connection ~ 4100 4950
Wire Wire Line
	4100 4950 5250 4950
Wire Wire Line
	4850 4250 4850 4500
Wire Wire Line
	4850 4500 3550 4500
Wire Wire Line
	4850 4150 4750 4150
Wire Wire Line
	4750 4150 4750 4400
Wire Wire Line
	4750 4400 3550 4400
Wire Wire Line
	4850 4050 4650 4050
Wire Wire Line
	4650 4050 4650 4300
Wire Wire Line
	4650 4300 3550 4300
Wire Wire Line
	4850 3950 4550 3950
Wire Wire Line
	4550 3950 4550 4200
Wire Wire Line
	4550 4200 3550 4200
Wire Wire Line
	4850 3250 4750 3250
Wire Wire Line
	4750 3250 4750 3850
Wire Wire Line
	4750 3850 4450 3850
Wire Wire Line
	4450 3850 4450 4100
Wire Wire Line
	4450 4100 3550 4100
Wire Wire Line
	4850 3050 4650 3050
Wire Wire Line
	4650 3050 4650 3750
Wire Wire Line
	4650 3750 4350 3750
Wire Wire Line
	4350 3750 4350 4000
Wire Wire Line
	4350 4000 3550 4000
Text GLabel 4950 1650 0    50   Output ~ 0
RESET
$Comp
L power:+5V #PWR?
U 1 1 5EE54026
P 4800 1000
F 0 "#PWR?" H 4800 850 50  0001 C CNN
F 1 "+5V" H 4815 1173 50  0000 C CNN
F 2 "" H 4800 1000 50  0001 C CNN
F 3 "" H 4800 1000 50  0001 C CNN
	1    4800 1000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EE5EAD3
P 4800 1150
F 0 "#PWR?" H 4800 900 50  0001 C CNN
F 1 "GND" H 4805 977 50  0000 C CNN
F 2 "" H 4800 1150 50  0001 C CNN
F 3 "" H 4800 1150 50  0001 C CNN
	1    4800 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	4950 1150 4950 1000
Wire Wire Line
	4950 1000 4800 1000
Wire Wire Line
	4950 1250 4800 1250
Wire Wire Line
	4800 1250 4800 1150
Text GLabel 3550 3600 2    50   Input ~ 0
RESET
Wire Wire Line
	3550 2200 5900 2200
Wire Wire Line
	5900 2200 5900 3450
Wire Wire Line
	5900 3450 5650 3450
$Comp
L MCU_Microchip_ATmega:ATmega328P-PU U1
U 1 1 5EDD3B9E
P 2950 3300
F 0 "U1" H 2309 3346 50  0000 R CNN
F 1 "ATmega328P-PU" H 2309 3255 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 2950 3300 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 2950 3300 50  0001 C CNN
	1    2950 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2400 4100 2400
Wire Wire Line
	3550 2500 4200 2500
Wire Wire Line
	3750 2600 3750 2250
Wire Wire Line
	3750 2250 4000 2250
Wire Wire Line
	3550 2600 3750 2600
Text GLabel 3550 2100 2    50   BiDi ~ 0
C1
Text GLabel 3550 2300 2    50   BiDi ~ 0
C2
Text GLabel 3550 3000 2    50   BiDi ~ 0
R1
Text GLabel 3550 3100 2    50   BiDi ~ 0
R2
Text GLabel 3550 3200 2    50   BiDi ~ 0
R3
Text GLabel 3550 3300 2    50   BiDi ~ 0
R4
Text GLabel 3550 3400 2    50   BiDi ~ 0
R5
Text GLabel 3550 3500 2    50   BiDi ~ 0
R6
Text GLabel 3550 3800 2    50   BiDi ~ 0
R7
Text GLabel 3550 3900 2    50   BiDi ~ 0
R8
Wire Wire Line
	4000 1350 4950 1350
Wire Wire Line
	4000 1350 4000 2250
Wire Wire Line
	4100 1450 4950 1450
Wire Wire Line
	4100 1450 4100 2400
Wire Wire Line
	4200 1550 4950 1550
Wire Wire Line
	4200 1550 4200 2500
Text Label 4950 1350 2    50   ~ 0
SCK
Text Label 4950 1450 2    50   ~ 0
MOSI
Text Label 4950 1550 2    50   ~ 0
MISO
$EndSCHEMATC
