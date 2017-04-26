float voltage;
int temp=0;
int dose=0;
int count=0;
int flag=0;
int temp2=0;
int taken=0;

#include <Time.h>

void setup()
{
  pinMode(A0,INPUT);
  Serial.begin(9600);
  setTime(14,20,0,14,9,14);
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
      if(count>=3000)
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
        Serial.print("Dosage: ");
        Serial.print(temp2);
        digitalClockDisplay();
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
  
  void digitalClockDisplay()
  {
  Serial.print(" Date: ");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(year());
  // digital clock display of the time
  Serial.print(" Time: ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();  
}

void printDigits(int digits)
{
  // utility function for clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
