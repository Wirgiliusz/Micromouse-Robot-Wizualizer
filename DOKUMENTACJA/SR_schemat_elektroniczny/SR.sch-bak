EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 9843 8268
encoding utf-8
Sheet 1 1
Title "Micromouse Wizualizer "
Date "2020-06-06"
Rev "3"
Comp "Magdalena Sałęga, Kamil Drewniak"
Comment1 "https://github.com/Wirgiliusz/Micromouse-Robot-Wizualizer"
Comment2 "Full documentation (in Polish) available at:"
Comment3 "This document is part of \"Miromouse Robot Visualizer\" project"
Comment4 ""
$EndDescr
$Comp
L SR-rescue:STM32F429I-DISC1-MOJ U1
U 2 1 5E7742CA
P 2900 4100
F 0 "U1" H 2900 6347 50  0000 C CNN
F 1 "STM32F429I-DISC1" H 2900 6256 50  0000 C CNN
F 2 "MODULE_STM32F429I-DISC1" H 2900 4100 50  0001 L BNN
F 3 "Manufacturer recommendations" H 2900 4100 50  0001 L BNN
F 4 "" H 2900 4100 50  0001 L BNN "Pole4"
F 5 "1.0" H 2900 4100 50  0001 L BNN "Pole5"
F 6 "STMicroelectronics" H 2900 4100 50  0001 L BNN "Pole6"
	2    2900 4100
	1    0    0    -1  
$EndComp
Text GLabel 2200 3200 0    50   Input ~ 0
SENSOR1
Text GLabel 2200 3400 0    50   Input ~ 0
SENSOR2
Text GLabel 2200 4700 0    50   Input ~ 0
SENSOR3
Text GLabel 2200 4900 0    50   Input ~ 0
SENSOR4
Text GLabel 2200 5800 0    50   Input ~ 0
PWM_CH1
Text GLabel 4900 3450 0    50   Input ~ 0
PWM_CH2
Text GLabel 6300 4850 2    50   Input ~ 0
PWM_CH3
Text GLabel 6300 4950 2    50   Input ~ 0
PWM_CH4
$Comp
L SR-rescue:HC-05-RF_Bluetooth-MOJ U2
U 1 1 5E7D6251
P 4050 1250
F 0 "U2" H 4528 988 50  0000 L CNN
F 1 "HC-05-RF_Bluetooth" H 4528 897 50  0000 L CNN
F 2 "" H 4050 1250 50  0001 C CNN
F 3 "" H 4050 1250 50  0001 C CNN
	1    4050 1250
	1    0    0    -1  
$EndComp
NoConn ~ 3950 1850
NoConn ~ 4450 1850
Text GLabel 2200 2700 0    50   Input ~ 0
ENCODER_R
Text GLabel 4900 3750 0    50   Input ~ 0
ENCODER_L
$Comp
L SR-rescue:STM32F429I-DISC1-MOJ U1
U 1 1 5E753BA3
P 5600 4150
F 0 "U1" V 5554 6260 50  0000 L CNN
F 1 "STM32F429I-DISC1" V 5645 6260 50  0000 L CNN
F 2 "MODULE_STM32F429I-DISC1" H 5600 4150 50  0001 L BNN
F 3 "Manufacturer recommendations" H 5600 4150 50  0001 L BNN
F 4 "" H 5600 4150 50  0001 L BNN "Pole4"
F 5 "1.0" H 5600 4150 50  0001 L BNN "Pole5"
F 6 "STMicroelectronics" H 5600 4150 50  0001 L BNN "Pole6"
	1    5600 4150
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7805 U3
U 1 1 5E957AE2
P 7450 3000
F 0 "U3" H 7450 3242 50  0000 C CNN
F 1 "L7805" H 7450 3151 50  0000 C CNN
F 2 "" H 7475 2850 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 7450 2950 50  0001 C CNN
	1    7450 3000
	0    -1   -1   0   
