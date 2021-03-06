float voltage;
int temp=0;
int dose=0;
int count=0;
int flag=0;
int temp2=0;
int taken=0;

void setup()
{
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop()
{
    temp=dose;
    voltage=analogRead(A0);
    voltage=voltage*5/1023;
    dose=voltage_to_dosage(voltage); 
    
    if(dose!=0 && dose==temp)
  {
      count++;
      temp2=temp;
      if(count>=300)
      {
        flag=1; // stopped at some particular non-zero value (dosage) 
      }
      else
      {
        flag=0;
      }  
  }
  else
  {
      count=0;
  }
  
  while (flag==1)
  {
    voltage=analogRead(A0);
    voltage=voltage*5/1023;
    dose=voltage_to_dosage(voltage);
    
    if(dose>temp2)
    {
      flag=0;
      break;
    }
    
    else if(dose<temp2)
    {
      delay(300);
      voltage=analogRead(A0);
      voltage=voltage*5/1023;
      dose=voltage_to_dosage(voltage);
    
      if(dose==0)
      {
        taken=1;
        flag=0;
        Serial.println(temp2);
        break;
      }
      else
      {
        taken=0;
        break;
      }
    }
  }
 
}


int voltage_to_dosage(float vol)
  {
    int dosage;
    
    if (vol>=0.00 && vol<0.45)
    dosage=15 ;
    else if (vol>0.46 && vol<1.35)
    dosage=12 ;
    else if (vol>1.36 && vol<2.25)
    dosage=9 ;
    else if (vol>2.26 && vol<3.15)
    dosage=6 ;
    else if (vol>3.16 && vol<4.05)
    dosage=3 ;
    else if (vol>4.06 && vol<=5.00)
    dosage=0 ;
    
    return dosage;
  }
