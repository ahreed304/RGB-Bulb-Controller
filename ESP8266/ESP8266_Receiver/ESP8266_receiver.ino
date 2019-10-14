#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const char nodeName[] = "night stand 1";
const int nodeNumber = 2;

const char* ssid     = "Bikini Bottom WiFi";      // SSID of local network
const char* password = "motowNshufflE";   // Password on network

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 202); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
//IPAddress dns(1, 1, 1, 1);  //DNS
const char* deviceName = "wemos2.local";

int ledPin = LED_BUILTIN;
WiFiServer server(80);
IRsend irsend(5); 

class IRCommand {
  public:
    long IRCode;
    String Command;
    
    IRCommand(long iRCode, String command) {
      IRCode = iRCode;
      Command = command;
    }
};

IRCommand white(0xFF52AD, "white");
IRCommand red(0xFF6897, "red");
IRCommand orange(0xFF30CF, "orange");
IRCommand gold(0xFF38C7, "gold");
IRCommand yellow(0xFF4AB5, "yellow");
IRCommand green(0xFF9867, "green");
IRCommand turquoise(0xFF18E7, "turquoise");
IRCommand cyan(0xFF5AA5, "cyan");
IRCommand blue(0xFFB04F, "blue");
IRCommand purple(0xFF7A85, "purple");
IRCommand magenta(0xFF10EF, "magenta");
IRCommand pink(0xFF42BD, "pink");
IRCommand powerOn(0xFFA25D, "powerOn");
IRCommand powerOff(0xFFE21D, "powerOff");
IRCommand brighter(0xFFA857, "brighter");
IRCommand dimmer(0xFF906F, "dimmer");
IRCommand flash(0xFF22DD, "flash (lavender)");
IRCommand smooth(0xFFE01F, "smooth (crimson)");
IRCommand speed(0xFF629D, "speed (indigo)");
IRCommand brightness25 (NULL, "brightness 25");
IRCommand brightness50 (NULL, "brightness 50");
IRCommand brightness75 (NULL, "brightness 75");
IRCommand brightness100 (NULL, "brightness 100");

IRCommand commandArray[] = {white, red , orange, gold, yellow, green, turquoise, cyan, blue, purple, magenta, pink, powerOn, powerOff, brighter, dimmer, flash, smooth, speed, brightness25, brightness50, brightness75, brightness100};


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  
  Serial.begin(9600);
  delay(10);
  irsend.begin();
 
  
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
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  String commandIn = getValue(request, '/', 1);
  // int len = strlen(xval)-4;
  commandIn.remove(commandIn.length()-5 ,5);
  Serial.println(commandIn);
  long IRCode = lookupIRCode(commandIn);
  Serial.println(IRCode);
  if(IRCode != 0)  {irsend.sendNEC(IRCode, 32);}
  else
  {   if(commandIn == "brightness25") {for(int y = 0; y<3; y++)  {irsend.sendNEC(dimmer.IRCode, 32);}} //BRIGHTNESS 25%   -- brightness down(x3)
      else if(commandIn == "brightness50") {for(int y = 0; y<3; y++)  {irsend.sendNEC(dimmer.IRCode, 32);} //BRIGHTNESS 50%   -- brightness down(x3), 
        for(int y = 0; y<1; y++)  {irsend.sendNEC(brighter.IRCode, 32);} //                 -- brightness up(x1)
      }
      else if(commandIn == "brightness75") {for(int y = 0; y<3; y++)  {irsend.sendNEC(dimmer.IRCode, 32);} //BRIGHTNESS 75%   -- brightness down(x3),
        for(int y = 0; y<2; y++)  {irsend.sendNEC(brighter.IRCode, 32);} //                 -- brightness up(x2)
      }
      else if(commandIn == "brightness100") {for(int y = 0; y<3; y++)  {irsend.sendNEC(brighter.IRCode, 32);}} //BRIGHTNESS 100%  -- brightness up(x3)
  }
//    switch(commandIn) 
//    {          
//      case "brightness25": for(int y = 0; y<3; y++)  {irsend.sendNEC(dimmer.IRCode, 32);} //BRIGHTNESS 25%   -- brightness down(x3)
//                break;
//      case "brightness50": for(int y = 0; y<3; y++)  {irsend.sendNEC(dimmer.IRCode, 32);} //BRIGHTNESS 50%   -- brightness down(x3), 
//                for(int y = 0; y<1; y++)  {irsend.sendNEC(brighter.IRCode, 32);} //                 -- brightness up(x1)
//                break;
//      case "brightness75": for(int y = 0; y<3; y++)  {irsend.sendNEC(dimmer.IRCode, 32);} //BRIGHTNESS 75%   -- brightness down(x3),
//                for(int y = 0; y<2; y++)  {irsend.sendNEC(brighter.IRCode, 32);} //                 -- brightness up(x2)
//                break;
//      case "brightness100": for(int y = 0; y<3; y++)  {irsend.sendNEC(brighter.IRCode, 32);} //BRIGHTNESS 100%  -- brightness up(x3)
//                break;
//    }
//  }
  irsend.sendNEC(IRCode, 32);
  
  char responseBody[100];
    char commandInCharArray[commandIn.length() + 1];
    commandIn.toCharArray(commandInCharArray, commandIn.length() +1);
//    sprintf(responseBody, "{\"node\":{\"nodeName\":\"%s\",\"nodeNumber\":%hd},\"commandName\":\"%s\",\"ircode\":%ld}",nodeName, nodeNumber, commandInCharArray, IRCode);
    sprintf(responseBody, "{\"nodeName\":\"%s\",\"nodeNumber\":%hd,\"command\":\"%s\",\"ircode\":%ld}",nodeName, nodeNumber, commandInCharArray, IRCode);

//    sprintf(responseBody, "{\"ircode\": %ld}",IRCode);

  Serial.println(responseBody);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println(""); //  do not forget this one
  client.println(responseBody);

 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
  digitalWrite(ledPin, HIGH);
}


long lookupIRCode(String command) {
  long IRCode;
  for(int i = 0; i<sizeof(commandArray); i++) {
    if(command == commandArray[i].Command)  {
      IRCode = commandArray[i].IRCode;
      return IRCode;
    }
  }
  return IRCode;
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
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
