char input; // value read from the Bluetooth modem via the serial Rx pin of Arduino

void setup()
{
  pinMode(6,OUTPUT); // Relay +ve input
  pinMode(7,OUTPUT); // Relay -ve input
  Serial.begin(9600);
}

void loop()
{
  input=Serial.read(); // reading input value from Bluetooth modem
  Serial.println(input);

  if(input =='a') // to be set in the mobile application accordingly
  { 
    digitalWrite(6,HIGH); // turn device ON
    digitalWrite(7,LOW); 
  }
  
  else if(input =='d') // to be set in the mobile application accordingly
  {
    digitalWrite(6,LOW); // turn device OFF
    digitalWrite(7,LOW);
  }    
}
