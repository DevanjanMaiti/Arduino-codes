int a;
unsigned int i;
boolean flag=true;
#include <SoftwareSerial.h>
#include <TinyGPS.h>
int j;
int timesTosend=1;
int count;
char phone_no[]="07406849484";
float lat;
float lon;
char payload[100];

TinyGPS gps;
SoftwareSerial ss(4, 3); //4 is Tx, 3 is Rx on GPS module

static void smartdelay(unsigned long ms);

void setup() {
  //Serial.begin (9600);
 Serial.begin (115200);
 ss.begin(9600);
 Serial.println("AT+CMGF=1");
  delay(200);
  pinMode(A0,INPUT);
  pinMode(8,OUTPUT);//buzzer high
  pinMode(9,OUTPUT);
  //swit 12
  pinMode(12,INPUT);
  //11 high
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  //pinMode(A1,INPUT);
  
}

void loop() 
{
  i=0;
 digitalWrite(11,HIGH);
 digitalWrite(10,HIGH);
 digitalWrite(9,LOW);
 
a=analogRead(A0);
a=a-310;
if (flag)
Serial.println(a);

if (a<-50)
flag= false;

//buzzer
while(!flag)
{ i++;
  digitalWrite(8,HIGH);
  delay(500);
  digitalWrite(8,LOW);
  delay(500);
  if (digitalRead(12))// switch
  flag = true;
  if (i==15)
  {
    digitalWrite(8,LOW);
    delay(50);
    flag=true;
    trigger_alarm();
  //func
  }
}}

void trigger_alarm()
{
  float flat, flon;
  unsigned long age=0;
 
 for(j=0;j<3;j++) // for stabilising the gps values
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
