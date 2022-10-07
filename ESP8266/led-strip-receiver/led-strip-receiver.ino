#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <stdlib.h>

const int nodeNumber = 231;
const char nodeName[] = "living room light strip";

// Interestingly, the device is able to connect to WiFi even with these values empty.
// It must be somehow re-using a previous authentication session.

const char* ssid     = "";      // SSID of local network
const char* password = "";   // Password on network

IPAddress staticIP(192, 168, 1, nodeNumber); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
//IPAddress dns(1, 1, 1, 1);  //DNS
const char* deviceName = "wemos";

#define RED_LED 4
#define GREEN_LED 0
#define BLUE_LED 5
int ledPin = LED_BUILTIN;
 
WiFiServer server(80);


bool isOn = true;
String currentColor = "FFFFFF";
String currentBrightness = "100";

String responseBody;
int responseStatus;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);


   pinMode(GREEN_LED, OUTPUT);
   pinMode(RED_LED, OUTPUT);
   pinMode(BLUE_LED, OUTPUT);
//   TurnOn();
//   delay(5000);
//   TurnOff();
//  


  Serial.begin(9600);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.print("node number: ");
  Serial.print(nodeNumber);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, subnet, gateway);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(ledPin, HIGH);

  displayCurrentColor();
}

void loop() {
  responseBody = "";
  responseStatus = 500;

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) { return; }

  // Wait until the client sends some data
  Serial.println("==========");
  Serial.println("new client");
  while (!client.available()) { delay(1); }

  // Read the first line of the request
  digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  responseBody = handleRequest(request, client);

  if (responseBody == "") {
    responseBody = "Error: not found";
    responseStatus = 404;
  }
  else { responseStatus = 200; }
  Serial.println(responseBody);

  // Return the response
  switch (responseStatus) {
    default :
    case 500: client.println("HTTP/1.1 500 ERROR"); break;
    case 404: client.println("HTTP/1.1 404 NOT FOUND"); break;
    case 200: client.println("HTTP/1.1 200 OK"); break;
  }//-----end switch
  // client.println("Content-Type: application/json");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println(""); //  do not forget this one
  client.println(responseBody);
  delay(1);
  // TODO: Find out when to use client.stop().  
  // Leaving disabled for now, since it breaks core functionality
  //client.stop();
  Serial.println("Client disconnected");
  Serial.println("==========");
  Serial.println("");
  digitalWrite(ledPin, HIGH);
}

void(* resetDevice) (void) = 0;

String handleRequest(String request, WiFiClient client) {
  String endpoint1 = splitString(request, '/', 1);
  endpoint1 = splitString(endpoint1, ' ', 0);
  Serial.println(endpoint1);
  // TODO:  Implement mapping logic to replace if/else
  // Switch not possible here with strings in C++
  // Potential solution here https://stackoverflow.com/a/4535852
  if (endpoint1 == "set") { return handleSet(request); }
  else if (endpoint1 == "statuspower") { return handleStatusPower(); }
  else if (endpoint1 == "statusbrightness") { return handleStatusBrightness(); }
  else if (endpoint1 == "statuscolor") { return handleStatusColor(); }
  else if (endpoint1 == "on") { return handleOn(); }
  else if (endpoint1 == "off") { return handleOff(); }
  else if (endpoint1 == "brightness") { return handleBrightness(request); }
  else if (endpoint1 == "reset") { handleDeviceReset(client); }

  return "";
}

String handleSet(String request) {
  String endpoint2 = splitString(request, '/', 2);
  endpoint2 = splitString(endpoint2, ' ', 0);
  Serial.println(endpoint2);
  currentColor = endpoint2;
  displayCurrentColor();
  return currentColor;
}

String handleBrightness(String request) {
  String endpoint2 = splitString(request, '/', 2);
  endpoint2 = splitString(endpoint2, ' ', 0);
  Serial.println(endpoint2);
  currentBrightness = endpoint2;
  displayCurrentColor();
  return currentBrightness;
}

String handleOff() {
  isOn = false;
  displayCurrentColor();
  return "0";
}

String handleOn() {
  isOn = true;
  displayCurrentColor();
  return "1";
}

String handleStatusPower() {
  if(isOn) { return "1"; }
  return "0";
}

String handleStatusColor() {
  return currentColor;
}

String handleStatusBrightness() {
  return currentBrightness;
}

void handleDeviceReset(WiFiClient client) {
  // TODO: Refactor this to complete the response to the browser.
  // Currently, the request gets re-sent repeatedly by the broswer.
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println(""); //  do not forget this one
  client.println("reset");
  delay(1);
  client.stop();
  Serial.println("Client disconnected");
  Serial.println("==========");
  Serial.println("Resetting device...");
  resetDevice();
}

void displayCurrentColor() {
  displayPrimaryColor(currentColor.substring(0, 2), RED_LED);
  displayPrimaryColor(currentColor.substring(2, 4), GREEN_LED);
  displayPrimaryColor(currentColor.substring(4, 6), BLUE_LED);
}

void displayPrimaryColor(String hexCodeFragment, int ledPin) {
  int effectiveBrightness = currentBrightness.toInt();
  if (!isOn) { effectiveBrightness = 0; }
  unsigned long int outputValue = strtoul(hexCodeFragment.c_str(), NULL, 16);
  outputValue = outputValue * effectiveBrightness * .1;
  analogWrite(ledPin, outputValue);
}

String splitString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


// int brightness = 255;
// int gBright = 0;
// int rBright = 0;
// int bBright = 0;
// int fadeSpeed = 10;

// void TurnOn() { 
//    for (int i = 0; i < 256; i++) {
//        analogWrite(RED_LED, rBright);
//        rBright +=1;
//        delay(fadeSpeed);
//    }
 
//    for (int i = 0; i < 256; i++) {
//        analogWrite(BLUE_LED, bBright);
//        bBright += 1;
//        delay(fadeSpeed);
//    } 
//    for (int i = 0; i < 256; i++) {
//        analogWrite(GREEN_LED, gBright);
//        gBright +=1;
//        delay(fadeSpeed);
//    } 
// }

// void TurnOff() {
//    for (int i = 0; i < 256; i++) {
//        analogWrite(GREEN_LED, brightness);
//        analogWrite(RED_LED, brightness);
//        analogWrite(BLUE_LED, brightness);
 
//        brightness -= 1;
//        delay(fadeSpeed);
//    }
// }
