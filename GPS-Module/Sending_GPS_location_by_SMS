#include <SoftwareSerial.h>
#include <TinyGPS.h>
int i;
int timesTosend=1;
int count;
char phone_no[]="07406849484";
float lat;
float lon;
char payload[100];

TinyGPS gps;
SoftwareSerial ss(4, 3); //4 is Tx, 3 is Rx on GPS module

static void smartdelay(unsigned long ms);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println("AT+CMGF=1");
  delay(200);
}

void loop()
{
  float flat, flon;
  unsigned long age=0;
 
 for(i=0;i<3;i++) // for stabilising the gps values
 {
  gps.f_get_position(&flat, &flon, &age);
  lat=flat;
  lon=flon;
  smartdelay(1000);
 } 
  send_sms();
}
 void send_sms()
 {
  while(count<timesTosend)
  {
    delay(1500);
    Serial.print("AT+CMGS=\"");
    Serial.print(phone_no);
    Serial.println("\"");
    while(Serial.read()!='>');
    {
        Serial.print(lat);
        Serial.print(",");
        Serial.println(lon);
        delay(500);
        Serial.write(0x1A);
        Serial.write(0x0D);
        Serial.write(0x0A);
        delay(5000);
    }
   count++;
  } 
  while(1);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
