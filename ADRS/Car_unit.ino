/***********************************************************************************************
 *
 * File Name: Accident_Detection_&_Rescue_System_(ADRS)_Vehicle_Unit.ino
 * Author: Devanjan Maiti (devanjan008@gmail.com)
 * Created: Oct/5/2014
 *
 *
 * Copyright (c) <2014>, <Devanjan Maiti>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the names of its contributors
 *     may be used to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 **********************************************************************************************/
/*-----------------------------------------------------------------------------

PIN DETAILS (Arduino Uno):

D0: GSM MODULE Tx
D1: GSM MODULE Rx
D3: GPS MODULE Rx
D4: GPS MODULE Tx
D8: LED/BUZZER +VE
D9: LED/BUZZER -VE
D10: HIGH (ACCELEROMETER-1 +5V)
D11: HIGH (SWITCH INPUT)
D12: SWITCH OUTPUT TO ARDUINO & RESISTOR ONE END
SINGLE GND: ACCELEROMETER GND & RESISTOR OTHER END
+5V: GPS MODULE +5V
ADJ. GND: GPS & GSM MODULE GND
A0: ACCELEROMETER-1 OUTPUT

-----------------------------------------------------------------------------*/

int a;
unsigned int i;
boolean flag=true;
#include <SoftwareSerial.h>
#include <TinyGPS.h>
int j;
int timesTosend=1;
int count;
char phone_no[]="07406849484";
char vehicle_reg_no[]="KA 19 P 8488";
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
        Serial.print(vehicle_reg_no);
        Serial.print(" has met with an accident at the location: ");
        Serial.print(lat);
        Serial.print(",");
        Serial.println(lon);
        Serial.print(" The nearest ambulance service has already been alerted by the ADRS.");
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
