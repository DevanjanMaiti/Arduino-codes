#include <Servo.h>
Servo myservo;
void setup()
{
 pinMode(2 , INPUT);
 pinMode(3 , INPUT);
 pinMode(4 , INPUT);
 pinMode(5 , INPUT);
 pinMode(6 , OUTPUT);
 pinMode(7 , OUTPUT);
 pinMode(8 , OUTPUT);
 pinMode(9 , OUTPUT);
 pinMode(10 , OUTPUT);
 pinMode(11 , OUTPUT);
 myservo.attach(12);
 //pinMode(12 , OUTPUT);
 //pinMode(13 , OUTPUT);
}
void loop()
{
 
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  int pos;
 if(pos!=0)
   {
    while(pos!=0)
    {
     if(pos>0)
      pos--;
     else
      pos++;
    }
   } 
 if(digitalRead(2)==LOW && digitalRead(3)==HIGH && digitalRead(4)==HIGH && digitalRead(5)==LOW)
 {
   digitalWrite(6,HIGH);
   digitalWrite(7,LOW);
   digitalWrite(8,HIGH);
   digitalWrite(9,LOW);
   
 }
 else if(digitalRead(2)==LOW && digitalRead(3)==LOW && digitalRead(4)==HIGH && digitalRead(5)==LOW)
 {
   
   digitalWrite(6,HIGH);
   digitalWrite(7,LOW);
   digitalWrite(8,HIGH);
   digitalWrite(9,LOW);
   for(pos=0;pos<=60;pos++)
   {                                  
    myservo.write(pos);      
   } 
 }
  else if(digitalRead(2)==LOW && digitalRead(3)==HIGH && digitalRead(4)==LOW && digitalRead(5)==LOW)
 {
   digitalWrite(6,HIGH);
   digitalWrite(7,LOW);
   digitalWrite(8,HIGH);
   digitalWrite(9,LOW);
   for(pos=0;pos>=-60;pos--)
   {                                  
    myservo.write(pos);             
   } 
   
 }
 else if(digitalRead(2)==LOW && digitalRead(3)==LOW&& digitalRead(4)==LOW && digitalRead(5)==HIGH)
 {
   digitalWrite(6,LOW);
   digitalWrite(7,HIGH);
   digitalWrite(8,LOW);
   digitalWrite(9,HIGH);
 }
  else if(digitalRead(2)==HIGH && digitalRead(3)==LOW && digitalRead(4)==HIGH && digitalRead(5)==LOW)
  {
    digitalWrite(6,LOW);
   digitalWrite(7,LOW);
   digitalWrite(8,LOW);
   digitalWrite(9,LOW);
  }
}