$EndComp
$Comp
L SR-rescue:Battery_double_pack-Device-MOJ BT1
U 1 1 5E95A143
P 7350 3100
F 0 "BT1" V 6777 2925 50  0000 C CNN
F 1 "Battery_double_pack (2x4V)" V 6850 2900 50  0000 C CNN
F 2 "" V 7000 3060 50  0001 C CNN
F 3 "" V 7000 3060 50  0001 C CNN
	1    7350 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3300 7200 3300
Text GLabel 7000 2900 1    50   Input ~ 0
Motors
Wire Wire Line
	4900 2950 4150 2950
Wire Wire Line
	4150 1850 4150 2950
Wire Wire Line
	4900 2850 4050 2850
Wire Wire Line
	4050 1850 4050 2850
Wire Wire Line
	4350 1850 4350 2300
Wire Wire Line
	4350 2300 3600 2300
Wire Wire Line
	4250 1850 4250 6000
Wire Wire Line
	4250 6000 3600 6000
Text HLabel 6300 4550 2    50   Input ~ 0
FMC_A0
Text HLabel 6300 4450 2    50   Input ~ 0
FMC_A1
Text HLabel 6300 4350 2    50   Input ~ 0
FMC_A2
Text HLabel 6300 4250 2    50   Input ~ 0
FMC_A3
Text HLabel 6300 4150 2    50   Input ~ 0
FMC_A4
Text HLabel 6300 4050 2    50   Input ~ 0
FMC_A5
Wire Wire Line
	7450 2250 7450 2700
NoConn ~ 6300 2350
Text HLabel 3600 4300 2    50   Input ~ 0
SPI5_SCK
Text HLabel 3600 4200 2    50   Input ~ 0
SPI5_MISO
Text HLabel 3600 4100 2    50   Input ~ 0
SPI5_MOSI
Text HLabel 3600 4000 2    50   Input ~ 0
LTDC_DE
NoConn ~ 2200 2500
Text HLabel 2200 4600 0    50   Input ~ 0
FMC_SDNWE
Text HLabel 2200 3000 0    50   Input ~ 0
LTDC_B5
Text HLabel 2200 3100 0    50   Input ~ 0
LTDC_VSYNC
Text HLabel 2200 3300 0    50   Input ~ 0
LTDC_G2
Text HLabel 2200 3600 0    50   Input ~ 0
LTDC_R3
Text HLabel 2200 3700 0    50   Input ~ 0
LTDC_R6
Text HLabel 3600 3900 2    50   Input ~ 0
FMC_SDNRAS
Text HLabel 3600 3800 2    50   Input ~ 0
FMC_A6
Text HLabel 3600 3700 2    50   Input ~ 0
FMC_A7
Text HLabel 3600 3600 2    50   Input ~ 0
FMC_A8
Text HLabel 3600 3500 2    50   Input ~ 0
FMC_A9
Text HLabel 3600 3200 2    50   Input ~ 0
FMC_A11
Text HLabel 3600 3300 2    50   Input ~ 0
FMC_A10
Text HLabel 3600 5400 2    50   Input ~ 0
FMC_D4
Text HLabel 3600 5300 2    50   Input ~ 0
FMC_D5
Text HLabel 3600 5200 2    50   Input ~ 0
FMC_D6
Text HLabel 3600 5100 2    50   Input ~ 0
FMC_D7
Text HLabel 3600 5000 2    50   Input ~ 0
FMC_D8
Text HLabel 3600 4900 2    50   Input ~ 0
FMC_D9
Text HLabel 3600 4800 2    50   Input ~ 0
FMC_D10
Text HLabel 3600 4700 2    50   Input ~ 0
FMC_D11
Text HLabel 3600 4600 2    50   Input ~ 0
FMC_D12
Text HLabel 2200 3900 0    50   Input ~ 0
LTDC_G4
Text HLabel 2200 4000 0    50   Input ~ 0
LTDC_G5
Text HLabel 2200 5400 0    50   Input ~ 0
FMC_D13
Text HLabel 2200 5500 0    50   Input ~ 0
FMC_D14
Text HLabel 2200 5600 0    50   Input ~ 0
FMC_D15
Text HLabel 3600 5700 2    50   Input ~ 0
FMC_D0
Text HLabel 3600 5600 2    50   Input ~ 0
FMC_D1
Text HLabel 6300 3850 2    50   Input ~ 0
FMC_BA0
Text HLabel 6300 3750 2    50   Input ~ 0
FMC_BA1
Text HLabel 6300 3650 2    50   Input ~ 0
LTDC_R7
Text HLabel 6300 3550 2    50   Input ~ 0
LTDC_CLK
Text HLabel 6300 3450 2    50   Input ~ 0
FMC_SDCLK
Wire Wire Line
	7000 3650 7000 3750
