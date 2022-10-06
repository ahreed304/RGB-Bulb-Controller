#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
//#include <IRremoteESP8266.h>
//#include <IRsend.h>
#include <stdlib.h>



#define RED_LED 4
#define GREEN_LED 0
#define BLUE_LED 5

int brightness = 255;
int gBright = 0;
int rBright = 0;
int bBright = 0;
int fadeSpeed = 10;

void TurnOn() { 
   for (int i = 0; i < 256; i++) {
       analogWrite(RED_LED, rBright);
       rBright +=1;
       delay(fadeSpeed);
   }
 
   for (int i = 0; i < 256; i++) {
       analogWrite(BLUE_LED, bBright);
       bBright += 1;
       delay(fadeSpeed);
   } 
   for (int i = 0; i < 256; i++) {
       analogWrite(GREEN_LED, gBright);
       gBright +=1;
       delay(fadeSpeed);
   } 
}

void TurnOff() {
   for (int i = 0; i < 256; i++) {
       analogWrite(GREEN_LED, brightness);
       analogWrite(RED_LED, brightness);
       analogWrite(BLUE_LED, brightness);
 
       brightness -= 1;
       delay(fadeSpeed);
   }
}

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

class RGBCommand {
  public:
    long IRCode;
    String Command;

    RGBCommand(long iRCode, String command) {
      IRCode = iRCode;
      Command = command;
    }
};

RGBCommand white(0xFF52AD, "white");
RGBCommand red(0xFF6897, "red");
RGBCommand orange(0xFF30CF, "orange");
RGBCommand gold(0xFF38C7, "gold");
RGBCommand yellow(0xFF4AB5, "yellow");
RGBCommand green(0xFF9867, "green");
RGBCommand turquoise(0xFF18E7, "turquoise");
RGBCommand cyan(0xFF5AA5, "cyan");
RGBCommand blue(0xFFB04F, "blue");
RGBCommand purple(0xFF7A85, "purple");
RGBCommand magenta(0xFF10EF, "magenta");
RGBCommand pink(0xFF42BD, "pink");
RGBCommand powerOn(0xFFA25D, "powerOn");
RGBCommand powerOff(0xFFE21D, "powerOff");
RGBCommand brighter(0xFFA857, "brighter");
RGBCommand dimmer(0xFF906F, "dimmer");
RGBCommand flash(0xFF22DD, "flash (lavender)");
RGBCommand smooth(0xFFE01F, "smooth (crimson)");
RGBCommand speed(0xFF629D, "speed (indigo)");
RGBCommand brightness25 (1, "brightness25");
RGBCommand brightness50 (1, "brightness50");
RGBCommand brightness75 (1, "brightness75");
RGBCommand brightness100 (1, "brightness100");

RGBCommand commandArray[] = {white, red , orange, gold, yellow, green, turquoise, cyan, blue, purple, magenta, pink, powerOn, powerOff, brighter, dimmer, flash, smooth, speed, brightness25, brightness50, brightness75, brightness100};





char http[] = "HTTP/1.1";
char notFound404[] = "HTTP/1.1 404 NOT FOUND";
char ok200[] = "HTTP/1.1 200 OK";

char responseBody[200];
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
//  pinMode(RED, OUTPUT);
//  digitalWrite(RED, HIGH);
//  pinMode(GREEN, OUTPUT);
//  digitalWrite(GREEN, HIGH);
//  pinMode(BLUE, OUTPUT);
//  digitalWrite(BLUE, HIGH);

//  pinMode(10, OUTPUT); digitalWrite(10, HIGH);
//  pinMode(11, OUTPUT); digitalWrite(11, HIGH);
//  pinMode(12, OUTPUT); digitalWrite(12, HIGH);
//  pinMode(13, OUTPUT); digitalWrite(13, HIGH);
//  pinMode(14, OUTPUT); digitalWrite(14, HIGH);
//  pinMode(15, OUTPUT); digitalWrite(15, HIGH);
//  pinMode(16, OUTPUT); digitalWrite(16, HIGH);
//  pinMode(17, OUTPUT); digitalWrite(17, HIGH);
//  pinMode(18, OUTPUT); digitalWrite(18, HIGH);
//  pinMode(19, OUTPUT); digitalWrite(19, HIGH);
//  pinMode(20, OUTPUT); digitalWrite(20, HIGH);

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
  sprintf(responseBody, "");
  responseStatus = 500;

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  String commandIn = getValue(request, '/', 1);
  // int len = strlen(xval)-4;
  commandIn.remove(commandIn.length() - 5 , 5);
  Serial.println(commandIn);
  displayColor(commandIn);
//  if (IRCode == NULL) {
  if (false) {
    sprintf(responseBody, "{\"error\":\"command not found\"}");
    responseStatus = 404;
  }
  else {
    responseStatus = 200;
    char commandInCharArray[commandIn.length() + 1];
    commandIn.toCharArray(commandInCharArray, commandIn.length() + 1);
    sprintf(responseBody, "{\"node\":{\"nodeNumber\":%hd,\"nodeName\":\"%s\"},\"command\":{\"commandName\":\"%s\",\"ircode\":%ld}}", nodeNumber, nodeName, commandInCharArray, "{IRCode}");
    //    sprintf(responseBody, "{\"nodeName\":\"%s\",\"nodeNumber\":%hd,\"command\":\"%s\",\"ircode\":%ld}",nodeName, nodeNumber, commandInCharArray, IRCode);

    //    sprintf(responseBody, "{\"ircode\": %ld}",IRCode);
  }
  Serial.println(responseBody);

  // Return the response
  switch (responseStatus) {
    default :
    case 500: client.println("HTTP/1.1 500 ERROR"); break;
    case 404: client.println("HTTP/1.1 404 NOT FOUND"); break;
    case 200: client.println("HTTP/1.1 200 OK"); break;
  }//-----end switch
  client.println("Content-Type: application/json");
  client.println(""); //  do not forget this one
  client.println(responseBody);


  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
  digitalWrite(ledPin, HIGH);

  // TODO: Find a better place for this logic.
  if (commandIn == "reset") { resetDevice(); }
}

void displayColor(String hexCode) {
  displayPrimaryColor(hexCode.substring(0, 2), RED_LED);
  displayPrimaryColor(hexCode.substring(2, 4), GREEN_LED);
  displayPrimaryColor(hexCode.substring(4, 6), BLUE_LED);
  Serial.println(hexCode);
}

void displayPrimaryColor(String hexCodeFragment, int ledPin) {
  unsigned long int outputValue = strtoul(hexCodeFragment.c_str(), NULL, 16);
  Serial.println(hexCodeFragment);
  analogWrite(ledPin, outputValue);
}
long lookupIRCode(String command) {
  long IRCode;
  for (int i = 0; i < sizeof(commandArray); i++) {
    if (command == commandArray[i].Command)  {
      IRCode = commandArray[i].IRCode;
      return IRCode;
    }
  }
  return NULL;
}


String getValue(String data, char separator, int index)
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
