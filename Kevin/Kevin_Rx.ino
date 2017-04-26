int i, good, k;
byte data_in;
void setup(){
  attachInterrupt(1,data_incoming,RISING);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
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
        if(data_in=='#')
        Serial.println("");
        else
        Serial.print(char(data_in));

       break;//secondtwhile
      }//low kickoff
      
    }//second while
    
    }//good check

  attachInterrupt(1,data_incoming,RISING);
  
  
  
}//routine
