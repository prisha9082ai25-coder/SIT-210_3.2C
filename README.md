# SIT-210_3.2C
# MQTT-Based Gesture Detection System Using Arduino Nano

## Overview

This project demonstrates an IoT-based embedded system using an Arduino Nano, an HC-SR04 ultrasonic sensor, two LEDs, and the EMQX public MQTT broker. The system detects hand gestures (wave and pat) and uses the MQTT publish-subscribe protocol to control two LEDs representing hallway and bathroom lights.

---

## Features

- Detects hand gestures using an HC-SR04 ultrasonic sensor.
- Turns both LEDs ON when a wave message is received.
- Turns both LEDs OFF when a pat message is received.
- Displays received MQTT messages on the Serial Monitor.

---

## Hardware Components

- Arduino Nano
- HC-SR04 Ultrasonic Sensor
- 2 LEDs
- 2 × 220Ω Resistors
- Breadboard
- Jumper Wires
