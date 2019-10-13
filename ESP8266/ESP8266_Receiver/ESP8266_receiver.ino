
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>


const char* ssid     = "Bikini Bottom WiFi";      // SSID of local network
const char* password = "motowNshufflE";   // Password on network
 
int ledPin = LED_BUILTIN;
WiFiServer server(80);
IRsend irsend(5); 


//The following arrays match each possible char in a payload to a specific command and a corresponding IR code. 
//array value =             0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16        17        18        19                20                21              22              23              24              25
const long IRCodes[] =     {0xFF52AD, 0xFF6897, 0xFF30CF, 0xFF38C7, 0xFF4AB5, 0xFF9867, 0xFF18E7, 0xFF5AA5, 0xFFB04F, 0xFF7A85, 0xFF10EF, 0xFF42BD, NULL,     NULL,     NULL,     0xFFA25D, 0xFFE21D, 0xFFA857, 0xFF906F, 0xFF22DD,         0xFFE01F,         0xFF629D,       NULL,           NULL,           NULL,           NULL};
//command =                 WHITE     RED       ORANGE    GOLD      YELLOW    GREEN     TURQUOISE CYAN      BLUE      PURPLE    MAGENTA   PINK      NULL      NULL      NULL      ON        OFF       BRIGHTER  DIMMER    FLASH (LAVENDER)  SMOOTH (CRIMSON)  SPEED (INDIGO)  BRIGHTNESS 25%  BRIGHTNESS 50%  BRIGHTNESS 75%  BRIGHTNESS 100%


//StaticJsonBuffer<200> jsonBuffer;
char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}"; 

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 200); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(1, 1, 1, 1);  //DNS


//const char* deviceName = "austino.com";
  

class IRCommand {
  public:
    long IRCode;
    char Command[20];
    IRCommand(long iRCode,char command[20]) {
      IRCode = iRCode;
      for(int i = 0; i<sizeof command; i++) {
        Command[i] = command [i];
      }    
    }
};

//IRCommand iRCommand;
IRCommand powerOn(0xFFA25D, "powerOn");
IRCommand powerOff(0xFFE21D, "powerOff");



//
//
//class PowerOn {
//  public:
//    long IRCode = 0xFFA25D;
//    char comnmand[] = "on";
//};
//
//
// 
//class PowerOff {
//  public:
//    long IRCode = 0xFFE21D;
//    char comnmand[] = "off";
//};


//sprintf(IRCode, "asdf");

//   char buffer[30];
//   sprintf(buffer, "name=pin%d&value=%d", pinNumber, value);
 
void setup() {

//  char IRCode[20];
//for(int i = 0; i<sizeof(IRCode); i++) {
//  IRCode[i] = 'A';
//}
//  IRCode = "asdf";

  Serial.begin(9600);
  delay(10);
  irsend.begin();
  
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

//  WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, subnet, gateway, dns);
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

//  IROn iROn;
//  IROff iROff;
//  
//  IRCommand powerOn = new IRCommand();
//  powerOn.IRCode = 0xFFA25D;
//  powerOn.command = "powerOn";
//  
//  
//  IRCommand powerOff = new IRCommand();
//  powerOff.IRCode = 0xFFE21D;
//  powerOff.command = "powerOff";

Serial.println(powerOn.Command);
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
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, LOW);
    irsend.sendNEC(powerOn.IRCode, 32);
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, HIGH);
    irsend.sendNEC(powerOff.IRCode, 32);
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println(""); //  do not forget this one
//  client.println("<!DOCTYPE HTML>");
  client.println(json);
 
//  client.print("Led pin is now: ");
 
  if(value == HIGH) {
//    client.print("On");  
  } else {
//    client.print("Off");
  }
//  client.println("<br><br>");
//  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 5 ON<br>");
//  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 5 OFF<br>");
//  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
