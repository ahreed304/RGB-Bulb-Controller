void setup() 
{
  //Initial setup for radio and serial connections
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1, pipeAddress[0]);
  radio.startListening();
}//-----end setup

void loop() 
{
  char payload[] = "0000.0000.0000"; //set max payload length
  
  if(radio.available(1)) //Listen for incoming payload from RF broadcast via RF24L01 transceiver 
  {
    radio.read(&payload, sizeof(payload)); //store received payload as char array

    transmitIRCommand(payload);  //If payload contains a command for this node, transmit the corresponing IR code to the RGB bulb via IR LED
    Serial.println(payload);
  }//-----end if
}//-----end loop
