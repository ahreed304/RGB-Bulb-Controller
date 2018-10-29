void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1, pipeAddress[0]);
  radio.startListening();
}

void loop() 
{
  if(radio.available(1)) 
  {
    radio.read(&payload, sizeof(payload));
    transmitIRCommand();
    Serial.println(payload);
  }
}