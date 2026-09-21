## Project Overview

The objective of this project is to develop a web-based remote control system for home lighting using an Arduino Nano 33 IoT. The system is designed to allow a user to turn specific lights on/off remotely using a web dashboard. Three LEDs represent different rooms that can be controlled independently:

1. Living Room
2. Bathroom
3. Closet

Each of the three LEDs is connected to a separate digital pin of the Arduino Nano 33 IoT. The web dashboard provides ON/OFF buttons for each of the rooms being represented by an LED.

The project is a demonstration of the following concepts:

1) Embedded systems
2) Arduino Nano 33 IoT
3) Arduino IoT Cloud
4) Wi-Fi communication
5) HTML
6) CSS
7) JavaScript
8) HTTP web requests/responses
9) Digital input/output (GPIO)
10) Web dashboard interaction

# Project Objective

The objective of this project is to showcase ways in which a web interface can be used for controlling physical outputs on an embedded device.

The system can be controlled by anyone who has access to the web dashboard:
1. A user can open the web dashboard
2. The user can choose the room
3. The user can toggle the corresponding light ON or OFF
4. The command will be sent to the embedded device
5. The microcontroller will process the command
6. The microcontroller will change the corresponding digital output
7. The selected LED will be physically switched ON or OFF

The project showcases how the communication between web interface and the embedded device works.

# Hardware Implementation

The hardware implementation uses an Arduino Nano 33 IoT with three LEDs.

Each LED is assigned to an independent digital output.

| Room | Arduino Pin | Output |
|---|---|---|
| Living Room | D4 | Living Room LED |
| Bathroom | D5 | Bathroom LED |
| Closet | D6 | Closet LED |

The separate GPIO assignments allow each room to be controlled independently.

# Arduino IoT Cloud

Arduino IoT Cloud was used during the process of development and configuration of the IoT device. The configuration of the Thing has variables, which stand for the three lighting controls. These are:
• livingRoom
• bathroom
• closet
They stand for the status of these outputs for lighting.

# Web Dashboard

A custom HTML-based dashboard was developed to provide the user interface. The dashboard contains separate controls for the three rooms.

![HTML Dashboard](Images/HTML.png)

## Web dashboard used to control the three lighting outputs.**

The controls are mapped to the Arduino outputs as follows:
Living Room → D4
Bathroom    → D5
Closet      → D6
This allows each LED to be controlled independently.

