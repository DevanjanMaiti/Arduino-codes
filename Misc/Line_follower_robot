int sen1=2;//left sensor
int sen2=3;//middle sensor
int sen3=4;//right sensor
int mot11=5;//left motor one end all pwm
int mot12=6;//left motor other end
int mot21=9;//right motor one end
int mot22=10;//right motor other end
int en=7;//for motor driver
/*int cx=0;
int cy=0;
int x=0;
int y=0;
*/
void setup()
{
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  pinMode(sen3,INPUT);
  pinMode(mot11,OUTPUT);
  pinMode(mot12,OUTPUT);
  pinMode(mot21,OUTPUT);
  pinMode(mot22,OUTPUT);
  pinMode(en,OUTPUT);
  Serial.begin(9600);
  /*pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
*/
}

void loop()
{ //digitalWrite(A0,LOW);
  //digitalWrite(A1,LOW);
  //digitalWrite(A2,LOW);
  
  
  digitalWrite(en,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  Serial.print(digitalRead(sen1));
  if(digitalRead(sen1) == 1 )
  goleft();
  
  if(digitalRead(sen3) == 1 )
  goright();
  
  //Serial.print('a');
  
}


void goleft()
{ Serial.println('L');
  digitalWrite(mot11,LOW);
  digitalWrite(mot12,HIGH);
  digitalWrite(mot22,LOW);
  digitalWrite(mot21,HIGH);
  
}

void goright()
{ Serial.println('R');
  digitalWrite(mot11,HIGH);
  digitalWrite(mot12,LOW);
  digitalWrite(mot22,HIGH);
  digitalWrite(mot21,LOW);
}



