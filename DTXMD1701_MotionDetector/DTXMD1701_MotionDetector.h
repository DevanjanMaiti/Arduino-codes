/*******************************************************************************
  Filename:       DTXMD1701_MotionDetector.h
  
  Author:         Devanjan Maiti
  Date:           03-05-2017
  Description:    Header File for the DTXMD1701_MotionDetector Application.
                  
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
#ifndef DTXMD1701_MotionDetector_h
#define DTXMD1701_MotionDetector_h
#endif

#define WATCHDOG_EN            // ENABLE ON-CHIP WATCHDOG TIMER
#define DUAL_PIR_EN            // ENABLE 2ND PIR SENSOR
#define EXT_LIGHT_THRESH_CTRL  // ENABLE AMBIENT LIGHT THRESHOLD CONTROL

// PIN DEFINITIONS ---------------
const uint8_t ldr_snsr_pin     = 0; // ANALOG 0
const uint8_t ldr_pot_pin      = 1; // ANALOG 1
const uint8_t timer_pot_pin    = 2; // ANALOG 2
const uint8_t pir_snsr1_pin    = 3;
const uint8_t pir_snsr2_pin    = 4;
const uint8_t ctrl_bypass_pin  = 7;
const uint8_t relay_ctrl_pin   = 12;
const uint8_t led_ctrl_pin     = 13;

// VARIABLES --------------
unsigned int ldr_adc_rd_val;
unsigned int ldr_adc_thresh_val;
unsigned int pir_snsr1_rd_val;
unsigned int pir_snsr2_rd_val;

// CONSTANTS ------
const unsigned int ldr_adc_thresh_val_fixed = 80;         // ANALOG DATA VALUE COMPARISON THRESHOLD
const unsigned int on_timer_interval        = 3*60*1000;  // 3 SECS ON TIME

#ifdef WATCHDOG_EN  // WATCHDOG TIMER FUNCTIONALITY
#include <avr/wdt.h> 
#endif
