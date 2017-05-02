/*******************************************************************************
  Filename:       DTXGA1701_Garden_Automation.ino
  
  Author:         Devanjan Maiti
  Date:           17-04-2017

  Description:    This file contains the program to run the  application
                  for automatic watering of plants using soil moisture 
                  sensor and 6V DC pump.

 The MIT License (MIT)

  Copyright (c) 2017 Devanjan Maiti (devanjan008@gmail.com)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

  Should you have any questions regarding your right to use this Software,
  contact Devanjan Maiti at devanjan008@gmail.com.
  
********************************************************************************/
#include "DTXGA1701_Garden_Automation.h"

// SETUP ---------------------------------------
void setup() {

// PIN DIRECTIONS
pinMode(pump_on_pin,OUTPUT);
pinMode(buzzer_pin,OUTPUT);
pinMode(pump_error_led,OUTPUT);

#ifdef LED_BAR
bar.begin();
#endif
} //---------------------------------------------

// LOOP -----------------------------------------
void loop() {

  long timeout_counter = 0;
  long timeout_count   = 100000;
  
  moisture_level = analogRead(moisture_level_pin); // READ ADC

#ifdef LED_BAR
  led_bar(moisture_level);
#endif    
  
  if(moisture_level > moisture_threshold) {
  
    while (moisture_level > moisture_okay) {

#ifdef LED_BAR
      moisture_level = analogRead(moisture_level_pin); // READ ADC
      led_bar(moisture_level);
#endif 

      digitalWrite(pump_on_pin,HIGH); //PUMP ON
      timeout_counter++;
      delay(10*1000); // Check moisture level every 10 seconds
  
      if(timeout_counter > timeout_count) {
        pump_error();
      }
    }

    timeout_counter = 0; // RESET COUNTER
    digitalWrite(pump_on_pin,LOW); //PUMP OFF
  }
} // END OF LOOP ---------------------------------

#ifdef LED_BAR
// LED BAR FUNCTION -------------------------------
void led_bar(unsigned int moisture_level) {

  if (moisture_level>=0 && moisture_level<100) // MAX MOISTURE LEVEL
  {
    ledbar_output=0x3ff;
  }
  else if (moisture_level>=100 && moisture_level<200)
  {
    ledbar_output=0x1ff;
  }
  else if (moisture_level>=200 && moisture_level<300)
  {
    ledbar_output=0x0ff;
  }
  else if (moisture_level>=300 && moisture_level<400)
  {
    ledbar_output=0x07f;
  }
  else if (moisture_level>=400 && moisture_level<500)
  {
    ledbar_output=0x03f;
  }
  else if (moisture_level>=500 && moisture_level<600)
  {
    ledbar_output=0x01f;
  }
  else if (moisture_level>=600 && moisture_level<700)
  {
    ledbar_output=0x00f;
  }
  else if (moisture_level>=700 && moisture_level<800)
  {
    ledbar_output=0x007;
  }
  else if (moisture_level>=800 && moisture_level<900)
  {
    ledbar_output=0x003;
  }
  else if (moisture_level>=900 && moisture_level<=1023) // MIN MOISTURE LEVEL
  {
    ledbar_output=0x001;
  }

  bar.setBits(ledbar_output); // WRITE DATA TO LED BAR DRIVER IC
} //-----------------------------------------------
#endif

// FAST BUZZER FUNCTION --------------------------
void buzzer_fast() {

  int buzz_count;

  for(buzz_count=0;buzz_count<8;buzz_count++) {
   
    digitalWrite(buzzer_pin,HIGH);
    delay(100);
    digitalWrite(buzzer_pin,LOW);
    delay(100);
  }
} //-----------------------------------------------

// PUMP ERROR FUNCTION ----------------------------
void pump_error() {

  digitalWrite(pump_error_led,HIGH); // PUMP ERROR LED ON

  moisture_level = analogRead(moisture_level_pin); // READ ADC
  delay(100);                                      // ADC ACQUISITION TIME
  while(moisture_level > moisture_okay) {

 #ifdef LED_BAR
    moisture_level = analogRead(moisture_level_pin); // READ ADC
  delay(100);                                      // ADC ACQUISITION TIME
    led_bar(moisture_level);
#endif 

    buzzer_fast();
    delay(15*60*1000); // 15 Minute Interval
  }
  
  digitalWrite(pump_error_led,LOW); // PUMP ERROR LED OFF
} //----------------------------------------------

// END OF CODE ------------------------------------
