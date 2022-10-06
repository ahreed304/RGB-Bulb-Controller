// TODO: replace request parsing code with code from original controller


#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
//#include <IRremoteESP8266.h>
//#include <IRsend.h>
//#include <stdlib.h>



#define RED_LED 4
#define GREEN_LED 0
#define BLUE_LED 5
#define switchButton 7


const int nodeNumber = 231;
const char nodeName[] = "living room light strip";

const char* ssid     = "";      // SSID of local network
const char* password = "";   // Password on network

//Static IP address configuration
IPAddress staticIP(192, 168, 1, nodeNumber); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
//IPAddress dns(1, 1, 1, 1);  //DNS
const char* deviceName = "wemos";

int ledPin = LED_BUILTIN;
 
WiFiServer server(80);

void(* resetDevice) (void) = 0;


// network properties
char homebridgeServer[] = "192.168.1.20";
int homebridgePort = 8581;

// request handling
String requestBuffer;

// variables
int powerStatus = 0;
int brightness = 100;
int buttonState = 0;

// color properties
String color = "FFFFFF";
long colorR = 0;
long colorG = 0;
long colorB = 0;

// notification handling
WiFiClient notificationClient;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);


   pinMode(GREEN_LED, OUTPUT);
   pinMode(RED_LED, OUTPUT);
   pinMode(BLUE_LED, OUTPUT);

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
}

void loop() {
//  Serial.println("foo");
//  delay(5000);

  WiFiClient client = server.available();
  if (client) {
    Serial.println("==========");
    Serial.println("New client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        requestBuffer += c;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {

          Serial.println("The request has finished, the following data was received: ");

          // extracting the first line
          String firstLine = requestBuffer.substring(0, requestBuffer.indexOf('\n'));
          Serial.println(firstLine);

          // check if the command is present inside the line
          if (firstLine.indexOf("on") != -1) {
            Serial.println("Turning ON");

            powerStatus = 1;

            analogWrite(RED_LED, colorR);
            analogWrite(GREEN_LED, colorG);
            analogWrite(BLUE_LED, colorB);

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(powerStatus);
          }

          if (firstLine.indexOf("off") != -1) {
            Serial.println("Turning OFF");

            powerStatus = 0;

            analogWrite(RED_LED, 0);
            analogWrite(GREEN_LED, 0);
            analogWrite(BLUE_LED, 0);

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(powerStatus);

          }

          if (firstLine.indexOf("set") != -1) {
            color = firstLine.substring(9, 15);
            Serial.print("Color set to: ");
            Serial.println(color);

            long number = strtol( &color[0], NULL, 16);
            colorR = number >> 16;
            colorG = number >> 8 & 0xFF;
            colorB = number & 0xFF;

            Serial.print("With RGB values of R: ");
            Serial.print(colorR);
            Serial.print(" G: ");
            Serial.print(colorG);
            Serial.print(" B: ");
            Serial.println(colorB);

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(color);
          }

          if (firstLine.indexOf("brightness") != -1) {
            brightness = firstLine.substring(16, firstLine.indexOf(" ", 16)).toInt();
            Serial.print("Brightness set to: ");
            Serial.println(brightness);

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(brightness);
          }

          if (firstLine.indexOf("statuspower") != -1) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(powerStatus);
            
            Serial.print("Power status sent");
          }

          if (firstLine.indexOf("statusbrightness") != -1) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(brightness);
            
            Serial.println("Brightness status sent");
          }

          if (firstLine.indexOf("statuscolor") != -1) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(color);
            
            Serial.println("Color status sent");
          }
          

          requestBuffer = "";
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("==========");
  }

  // switching the status physically by pressing a button
  buttonState = digitalRead(switchButton);

  if (buttonState == HIGH) {
    Serial.println("==========");
    Serial.println("Button changed the state, sending a notification to HomeBridge");
  
    if (notificationClient.connect(homebridgeServer, homebridgePort)) {

      if (powerStatus == 0) {
        powerStatus = 1;
      } else {
        powerStatus = 0;
      }
  
      Serial.print("Successfully connected to: ");
      Serial.println(notificationClient.remoteIP());
  
      notificationClient.println("POST /47110815 HTTP/1.1");
      notificationClient.print("Host: ");
      notificationClient.print(homebridgeServer);
      notificationClient.print(":");
      notificationClient.println(homebridgePort);
      notificationClient.println("User-Agent: Arduino/1.0");

      if (powerStatus == 0) {
        notificationClient.println("Content-Length: 41");
      } else {
        notificationClient.println("Content-Length: 40");
      }
      
      notificationClient.println("Content-Type: application/json");
      notificationClient.println();

      if (powerStatus == 0) {
        notificationClient.println("{\"characteristic\": \"On\",\"value\": \"false\"}");
      } else {
        notificationClient.println("{\"characteristic\": \"On\",\"value\": \"true\"}");
      }
  
      delay(1);
      notificationClient.stop();

      Serial.println("Notification sent");
      Serial.println("==========");
    } else {
      Serial.println("Connection failed");
      Serial.println("==========");
    }
  }
}
