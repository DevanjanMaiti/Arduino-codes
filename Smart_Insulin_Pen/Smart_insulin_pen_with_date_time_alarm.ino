/***********************************************************************************************
 *
 * File Name: Smart_insulin_pen_with_date_time_alarm.ino
 * Author: Devanjan Maiti (devanjan008@gmail.com)
 * Created: Sep/18/2014
 *
 *
 * Copyright (c) <2014>, <Devanjan Maiti>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the names of its contributors
 *     may be used to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 **********************************************************************************************/

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
  Serial.begin(9600);
  setTime(12,0,0,15,9,14); // set the initial time
}

void loop()
{   
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
