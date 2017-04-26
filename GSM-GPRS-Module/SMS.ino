int timesTosend=1;
int count;
char phone_no[]="07406849484";
void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("AT+CMGF=1");
  delay(200);
}

void loop()
{
  while(count<timesTosend)
  {
    delay(1500);
    Serial.print("AT+CMGS=\"");
    Serial.print(phone_no);
    Serial.println("\"");
    while(Serial.read()!='>');
    {
      Serial.print("Location");
      delay(500);
      Serial.write(0x1A);
      Serial.write(0x0D);
      Serial.write(0x0A);
      delay(5000);
    }
    count++;
  }
}
