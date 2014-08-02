int value;
int counter=0;
void setup()
{
  pinMode(A0,INPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  value=analogRead(A0); // Input from the vibration sensor
  Serial.println(value);
  if(value<100)
  {
    counter++;
  }
  else
  {
    counter--;
  }
  if(counter>=5)
  {
    digitalWrite(12,HIGH); // To the actuator: Buzzer,LED etc.
  }
  else
  {
    digitalWrite(12,LOW);
  } 
  delay(1000);
}
