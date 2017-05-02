/*******************************************************************************
  Filename:       DTXGA1701_Garden_Automation.h
  
  Author:         Devanjan Maiti
  Date:           17-04-2017

  Description:    Header File for DTXGA1701_Garden_Automation Application.

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
#ifndef DTXGA1701_Garden_Automation_h
#define DTXGA1701_Garden_Automation_h
#endif

#define LED_BAR

#ifdef LED_BAR
#include <Grove_LED_Bar.h>
Grove_LED_Bar bar(9, 8, 0);  // Clock pin, Data pin, Orientation
#endif

// PIN DEFINITIONS
const uint8_t moisture_level_pin = 0; // ANALOG
const uint8_t pump_on_pin        = 12; 
const uint8_t buzzer_pin         = 2;
const uint8_t pump_error_led     = 10;

// GLOBAL VARIABLES
unsigned int moisture_level;
unsigned int ledbar_output;

// CONSTANTS
const int moisture_threshold = 700; // UPPER SOIL MOISTURE THRESHOLD
const int moisture_okay      = 400; // LOWER SOIL MOISTURE THRESHOLD


