void setup() {
// Initial Setup:
// LDR Input
  pinMode(A0,INPUT);

// Front PIR Sensor Input (only)
  pinMode(2,INPUT);

// Bypass Switch Input 
  pinMode(7,INPUT);

// Relay Control Output
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
}

void loop() {
// Main code:
  if(digitalRead(7)) {
    if(digitalRead(2)) {  // || digitalRead(Back_Pir_in)
      if(analogRead(A0) < 90) {
        digitalWrite(12,HIGH);
        delay(180000);
        while(digitalRead(2)); // || digitalRead(Back_Pir_in)
      }
    }
    else
    {
      digitalWrite(12,LOW);
    }
  }
  else {
    digitalWrite(12,HIGH);
  }     
}
