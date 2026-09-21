#include <WiFiNINA.h>       // Library used to connect the Arduino Nano 33 IoT to WiFi
#include <PubSubClient.h>   // Library used for MQTT communication

// WiFi Credentials

// Name of the WiFi network/hotspot
char ssid[] = "Galaxy A56 5G FF25";

// Password of the WiFi network/hotspot
char password[] = "1234567890";


// / MQTT Broker Configuration

// Address of the public EMQX MQTT broker
const char* mqttServer = "broker.emqx.io";

// MQTT communication port
// Port 1883 is the standard port for non-encrypted MQTT communication
const int mqttPort = 1883;

// MQTT Topics

// Topic used for sending and receiving "Wave" messages
const char* waveTopic = "ES/Wave";

// Topic used for sending and receiving "Pat" messages
const char* patTopic = "ES/Pat";

// Pin Configuration

// Ultrasonic sensor trigger pin
const int trigPin = 2;

// Ultrasonic sensor echo pin
const int echoPin = 3;

// First LED connected to digital pin 4
const int led1 = 4;

// Second LED connected to digital pin 5
const int led2 = 5;


// WiFi and MQTT Client Objects

// Creates a WiFi client that allows the Arduino to communicate
// with the network and MQTT broker
WiFiClient wifiClient;

// Creates the MQTT client using the WiFi connection
PubSubClient mqttClient(wifiClient);

// Function Prototypes

// Function used to connect/reconnect the Arduino to the MQTT broker
void connectMQTT();

// Function called automatically whenever an MQTT message is received
void callback(char* topic, byte* payload, unsigned int length);


void setup() {

  // Start serial communication so that information can be
  // displayed in the Arduino Serial Monitor
  Serial.begin(9600);

  // Ultrasonic Sensor Pin Setup

  // Trigger pin sends the ultrasonic pulse
  pinMode(trigPin, OUTPUT);

  // Echo pin receives the reflected ultrasonic pulse
  pinMode(echoPin, INPUT);


  // LED Pin Setup

  // Configure both LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Initially keep both LEDs turned OFF
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  // WiFi Connection

  Serial.print("Connecting to WiFi");

  // Keep trying to connect until the Arduino successfully
  // connects to the specified WiFi network
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {

    // Print a dot for every failed/repeated connection attempt
    Serial.print(".");

    // Wait for 2 seconds before trying again
    delay(2000);
  }

  // Print a new line after WiFi connection is successful
  Serial.println();

  Serial.println("WiFi Connected");

  // MQTT Configuration

  // Set the MQTT broker address and communication port
  mqttClient.setServer(mqttServer, mqttPort);

  // Tell the MQTT client which function should be called
  // whenever a subscribed message is received
  mqttClient.setCallback(callback);


  // Connect to the MQTT broker
  connectMQTT();
}


void loop() {
  
  // MQTT Connection Check

  // If the MQTT connection is lost, try to reconnect
  if (!mqttClient.connected()) {
    connectMQTT();
  }

  // Continuously checks for incoming MQTT messages.
  // This is required so that the callback() function can
  // process messages received from the broker.
  mqttClient.loop();

  // Ultrasonic Distance Measurement

  // Variable used to store the time taken by the ultrasonic
  // signal to travel to the object and return
  long duration;

  // Variable used to store the calculated distance in centimetres
  float distance;


  // Make sure the trigger pin starts in LOW state
  digitalWrite(trigPin, LOW);

  // Small delay to stabilise the trigger signal
  delayMicroseconds(2);


  // Send a HIGH pulse to the ultrasonic sensor
  digitalWrite(trigPin, HIGH);

  // Keep the trigger HIGH for 10 microseconds
  delayMicroseconds(10);


  // End the ultrasonic trigger pulse
  digitalWrite(trigPin, LOW);


  // Measure how long the echo pin remains HIGH.
  // This represents the time taken by the ultrasonic wave
  // to travel to the object and return to the sensor.
  duration = pulseIn(echoPin, HIGH);


  // Convert the measured time into distance in centimetres.
  // 0.0343 cm/microsecond is the approximate speed of sound.
  // Dividing by 2 accounts for the outgoing and returning journey.
  distance = duration * 0.0343 / 2;


  // Display the measured distance in the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // Wave Detection

  // If an object is detected between 15 cm and 30 cm,
  // the system treats the movement as a "Wave".
  if (distance >= 15 && distance <= 30) {

    Serial.println("Wave Detected");


    // Publish the name "Prisha" to the ES/Wave MQTT topic.
    // Any MQTT client subscribed to this topic can receive
    // this message.
    mqttClient.publish(waveTopic, "Prisha");


    // Wait for 2 seconds before detecting another action
    delay(2000);
  }

  // Pat Detection

  // If an object is detected closer than 10 cm,
  // the system treats it as a "Pat".
  //
  // distance > 0 prevents an invalid zero-distance reading
  // from being treated as a pat.
  else if (distance > 0 && distance < 10) {

    Serial.println("Pat Detected");


    // Publish the name "Prisha" to the ES/Pat MQTT topic.
    mqttClient.publish(patTopic, "Prisha");


    // Wait for 2 seconds before detecting another action
    delay(2000);
  }


  // Short delay before taking the next distance measurement
  delay(100);
}

// MQTT Connection Function

void connectMQTT() {

  // Continue attempting to connect until the MQTT connection
  // is successfully established
  while (!mqttClient.connected()) {

    Serial.println("Connecting to MQTT...");


    // Create a unique MQTT client ID.
    // A random number is added so that multiple devices can
    // connect to the same broker without using the same ID.
    String clientID = "NanoClient-";
    clientID += String(random(1000, 9999));


    // Attempt to connect to the MQTT broker using the generated ID
    if (mqttClient.connect(clientID.c_str())) {

      Serial.println("MQTT Connected");

      // MQTT Topic Subscriptions

      // Subscribe to the Wave topic so the Arduino can receive
      // Wave messages from the MQTT broker
      mqttClient.subscribe(waveTopic);


      // Subscribe to the Pat topic so the Arduino can receive
      // Pat messages from the MQTT broker
      mqttClient.subscribe(patTopic);


      // Display confirmation messages in Serial Monitor
      Serial.println("Subscribed to ES/Wave");
      Serial.println("Subscribed to ES/Pat");

    } else {

      // If connection fails, display the MQTT error state
      Serial.print("MQTT Failed. State: ");
      Serial.println(mqttClient.state());


      // Wait 3 seconds before attempting another connection
      delay(3000);
    }
  }
}

// MQTT Callback Function

// This function is automatically executed when the Arduino
// receives a message from one of the subscribed MQTT topics.
//
// topic   = MQTT topic from which the message was received
// payload = actual message data
// length  = length of the received message
void callback(char* topic, byte* payload, unsigned int length) {

  // String used to store the incoming MQTT message
  String receivedMessage = "";


  // Convert each byte of the MQTT payload into a character
  // and add it to the received message
  for (unsigned int i = 0; i < length; i++) {
    receivedMessage += (char)payload[i];
  }


  // Display the received MQTT message in Serial Monitor
  Serial.print("Message received: ");
  Serial.println(receivedMessage);

  // Wave Message Handling

  // Check whether the received message came from the ES/Wave topic
  if (String(topic) == waveTopic) {

    Serial.println("Turning LEDs ON");


    // Turn both LEDs ON when a Wave message is received
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }

  // Pat Message Handling

  // Check whether the received message came from the ES/Pat topic
  else if (String(topic) == patTopic) {

    Serial.println("Turning LEDs OFF");


    // Turn both LEDs OFF when a Pat message is received
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
}
