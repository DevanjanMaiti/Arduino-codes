int value; // For the digital input from the switch
void setup()
{
  pinMode(7,INPUT); // Switch input
  pinMode(6,OUTPUT); // Output to the buzzer
  pinMode(12,OUTPUT); // Output to the LED indicator (extra)
  Serial.begin(9600); // Initialising the serial monitor
}
void loop()
{
  value=digitalRead(7);
 Serial.println(value); // Printing the input values on the serial monitor
 if(value==0) // When water is filled
 {
   digitalWrite(6,HIGH); // Setting the buzzer ON
   digitalWrite(12,HIGH); // Setting the LED ON
 }
 else // Not necessary but this avoids False Positives
 {
   digitalWrite(6,LOW); // Setting the buzzer OFF
   digitalWrite(12,LOW); // Setting the LED OFF
 } 
 delay(1000);
}
