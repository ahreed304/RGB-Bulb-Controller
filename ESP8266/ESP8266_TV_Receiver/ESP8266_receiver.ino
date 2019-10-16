#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const int nodeNumber = 210;
const char nodeName[] = "tv";

const char* ssid     = "Bikini Bottom WiFi";      // SSID of local network
const char* password = "motowNshufflE";   // Password on network

//Static IP address configuration
IPAddress staticIP(192, 168, 1, nodeNumber); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
//IPAddress dns(1, 1, 1, 1);  //DNS
const char* deviceName = "wemos";

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

IRCommand tvPower(0xA90, "tvPower");
IRCommand volumeDown(0xC90, "");
IRCommand volumeUp(0x490, "");
IRCommand mute(0x290, "mute");
IRCommand input(0xA50, "input");

IRCommand up(0x2F0, "up");
IRCommand down(0xAF0, "down");
IRCommand left(0x2D0, "left");
IRCommand right(0xCD0, "right");
IRCommand enter(0xA70, "enter");

IRCommand hdmi1(0x930, "hdmi1");
IRCommand hdmi2(1, "hdmi2");
IRCommand hdmi3(1, "hdmi3");
IRCommand volumeUp10(1, "volumeUp");
IRCommand volumeDown10(1, "volumeDown");


 
IRCommand commandArray[] = {tvPower, volumeDown, volumeUp, mute, input, up, down, left, right, enter, hdmi1, hdmi2, hdmi3, volumeUp10, volumeDown10};

char responseBody[200];
int responseStatus;

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
  long IRCode = 0;
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
  IRCode = lookupIRCode(commandIn);
  Serial.println(IRCode);

  if (IRCode != 1  && IRCode != NULL)  {
    sendIR(IRCode);
  }
  else if (IRCode == 1) {
    
    if (commandIn == "hdmi2") {
      executeHdmi2();
    }//end if
    else if (commandIn == "hdmi3") {
      executeHdmi3();
    }
    else if (commandIn == "volumeUp") {
      executeVolumeUp10();
    }
    else if (commandIn == "volumeDown") {
      executeVolumeDown10();
    }
  }//end else if


  if (IRCode == NULL) {
    sprintf(responseBody, "{\"error\":\"internal server error\"}");
    responseStatus = 500;
  }
  else {  
    responseStatus = 200;
    char commandInCharArray[commandIn.length() + 1];
    commandIn.toCharArray(commandInCharArray, commandIn.length() + 1);
    sprintf(responseBody, "{\"node\":{\"nodeNumber\":%hd,\"nodeName\":\"%s\"},\"command\":{\"commandName\":\"%s\",\"ircode\":%ld}}", nodeNumber, nodeName, commandInCharArray, IRCode);
    //    sprintf(responseBody, "{\"nodeName\":\"%s\",\"nodeNumber\":%hd,\"command\":\"%s\",\"ircode\":%ld}",nodeName, nodeNumber, commandInCharArray, IRCode);

    //    sprintf(responseBody, "{\"ircode\": %ld}",IRCode);
  }

  respond(client, responseStatus, responseBody);

  
  Serial.println(responseBody);

  
  Serial.println("Client disconnected");
  Serial.println("");
  digitalWrite(ledPin, HIGH);
}


void respond(WiFiClient client, int responseStatus, char responseBody[])  {
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

void sendIR(long IRCode) {
    irsend.sendSony(IRCode, 12);
    delay(100);
}

void executeHdmi2()  {
  sendIR(input.IRCode);
  delay(500);
  for(int i = 0; i<6; i++) {
    sendIR(down.IRCode);
  }
  sendIR(up.IRCode);
  sendIR(enter.IRCode);
}

void executeHdmi3()  {
  sendIR(input.IRCode);
  delay(500);
  for(int i = 0; i<6; i++) {
    sendIR(down.IRCode);
  }
  sendIR(enter.IRCode);
}

void executeVolumeUp10()  {
  for(int i = 0; i<10; i++) {
    sendIR(volumeUp.IRCode);
  }
}

void executeVolumeDown10()  {
  for(int i = 0; i<10; i++) {
    sendIR(volumeDown.IRCode);
  }
}
