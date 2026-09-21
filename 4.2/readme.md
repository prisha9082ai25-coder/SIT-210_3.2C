# Task 4.2D – Calling a Function from the Web

## Project Overview

This project demonstrates a web-controlled lighting system implemented using an Arduino Nano 33 IoT.

Three individual lights can be controlled using the web interface. For the hardware implementation, three LEDs have been used to represent the Living Room, Bathroom and Closet lights.

Each lighting output is controlled independently. The user can therefore switch individual lights ON or OFF without affecting the other outputs.

The project incorporates embedded systems development with web-based interaction and wireless communication.

---

## Project Objective

The objective of this task is to demonstrate how a physical embedded system can be controlled using a web interface.

Once completed, the system allows a user to interact with a web dashboard and control the physical LED outputs connected to the Arduino Nano 33 IoT.

The project focuses on:

- Web-based device control

- Embedded system programming

- Wireless communication

- Arduino Nano 33 IoT

- Arduino IoT Cloud configuration

- Digital output control

- HTML-based user interface

- JavaScript-based interaction

- System testing and debugging

---

## System Description

The system comprises an Arduino Nano 33 IoT connected to three LEDs.

Each LED represents a different room:

| Room | Arduino Output |

|---|---|

| Living Room | D4 |

| Bathroom | D5 |

| Closet | D6 |

The three outputs operate independently. A user can therefore control one room without changing the state of the other rooms.

The Arduino acts as the embedded controller while the web interface provides the user interaction.

---

## Hardware Implementation

The physical system was constructed using an Arduino Nano 33 IoT, three LEDs, current-limiting resistors, a breadboard and jumper wires.

The three LEDs were connected to separate digital outputs of the Arduino.

The circuit was initially tested independently to verify that the LEDs could be switched correctly. This helped to ensure that the physical hardware was operating correctly before incorporating the web-based controls.

The final hardware implementation provides three independent lighting outputs corresponding to the three rooms.

---

## Arduino IoT Cloud

Arduino IoT Cloud was used during the course of developing and configuring the IoT device.

A Thing was configured for the Arduino Nano 33 IoT and the lighting properties were created for the three rooms.

The properties represent the state of:

- Living Room

- Bathroom

- Closet

The device and Thing configuration were checked during development to ensure that the Arduino was correctly recognised and that the required properties were available.

Arduino IoT Cloud was also useful during the development process for checking the device connectivity and configuration.

---

## Web Dashboard

The web dashboard was developed to provide a simple interface for controlling the lighting system.

The dashboard contains separate controls for the three rooms.

The user can select the required room and change their lighting state.

The dashboard was designed to have independent controls so that:

- The Living Room can be controlled independently.

- The Bathroom can be controlled independently.

- The Closet can be controlled independently.

This provides a straightforward interface for operating the physical lighting outputs.

---

## Web Interface Development

The web interface was developed using HTML, CSS and JavaScript.

HTML was used to structure the webpage and provide the required interface elements.

CSS was used to organise and style the dashboard.

JavaScript was used to process user interactions and communicate the selected commands to the Arduino.

The complete web implementation is provided separately in the Web folder of this repository.

---

## Arduino Firmware

The Arduino Nano 33 IoT contains the embedded firmware responsible for operating the physical lighting system.

The firmware performs the required initialisation of the hardware and network connection and maintains communication with the web-based control system.

The program also manages the three digital outputs corresponding to the Living Room, Bathroom and Closet LEDs.

The Arduino firmware is provided separately in the Arduino folder of this repository.

---

## Wi-Fi Communication

Wi-Fi communication allows for the Arduino Nano 33 IoT to communicate with the web interface over the local network.

During development, the Arduino was connected to the available Wi-Fi network and its local IP address was identified.

The IP address was then used when configuring the web interface to communicate with the Arduino.

This allowed the browser-based dashboard to send commands to the embedded device over the network.

---

## Independent Lighting Control

A key feature of the implementation is the ability to independently control the three lighting outputs.

Each room is associated with its own Arduino digital output.

This means that changing the state of one room does not automatically change the state of the other rooms.

For example, the Living Room can remain ON while the Bathroom and Closet remain OFF.

This independent control was verified during testing.

---

## Testing and Validation

Testing was performed progressively throughout development.

The hardware was tested, followed by network connectivity, web interface operation and finally complete system integration.

### Hardware Testing

Each LED was tested independently to verify:

- Correct physical connection

- Correct Arduino output

- ON operation

- OFF operation

### Network Testing

The network connection was checked to verify:

- Arduino Wi-Fi connectivity

- Device availability

- Local IP address

- Communication between the computer and Arduino

### Web Interface Testing

The individual web controls were tested for all three rooms.

| Test | Action | Expected Result |

|---|---|---|
| 1 | Living Room ON | Living Room LED turns ON |

| 2 | Living Room OFF | Living Room LED turns OFF |

| 3 | Bathroom ON | Bathroom LED turns ON |

| 4 | Bathroom OFF | Bathroom LED turns OFF |

| 5 | Closet ON | Closet LED turns ON |

| 6 | Closet OFF | Closet LED turns OFF |

## Project Outcomes

The completed implementation demonstrates the ability to integrate an embedded controller with a web-based user interface.

The project demonstrates:

- Physical hardware control

- Digital GPIO operation

- Wireless networking

- Arduino IoT Cloud configuration

- Web interface development

- Web-to-device communication

- Independent output control

- Hardware and software testing

- Troubleshooting and debugging

The final system provides a functional method of controlling three physical lighting outputs through a web interface.
