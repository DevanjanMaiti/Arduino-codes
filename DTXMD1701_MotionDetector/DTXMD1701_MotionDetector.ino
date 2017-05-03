/*******************************************************************************
  Filename:       DTXMD1701_MotionDetector.ino
  
  Author:         Devanjan Maiti
  Date:           03-05-2017
  Description:    This file contains the program for the DTXMD1701 Motion Sensing
                  Module that can be used to automatically control lights and other
                  appliances. 
                  NOTE: On-chip Watchdog Timer can be enabled in this application.
                  NOTE: The module can be configured to use one or two PIR Motion
                        Sensors along with the Ambient Light Sensor.
                  NOTE: It can be configured to set the ambient light threshold
                        from an on-board potentiometer. 
                                   
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
#include "DTXMD1701_MotionDetector.h"

// SETUP FUNCTION ----------------------------------------------------------
void setup() {

// PIN DIRECTIONS
  pinMode(pir_snsr1_pin,INPUT);
  pinMode(pir_snsr2_pin,INPUT);
  pinMode(ctrl_bypass_pin,INPUT);
  pinMode(relay_ctrl_pin,OUTPUT);
  pinMode(led_ctrl_pin,OUTPUT);

#ifdef WATCHDOG_EN
  watchdogSetup();
#endif

  led_blink(); // CHIP RESET INDICATION
  
} //-------------------------------------------------------------------------

// LOOP FUNCTION ------------------------------------------------------------
void loop() {
  
  wdt_reset();  // RESET WATCHDOG TIMER

  ldr_adc_thresh_val = light_threshold_val();
  
  if(digitalRead(ctrl_bypass_pin)) {
    if(digitalRead(pir_snsr1_pin) || digitalRead(pir_snsr2_pin)) {   
      if(analogRead(ldr_snsr_pin) < ldr_adc_thresh_val) {
        digitalWrite(relay_ctrl_pin,HIGH);
        delay(on_timer_interval);
        while(digitalRead(pir_snsr1_pin) || digitalRead(pir_snsr2_pin));
      }
    }
    else
    {
      digitalWrite(relay_ctrl_pin,LOW);
    }
  }
  else {
    digitalWrite(relay_ctrl_pin,HIGH);
  } 
} //-------------------------------------------------------------------------

#ifdef WATCHDOG_EN
// WATCHDOG TIMER SETUP FUNCTION --------------------------------------------
void watchdogSetup(void) { 
  
// REF: https://forum.arduino.cc/index.php?topic=63651.0
  wdt_reset();  // RESET WATCHDOG TIMER TO AVOID RESET DURING WDT CONFIGURATION
   
  WDTCSR |= (1<<WDCE) | (1<<WDE);  // ENTER WATCHDOG CONFIGURATION MODE
  WDTCSR  = (1<<WDE) | (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0);  // SET TIMEOUT VALUE TO 8 SECS
} //--------------------------------------------------------------------------
#endif

// AMBIENT LIGHT SENSOR THRESHOLD FUNCTION -----------------------------------
unsigned int light_threshold_val(void) {

  unsigned int ldr_adc_thresh_value = 0;
  
#ifdef EXT_LIGHT_THRESH_CTRL
  uint8_t count;

  for(count = 0; count < 5; count++) {  // AVERAGING 5 ADC READS
  ldr_adc_thresh_value += analogRead(ldr_pot_pin);  // READ ADC VALUE
  delay(500);  // MINIMUM 100 msecs BETWEEN ADC READS
  }

  ldr_adc_thresh_value = uint8_t(ldr_adc_thresh_value/5);
#else
  ldr_adc_thresh_value = ldr_adc_thresh_val_fixed;
#endif

  return ldr_adc_thresh_value;
} //--------------------------------------------------------------------------

// LED BLINK FUNCTION --------------------------------------------------------
void led_blink() {

  digitalWrite(led_ctrl_pin,HIGH);
  delay(500);
  digitalWrite(led_ctrl_pin,LOW);
  delay(500);
  digitalWrite(led_ctrl_pin,HIGH);
  delay(500);
  digitalWrite(led_ctrl_pin,LOW);
  delay(500);
  digitalWrite(led_ctrl_pin,HIGH);
  delay(500);
  digitalWrite(led_ctrl_pin,LOW);
  
} //--------------------------------------------------------------------------

// END OF CODE ---------------------------------------------------------------
