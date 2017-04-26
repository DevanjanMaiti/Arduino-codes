#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(9, 8, 0);  // Clock pin, Data pin, Orientation

void setup() {

pinMode(A0,INPUT);
pinMode(2,OUTPUT);
bar.begin();
//Serial.begin(9600);
}

void loop() {

int slow_timer_count = 0;
int fast_timer_count = 0;

long slow_timer_threshold = 100000;
long fast_timer_threshold = 10000;

int ledbar_output;

while(1) {
int moisture_level = analogRead(A0);

//Serial.println(moisture_level);
//Serial.println(ledbar_output);

if (slow_timer_count == slow_timer_threshold){
  slow_timer_count = 0;
}
else {
  slow_timer_count++;
}

if (moisture_level>=0 && moisture_level<100) // Maximum Moisture
{
    ledbar_output=0x3ff;
    bar.setBits(ledbar_output);
}
else if (moisture_level>=100 && moisture_level<200)
{
    ledbar_output=0x1ff;
    bar.setBits(ledbar_output);
}
else if (moisture_level>=200 && moisture_level<300)
{
    ledbar_output=0x0ff;
    bar.setBits(ledbar_output);
}
else if (moisture_level>=300 && moisture_level<400)
{
    ledbar_output=0x07f;
    bar.setBits(ledbar_output);
}
else if (moisture_level>=400 && moisture_level<500)
{
    ledbar_output=0x03f;
    bar.setBits(ledbar_output);
}
else if (moisture_level>=500 && moisture_level<600)
{
    ledbar_output=0x01f;
    bar.setBits(ledbar_output);
}
else if (moisture_level>=600 && moisture_level<700)
{
    ledbar_output=0x00f;
    bar.setBits(ledbar_output);
}
else if (moisture_level>=700 && moisture_level<800)
{
    ledbar_output=0x007;
    bar.setBits(ledbar_output);
    if (slow_timer_count == slow_timer_threshold)
    {
    buzzer_slow();
    }
}
else if (moisture_level>=800 && moisture_level<900)
{
    ledbar_output=0x003;
    bar.setBits(ledbar_output);
    if (fast_timer_count == fast_timer_threshold)
    {
    buzzer_fast();
    }
}
else if (moisture_level>=900 && moisture_level<=1023)
{
    ledbar_output=0x001;
    bar.setBits(ledbar_output);
    if (fast_timer_count == fast_timer_threshold)
    {
    buzzer_fast();
    }
}

//Serial.println(ledbar_output);
delay(100);
}
} // End of Loop

void buzzer_slow() {
  int buzz_count;

for(buzz_count=0;buzz_count<3;buzz_count++) {
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);
  }  
}

void buzzer_fast() {
int buzz_count;

for(buzz_count=0;buzz_count<8;buzz_count++) {
  digitalWrite(2,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  delay(100);
  }
}
