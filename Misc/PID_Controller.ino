int sen1=8;//left sensor
int sen2=4;//middle sensor
int sen3=3;//right sensor
int mot11=6;//left sensor one end
int mot12=9;//left sensor other end
int mot21=10;//right sensor one end
int mot22=11;//right sensor other end
int en1=12;//for motor driver
void setup()
{
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  pinMode(sen3,INPUT);
  pinMode(en1,OUTPUT);//motor driver enable for both the enable a single pin is used
  pinMode(mot11,OUTPUT);
  pinMode(mot12,OUTPUT);
  pinMode(mot21,OUTPUT);
  pinMode(mot22,OUTPUT);
  pinMode(7,OUTPUT);//this is for sensor  vcc and sensor ground is connected to the arduino
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(7,HIGH);
  int intgrl=0,cor,err,p_err=0,kp=12,kd=0.4,ki=0,s1,s2,s3,n_cor;
  s1=digitalRead(sen1);
  s2=digitalRead(sen2);
  s3=digitalRead(sen3);
  digitalWrite(en1,HIGH);
  err=s1*3+s2*0-s3*3;//instantaneous error
  intgrl=intgrl+err;//for Ki cummulative error
  cor=kp*err+ki*intgrl+kd*(err-p_err);//correction main algorithm
  p_err=err;
  n_cor=-cor;
Serial.println("Correction =");
Serial.print(cor);
  Serial.println("Integral=");
  Serial.print(intgrl);
  delay(1000);  
  
 if(cor==0)
  {
    analogWrite(mot12,90);   analogWrite(mot22,100);
  digitalWrite(mot21,0);
    digitalWrite(mot11,0);
  }
  else if(cor<0)
 {
  analogWrite(mot11,90-cor);
  digitalWrite(mot12,0);digitalWrite(mot22,70+cor);
  digitalWrite(mot21,0); }
 else if(cor>0)
 {
  analogWrite(mot12,80+cor);
  digitalWrite(mot11,0);
  digitalWrite(mot22,0);
  analogWrite(mot21,80-cor);
 }
}
