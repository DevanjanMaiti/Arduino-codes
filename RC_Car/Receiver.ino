int i, good, k;
byte data_in;
char rec;
void setup(){
  attachInterrupt(1,data_incoming,RISING);
  pinMode(3, INPUT);
  pinMode(1, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  


  Serial.begin(115200);
}//setup

void loop(){
  
  
}//loop






void data_incoming(){
    
    
    for(i=0; i<100; i++){
      delayMicroseconds(20);
      good=1;
      if(digitalRead(3)==LOW){
      good=0;
      i=100;
      }
    }//for
      
    if(good==1){
    detachInterrupt(1);
    while(1){
      if(digitalRead(3)==LOW){
        delayMicroseconds(750);

        for(i=0; i<8; i++){
          if(digitalRead(3)==HIGH)
          bitWrite(data_in, i, 1);
          else
          bitWrite(data_in, i, 0);
          delayMicroseconds(1000);
        }//for
        
        digitalWrite(1,HIGH);
 //digitalWrite(2,HIGH);
 //digitalWrite(7,HIGH);
 //digitalWrite(8,HIGH);
 
 
        rec = char(data_in);
        Serial.print(rec);
        if ((rec=='F')||(rec=='r')||(rec=='R')||(rec=='L')||(rec=='Q')||(rec=='E')||(rec=='Z')||(rec=='C'))
        {
          if(rec=='F')
          {
            goF();
          }
           if(rec=='r')
          {
            gor();
          }
           if(rec=='R')
          {
            goR();
          }
           if(rec=='L')
          {
            goL();
          }
           if(rec=='Q')
          {
            goQ();
          }
           if(rec=='E')
          {
            goE();
          }
           if(rec=='Z')
          {
            goZ();
          }
           if(rec=='C')
          {
            goC();
          }
          
        }
  	else if(rec == 'S')
	goS();
	
	
        
        Serial.println('a');

       break;//secondtwhile
      }//low kickoff
      
    }//second while
    
    }//good check

  attachInterrupt(1,data_incoming,RISING);
  
}
  
  void goF()
{
 digitalWrite(13,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
}
void gor()
{
  digitalWrite(13,LOW);
 digitalWrite(5,LOW);
 digitalWrite(9,LOW);
 digitalWrite(11,LOW);
 digitalWrite(4,HIGH);
 digitalWrite(6,HIGH);
 digitalWrite(10,HIGH);
 digitalWrite(12,HIGH);
}
void goR()
{
   digitalWrite(13,LOW);
 digitalWrite(5,HIGH);
 digitalWrite(9,LOW);
 digitalWrite(11,HIGH);
 digitalWrite(4,HIGH);
 digitalWrite(6,LOW);
 digitalWrite(10,HIGH);
 digitalWrite(12,LOW);
}
void goL()
{
  digitalWrite(13,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  

}
void goQ()
{
  digitalWrite(13,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  
}
void goE()
{
  digitalWrite(13,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
}
void goZ()
{
    digitalWrite(13,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
}
void goC()
{
    digitalWrite(13,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
}
void goS()
{
  digitalWrite(13,LOW);
 digitalWrite(5,LOW);
 digitalWrite(9,LOW);
 digitalWrite(11,LOW);
 digitalWrite(4,LOW);
 digitalWrite(6,LOW);
 digitalWrite(10,LOW);
 digitalWrite(12,LOW);
}
//routine

 /* digitalWrite(3,);
  digitalWrite(4,);
  digitalWrite(5,);
  digitalWrite(6,);
  digitalWrite(9,);
  digitalWrite(10,);
  digitalWrite(11,);
  digitalWrite(12,);*/