Wire Wire Line
	6300 6050 7000 6050
Wire Wire Line
	7000 3750 7750 3750
Wire Wire Line
	7750 3750 7750 3000
Connection ~ 7000 3750
Wire Wire Line
	7000 3750 7000 6050
Wire Wire Line
	6300 2250 7450 2250
Text HLabel 4900 4450 0    50   Input ~ 0
LTDC_HSYNC
Text HLabel 4900 4550 0    50   Input ~ 0
LTDC_G6
Text HLabel 4900 4750 0    50   Input ~ 0
I2C3_SDA
Text HLabel 4900 2750 0    50   Input ~ 0
I2C3_SCL
Text HLabel 4900 3050 0    50   Input ~ 0
LTDC_R4
Text HLabel 4900 3150 0    50   Input ~ 0
LTDC_R5
Text HLabel 4900 4850 0    50   Input ~ 0
LTDC_R2
Text HLabel 4900 5550 0    50   Input ~ 0
FMC_D2
Text HLabel 4900 5650 0    50   Input ~ 0
FMC_D3
Text HLabel 4900 5850 0    50   Input ~ 0
LTDC_G7
Text HLabel 6300 5650 2    50   Input ~ 0
LTDC_B2
Text HLabel 6300 3250 2    50   Input ~ 0
LTDC_G3
Text HLabel 6300 3150 2    50   Input ~ 0
LTDC_B3
Text HLabel 6300 3050 2    50   Input ~ 0
LTDC_B4
Text HLabel 6300 2850 2    50   Input ~ 0
LED
Text HLabel 6300 2750 2    50   Input ~ 0
FMC_SDNCAS
Text HLabel 4900 3850 0    50   Input ~ 0
FMC_SDCKE1
Text HLabel 4900 3950 0    50   Input ~ 0
FMC_SDNE1
Text HLabel 4900 4150 0    50   Input ~ 0
FMC_NBL0
Text HLabel 4900 4250 0    50   Input ~ 0
FMC_NBL1
NoConn ~ 2200 2800
NoConn ~ 2200 2900
NoConn ~ 2200 3800
NoConn ~ 2200 4100
NoConn ~ 2200 4200
NoConn ~ 2200 4300
NoConn ~ 2200 4400
NoConn ~ 2200 4800
NoConn ~ 2200 5000
NoConn ~ 2200 5100
NoConn ~ 2200 5700
NoConn ~ 3600 5800
NoConn ~ 3600 4400
NoConn ~ 3600 3100
NoConn ~ 3600 3000
NoConn ~ 3600 2800
NoConn ~ 3600 2700
NoConn ~ 4900 2550
NoConn ~ 4900 3250
NoConn ~ 4900 3350
NoConn ~ 4900 3650
NoConn ~ 4900 4050
NoConn ~ 4900 4650
NoConn ~ 4900 4950
NoConn ~ 4900 5050
NoConn ~ 4900 5150
NoConn ~ 4900 5250
NoConn ~ 4900 5350
NoConn ~ 4900 5750
NoConn ~ 6300 5850
NoConn ~ 6300 5750
NoConn ~ 6300 5550
NoConn ~ 6300 5350
NoConn ~ 6300 5250
NoConn ~ 6300 5150
NoConn ~ 6300 5050
NoConn ~ 6300 4750
NoConn ~ 6300 3350
NoConn ~ 6300 2950
Text GLabel 9200 6100 0    50   Input ~ 0
EXTERNAL_CONNECTION
Text HLabel 9200 6250 0    50   Input ~ 0
INTERNAL_CONNECTION
NoConn ~ 9200 6400
Text Label 9200 6400 2    50   ~ 0
NO_CONNECTION
$EndSCHEMATC
