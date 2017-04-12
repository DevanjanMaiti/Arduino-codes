#define LDR_in A0
//#define Front_PIR_in 2
#define Back_PIR_in 3  // UNUSED
#define Bypass_Switch_in 7
#define Relay_ctrl_out 13

#define LDR_Threshold 90
#define ON_Time 120000

void setup() {
// Initial Setup:
// LDR Input
  pinMode(LDR_in,INPUT);

// Front PIR Sensor Input (only)
  pinMode(2,INPUT);

// Bypass Switch Input 
  pinMode(Bypass_Switch_in,INPUT);

// Relay Control Output
  pinMode(Relay_ctrl_out,OUTPUT);
  digitalWrite(Relay_ctrl_out,LOW);
Serial.begin(9600);
}

void loop() {
// Main code:
Serial.println(digitalRead(2));
//  if(digitalRead(Bypass_Switch_in)) {
    if(digitalRead(2)) {  // || digitalRead(Back_Pir_in)
      if(analogRead(LDR_in) < LDR_Threshold) {
          digitalWrite(Relay_ctrl_out,HIGH);
          delay(ON_Time);
          while(digitalRead(2)); // || digitalRead(Back_Pir_in)
      }
    }
    else
    {
      digitalWrite(Relay_ctrl_out,LOW);
    }
//  }
//  else {
//  digitalWrite(Relay_ctrl_out,HIGH);
//  }
delay(100);
}
