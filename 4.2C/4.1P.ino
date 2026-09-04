#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Pin definitions
const int pirPin = 2;
const int buttonPin = 3;
const int led1 = 5;
const int led2 = 6;

// Variables
volatile bool motionDetected = false;
volatile bool buttonPressed = false;

bool lightsOn = false;
float lightLevel;

// Interrupt for PIR
void pirISR() {
  motionDetected = true;
}

// Interrupt for Push Button
void buttonISR() {
  buttonPressed = true;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(pirPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pirPin), pirISR, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);

  Serial.println("System Started");
}

void loop() {

  // Read light level
  lightLevel = lightMeter.readLightLevel();

  // ---------- PIR Interrupt ----------
  if (motionDetected) {
    motionDetected = false;

    Serial.println("Motion Detected!");

    if (lightLevel < 30) {     // Dark threshold
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      lightsOn = true;

      Serial.println("Dark detected.");
      Serial.println("Lights ON");
    }
    else {
      Serial.println("Bright environment.");
      Serial.println("Lights remain OFF");
    }
  }

  // ---------- Push Button Interrupt ----------
  if (buttonPressed) {
    buttonPressed = false;

    lightsOn = !lightsOn;

    digitalWrite(led1, lightsOn);
    digitalWrite(led2, lightsOn);

    if (lightsOn)
      Serial.println("Push Button Pressed - Lights ON");
    else
      Serial.println("Push Button Pressed - Lights OFF");
  }

  delay(100);
}