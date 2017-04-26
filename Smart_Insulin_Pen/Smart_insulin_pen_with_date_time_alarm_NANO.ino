/**************************************************************************************************
  Filename:       Smart_insulin_pen_with_date_time_alarm_NANO.ino
  Author:         Devanjan Maiti
  Date:           17-09-2014 (23:42 HRS)

  Description:    This file contains the program to run the 
                  smart insulin pen application.

  Copyright 2014  Wisense Incorporated. All rights reserved.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  WISENSE OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Wisense Incorporated at www.wisense.in.
**************************************************************************************************/

float voltage; // analog voltage read from the potentiometer on pin A0
int temp=0; // temporary variable to store the previous dosage, used for comparison
int dose=0; // dose calculated based on the analog voltage read from the pot
int count=0; // used to maintain a minimum time before which the non-zero dosage is not considered to be set by the user (the user might be setting the dosage and hence randomly changing the analog voltage)
int flag=0; // it is set when a stable non-zero dosage is read (count reached)
int taken=0; // it is set when a dosage is injected once
double count2=0; // used to count whether the minimum time before which a second dosage can be taken is reached or not
double thresh=50; // sets the time before which a second dosage is allowed

#include <Time.h> // for time-keeping

void setup()
{
  pinMode(A0,INPUT); // analog voltages from pot
  pinMode(6,OUTPUT); // +ve lead for buzzer
  pinMode(7,OUTPUT); // -ve lead for buzzer
  pinMode(2,OUTPUT); // Vcc, required for Nano-Slide Pot Double Side
  pinMode(3,OUTPUT); // GND, required for Nano-Slide Pot Single Side
  Serial.begin(9600);
  setTime(11,55,0,27,9,14); // set the initial time
}

void loop()
{   
    digitalWrite(2,HIGH); // Always Vcc
    digitalWrite(3,LOW); // Always GND
    temp=dose; // store previous value of dosage in temp variable
    voltage=analogRead(A0); // read analog voltage from pot
    voltage=voltage*5/1023; // bring the discrete integer value of voltage to the range of 0-5 V
    dose=voltage_to_dosage(voltage); // call the function to convert the voltage to a particular dose based on a look-up table saved in the function
    if(dose!=0 && dose==temp) // check for a non-zero stable dosage value being set by the user
  {
      count++;
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
  
  while (flag==1) // when user is already at a stable dosage value
  {
    voltage=analogRead(A0); // read value again
    voltage=voltage*5/1023;
    dose=voltage_to_dosage(voltage);
    
    if(dose>temp) // if the user rotates the knob again to increase the dosage
    {
      flag=0;
      break;
    }
    
    else if(dose<temp) // if the user decreases the dosage
    {
      delay(300);
      voltage=analogRead(A0); // read again
      voltage=voltage*5/1023;
      dose=voltage_to_dosage(voltage);
    
      if(dose==0) // if the user has pressed the knob to inject the insulin 
      {
        taken=1; // dosage is taken
        flag=0;
        Serial.print("Dosage: "); // send dosage, time and date information to the mobile application
        Serial.print(temp);
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
  
  if(taken==1) // if dosage is taken once
 {
   while(count2<=thresh) // till the pre-defined time is not elapsed
   {
      voltage=analogRead(A0); // read again
      voltage=voltage*5/1023;
      dose=voltage_to_dosage(voltage);
      
      if(dose!=0) // if the user is trying to use the pen again (detected by sensing a non-zero dosage input coming from the knob)
      {
        digitalWrite(6,HIGH); // buzzer 'ON'
        digitalWrite(7,LOW);
        delay(100);
        digitalWrite(6,LOW); // buzzer 'OFF' to make the buzzer beep
        digitalWrite(7,LOW);
        delay(100);
      }
      else
      {
        digitalWrite(6,LOW); // buzzer 'OFF'
        digitalWrite(7,LOW);
        delay(100);
      }
        
      count2++; // increment the counter
   }
     taken=0;
     count2=0;
 }
}


int voltage_to_dosage(float vol) // function to convert the input voltage to an equivalent dosage
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
  
  void digitalClockDisplay() // function to display date and time
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
