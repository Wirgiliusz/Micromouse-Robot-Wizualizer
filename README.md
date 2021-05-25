# Micromouse Robot Wizualizer
Project of a Micromouse robot with labirynth solving algorithms and visualisation on LCD display and in RViZ software.

[Readme in polish](/docs/README_pl.md)

---

## Project description
The project is made of two main parts:
1. Project of the Micromouse robot - mechanical, electronical and software part of the robot. 
   - Mechanical part consists of the robot housing. 
   - Electronical part consists of **STM32F429I-DISC1 microcontroller**, **HC-05 Bluetooth module**, DC motors, **LCD disply**, distance sensors and power supply. 
   - Software part consists of functions responsible for robot movement, environment scanning, and algorithms for searching the labirynth, finding the shortests path and driving to the finish.
3. Project of the robot visualization - functions responsible for communication with the LCD display, Bluetooth module, and visualization in RViZ software. 
   - The LCD display visualizes labirynt known to robot and shows information about speed and sensor readings. 
   - The bluetooth module communicates with PC computer via Python script and sends informations about robot. 
   - The PC computer uses RViZ software created in C++ language to visuallize the robot and labirynth in real-time.

---

## Results
### Robot

<img src=/docs/imgs/robot.jpg width="700">

### RViZ visualization

<img src=/docs/imgs/rviz.png width="700">

### LCD display

<img src=/docs/imgs/lcd.png width="700">

### Electronic diagram
<img src=/docs/imgs/electric_diagram.png width="700">

### Program flows
<img src=/docs/imgs/programsFlowChart.png width="700">

---

### Running the visualization software
To run the second part of the project you must install the ROS software with RViZ library and follow these steps:
1. Run the ROS software
```shell
$ roscore
```
3. In new console window run the application that communicates with RViZ and Bluetooth script
```shell
$ rosrun using_markers basic_shapes
```
4. In next console run the script for connecting with bluetooth module
```shell
$ rosrun using_markers publisher_node.py
```
4. In next console run the RViZ software
```shell
$ rviz rviz
```
6. Follow instructions that can be seen after running the script

