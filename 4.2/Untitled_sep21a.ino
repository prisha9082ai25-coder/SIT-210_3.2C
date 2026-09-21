#include "thingProperties.h"
#include <WiFiNINA.h>

// LED PINS


const int livingRoomLED = 4;
const int bathroomLED   = 5;
const int closetLED     = 6;

// WEB SERVER
  
WiFiServer server(80);

// SETUP

void setup() {

  Serial.begin(9600);
  delay(1500);

  // Configure LED pins as outputs
  pinMode(livingRoomLED, OUTPUT);
  pinMode(bathroomLED, OUTPUT);
  pinMode(closetLED, OUTPUT);

  // Start all LEDs in the OFF state
  digitalWrite(livingRoomLED, LOW);
  digitalWrite(bathroomLED, LOW);
  digitalWrite(closetLED, LOW);

  // Initialise Arduino Cloud properties
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Enable Arduino Cloud debugging information
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Start the local web server on port 80
  server.begin();
  Serial.println("Web server started.");
}

// LOOP

void loop() {

  // Keep the Arduino IoT Cloud connection active
  ArduinoCloud.update();

  // Check whether a browser/client has connected
  WiFiClient client = server.available();

  if (client) {
    handleWebRequest(client);
  }
}

// WEB REQUEST HANDLER

void handleWebRequest(WiFiClient client) {

  String request = "";

  unsigned long startTime = millis();

  // Read the HTTP request sent by the browser
  while (client.connected() && millis() - startTime < 2000) {

    if (client.available()) {

      char c = client.read();

      request += c;

      // Stop reading once the complete HTTP header is received
      if (request.endsWith("\r\n\r\n")) {
        break;
      }
    }
  }

  // LIVING ROOM CONTROL

  // Turn the Living Room LED ON
  if (request.indexOf("GET /living/on") >= 0) {

    livingRoom = true;

    digitalWrite(livingRoomLED, HIGH);

    Serial.println("HTML -> Living Room ON");
  }

  // Turn the Living Room LED OFF
  if (request.indexOf("GET /living/off") >= 0) {

    livingRoom = false;

    digitalWrite(livingRoomLED, LOW);

    Serial.println("HTML -> Living Room OFF");
  }

  // BATHROOM CONTROL

  // Turn the Bathroom LED ON
  if (request.indexOf("GET /bathroom/on") >= 0) {

    bathroom = true;

    digitalWrite(bathroomLED, HIGH);

    Serial.println("HTML -> Bathroom ON");
  }

  // Turn the Bathroom LED OFF
  if (request.indexOf("GET /bathroom/off") >= 0) {

    bathroom = false;

    digitalWrite(bathroomLED, LOW);

    Serial.println("HTML -> Bathroom OFF");
  }


    // CLOSET CONTROL

  // Turn the Closet LED ON
  if (request.indexOf("GET /closet/on") >= 0) {

    closet = true;

    digitalWrite(closetLED, HIGH);

    Serial.println("HTML -> Closet ON");
  }

  // Turn the Closet LED OFF
  if (request.indexOf("GET /closet/off") >= 0) {

    closet = false;

    digitalWrite(closetLED, LOW);

    Serial.println("HTML -> Closet OFF");
  }


  // SEND RESPONSE TO BROWSER


  // Send the HTTP response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();

  // Start the HTML webpage
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Linda Smart Lights</title>");
  client.println("</head>");

  // Start webpage body
  client.println("<body>");
  client.println("<h1>Linda's Smart Lights</h1>");

  client.println("<p>Arduino Nano 33 IoT</p>");

  // Display Living Room status
  client.println("<h2>Living Room</h2>");

  if (livingRoom) {
    client.println("<p>ON</p>");
  } else {
    client.println("<p>OFF</p>");
  }

  // Display Bathroom status
  client.println("<h2>Bathroom</h2>");

  if (bathroom) {
    client.println("<p>ON</p>");
  } else {
    client.println("<p>OFF</p>");
  }

  // Display Closet status
  client.println("<h2>Closet</h2>");

  if (closet) {
    client.println("<p>ON</p>");
  } else {
    client.println("<p>OFF</p>");
  }

  // End webpage
  client.println("</body>");
  client.println("</html>");

  // Give the client a short time to receive the response
  delay(1);

  // Close the client connection
  client.stop();
}


// ARDUINO CLOUD CALLBACKS

// Called when the Living Room Cloud property changes
void onLivingRoomChange() {

  digitalWrite(
    livingRoomLED,
    livingRoom ? HIGH : LOW
  );
}


// Called when the Bathroom Cloud property changes
void onBathroomChange() {

  digitalWrite(
    bathroomLED,
    bathroom ? HIGH : LOW
  );
}


// Called when the Closet Cloud property changes
void onClosetChange() {

  digitalWrite(
    closetLED,
    closet ? HIGH : LOW
  );
}