
#include <Wire.h>
#include <BH1750.h>

// Create a BH1750 light sensor object.
// The sensor is used to measure the surrounding light intensity in lux.
BH1750 lightMeter;

// Pin definitions
// PIR sensor is connected to digital pin 2.
// Push button is connected to digital pin 3.
// Two LEDs are connected to pins 5 and 6.
const int pirPin = 2;
const int buttonPin = 3;
const int led1 = 5;
const int led2 = 6;

// Variables
// These flags are set by the interrupt service routines when
// motion or a button press is detected.
volatile bool motionDetected = false;
volatile bool buttonPressed = false;

// Stores the current state of the two lights.
// true = lights ON, false = lights OFF.
bool lightsOn = false;

// Stores the light intensity measured by the BH1750 sensor in lux.
float lightLevel;

// Interrupt Service Routine for the PIR sensor.
// This function is automatically called when the PIR sensor
// detects a rising signal, indicating motion.
void pirISR() {
  motionDetected = true;
}

// Interrupt Service Routine for the push button.
// This function is automatically called when the button is pressed
// and the input signal changes from HIGH to LOW.
void buttonISR() {
  buttonPressed = true;
}

void setup() {
  // Start serial communication for displaying system status
  // and sensor/event information in the Serial Monitor.
  Serial.begin(9600);

  // Initialise I2C communication for the BH1750 light sensor.
  Wire.begin();

  // Initialise the BH1750 sensor so that light measurements
  // can be read during program execution.
  lightMeter.begin();

  // Configure both LED pins as outputs because the Arduino
  // controls the LEDs by setting their digital states.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Configure the PIR sensor as a digital input.
  pinMode(pirPin, INPUT);

  // Configure the push button using the internal pull-up resistor.
  // This keeps the input HIGH normally and changes to LOW
  // when the button is pressed.
  pinMode(buttonPin, INPUT_PULLUP);

  // Attach an interrupt to the PIR sensor.
  // RISING means the interrupt is triggered when the signal
  // changes from LOW to HIGH, indicating detected motion.
  attachInterrupt(digitalPinToInterrupt(pirPin), pirISR, RISING);

  // Attach an interrupt to the push button.
  // FALLING means the interrupt is triggered when the signal
  // changes from HIGH to LOW when the button is pressed.
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);

  // Display a message confirming that the system has started.
  Serial.println("System Started");
}

void loop() {

  // Read the current surrounding light intensity from the BH1750 sensor.
  // The measured value is returned in lux and stored in lightLevel.
  lightLevel = lightMeter.readLightLevel();

  // PIR Interrupt
  // Check whether the PIR interrupt has detected motion.
  if (motionDetected) {
    // Reset the flag so that the same motion event is not
    // processed repeatedly in the following loop cycles.
    motionDetected = false;

    // Display the motion detection event in the Serial Monitor.
    Serial.println("Motion Detected!");

    // If the measured light level is below 30 lux,
    // the environment is considered dark.
    if (lightLevel < 30) {     // Dark threshold

      // Turn both LEDs ON because motion has been detected
      // while the surrounding environment is dark.
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);

      // Update the light state variable to indicate that
      // the lights are currently switched on.
      lightsOn = true;

      // Display the reason for switching the lights on.
      Serial.println("Dark detected.");
      Serial.println("Lights ON");
    }
    else {
      // If the light level is 30 lux or higher, the environment
      // is considered bright enough, so the LEDs remain OFF.
      Serial.println("Bright environment.");
      Serial.println("Lights remain OFF");
    }
  }

  // ---------- Push Button Interrupt ----------
  // Check whether the push button interrupt has detected a press.
  if (buttonPressed) {
    // Reset the flag after processing the button event.
    buttonPressed = false;

    // Toggle the current light state.
    // If the lights are ON, they will turn OFF.
    // If the lights are OFF, they will turn ON.
    lightsOn = !lightsOn;

    // Apply the updated light state to both LEDs.
    digitalWrite(led1, lightsOn);
    digitalWrite(led2, lightsOn);

    // Display the new light state in the Serial Monitor.
    if (lightsOn)
      Serial.println("Push Button Pressed - Lights ON");
    else
      Serial.println("Push Button Pressed - Lights OFF");
  }

  // Small delay to provide a short pause between loop iterations
  // and allow the system to process sensor and interrupt events.
  delay(100);
}
