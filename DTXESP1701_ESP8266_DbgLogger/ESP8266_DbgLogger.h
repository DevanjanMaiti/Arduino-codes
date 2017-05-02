/*******************************************************************************
  Filename:       ESP8266_DbgLogger.h
  
  Author:         Devanjan Maiti
  Date:           02-05-2017
  Description:    Header File for the ESP8266_DbgLogger Application.
                  
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
#ifndef ESP8266_DbgLogger_h
#define ESP8266_DbgLogger_h
#endif

#define THINGSPEAK          // USE THINGSPEAK CLOUD
//#define MON_ANALOG          // ENABLE ANALOG CHANNEL MONITOR
//#define MON_DIGITAL_CH1     // ENABLE DIGITAL CHANNEL 1 MONITOR
#define MON_DIGITAL_CH2     // ENABLE DIGITAL CHANNEL 2 MONITOR
#define ANALOG_AVG_EN       // ENABLE AVERAGING FOR ADC DATA
#define LED_MON_EN          // ENABLE ON-BOARD DEBUG LED
#define EVENT_DRIVEN_MODE   // ENABLE EVENT DRIVEN DATA UPDATES
//#define ESP_LOW_PWR_MODE    // ENABLE LOW POWER MODE (USES CH_PD PIN ON ESP8266)

// PIN DEFINITIONS ---------------
const uint8_t dbg_anlg_pin     = 0;
const uint8_t dbg_dgtl_ch1_pin = 3;
const uint8_t dbg_dgtl_ch2_pin = 4;
const uint8_t mon_led_pin      = 13;
const uint8_t ch_pd_ctrl_pin   = 9;

// VARIABLES --------------
unsigned int rd_val_anlg;
unsigned int rd_val_dgtl_ch1;
unsigned int rd_val_dgtl_ch2;
String       getString_concat;

// CONSTANTS ------
const uint8_t anlg_ch_avg_count = 10;      // NUMBER OF SAMPLES TO AVERAGE IN "ANALOG_AVG_EN" MODE
const uint8_t adc_rd_thresh_val = 500;     // ANALOG DATA VALUE COMPARISON THRESHOLD
const int     push_interval     = 2*1000;  // 2 SECS

// STRING DEFINITIONS ------------------------
String getString_start = "GET /update?key=";
String getString_fval1 = "&field1=";
String getString_fval2 = "&field2=";
String getString_fval3 = "&field3=";

#ifdef THINGSPEAK
String Server_IP_addr = "184.106.153.149";
String API_key        = "RCG9Q2D4NO5KRRHF";
#endif

// FUNCTION TO PUSH PASSED STRING TO CLOUD PLATFORM OVER WIFI
void ESP_pushData() {
	
	
	
	
}
