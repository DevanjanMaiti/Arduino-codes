
void setup(){
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  //boolean test;
}

void loop(){
 boolean test = true;
  if (digitalRead(3) == HIGH)
   {test = false;
     if (digitalRead(5) == HIGH)
    {rf_send('Q');
     //break;
   }
    else if (digitalRead(6) == HIGH)
    {rf_send('E');
     //break;
   }
  else rf_send('F');
   }
  
  
  if (digitalRead(4) == HIGH)
  //rf_send('r');
   {test = false;
     if (digitalRead(5) == HIGH)
    {rf_send('Z');
     //break;
   }
    else if (digitalRead(6) == HIGH)
    {rf_send('C');
     //break;
     
   }
  else rf_send('r');
   }
  
  //if(button)
 // rf_send('S');
  
  if (test)
  {
  if (digitalRead(5) == HIGH)
  rf_send('L');
  
   if (digitalRead(6) == HIGH)
  rf_send('R');
  
  if (digitalRead(3) == LOW && digitalRead(4) == LOW)
  {if (digitalRead(5) == LOW && digitalRead(6) == LOW)
   rf_send('S');
   }
  }
  delay(100);
  //v++;
}

void rf_send(byte input){
  int i;
  
  for(i=0; i<20; i++){
  digitalWrite(2, HIGH);
  delayMicroseconds(500);
  digitalWrite(2, LOW);
  delayMicroseconds(500);
}

  digitalWrite(2, HIGH);
  delayMicroseconds(3000);
  digitalWrite(2, LOW);
  delayMicroseconds(500);
  
    
  for(i=0; i<8; i++){
  if(bitRead(input,i)==1)
  digitalWrite(2, HIGH);
  else
  digitalWrite(2, LOW);
  delayMicroseconds(500);
  
  if(bitRead(input,i)==1)
  digitalWrite(2, LOW);
  else
  digitalWrite(2, HIGH);
  delayMicroseconds(500);
}//i

  
  digitalWrite(2, LOW);
}




