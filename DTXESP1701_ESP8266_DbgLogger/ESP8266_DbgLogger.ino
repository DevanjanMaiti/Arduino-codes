/*******************************************************************************
  Filename:       ESP8266_DbgLogger.ino
  
  Author:         Devanjan Maiti
  Date:           26-04-2017
  Description:    This file contains the program to run on the DTXESP1701 Board.
                  The setup is designed to be able to simultaneously monitor up
                  to 1 Analog and 2 Digital Channels simultaneously and upload 
                  data at a desired interval to an online Data Analytics Platform
                  like ThingSpeak (https://thingspeak.com/).
                  NOTE: The ESP8266 Module is assumed to be configured in Mode 0/3
                        i.e. to support client mode and already configured to connect
                        to one of the available WLAN networks.
                  NOTE: The ThingSpeak Platform requires at least 15 seconds interval
                        between two consecutive updates.
                  NOTE: Change the jumper position on the board to be able to control
                        the CH_PD Pin on the ESP8266 Module.
                  
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
#define THINGSPEAK          // USE THINGSPEAK CLOUD
#define MON_ANALOG          // ENABLE ANALOG CHANNEL MONITOR
#define MON_DIGITAL_CH1     // ENABLE DIGITAL CHANNEL 1 MONITOR
#define MON_DIGITAL_CH2     // ENABLE DIGITAL CHANNEL 2 MONITOR
#define ANALOG_AVG_EN       // ENABLE AVERAGING FOR ADC DATA
#define LED_MON_EN          // ENABLE ON-BOARD DEBUG LED
#define EVENT_DRIVEN_MODE   // ENABLE EVENT DRIVEN DATA UPDATES
#define ESP_LOW_PWR_MODE    // ENABLE LOW POWER MODE (USES CH_PD PIN ON ESP8266)

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

// SETUP -------------------------------------
void setup() {

#ifdef MON_DIGITAL_CH1  
  pinMode(dbg_dgtl_ch1_pin,INPUT);
#endif

#ifdef MON_DIGITAL_CH2
  pinMode(dbg_dgtl_ch2_pin,INPUT);
#endif

#ifdef LED_MON_EN
  pinMode(mon_led_pin,OUTPUT);
#endif

#ifdef ESP_LOW_PWR_MODE
  pinMode(ch_pd_ctrl_pin,OUTPUT);
#endif

// SERIAL BAUD RATE CONFIGURATION
  Serial.begin(115200);
    
// INITIAL ESP8266 RESET
  Serial.println("AT+RST");
  
} //------------------------------------------

// LOOP ------------------------------------------------------------------
void loop() {

#ifdef ESP_LOW_PWR_MODE
// DISABLE ESP8266 LOW POWER MODE TO SEND PACKETS
  digitalWrite(ch_pd_ctrl_pin,HIGH);
#endif

// ANALOG CHANNEL --------------------------------------
#ifdef MON_ANALOG

#ifdef ANALOG_AVG_EN
  unsigned int adc_rd_count;
  rd_val_anlg = 0; // RE-INITIALIZE TO ZERO

  for (adc_rd_count = 0; adc_rd_count < anlg_ch_avg_count; adc_rd_count++) {
    rd_val_anlg += analogRead(A0);
    delay(0.5*1000); // 0.5 msecs; MINIMUM 0.1 msecs GAP BETWEEN CONSECUTIVE READS FROM ADC
  }

  rd_val_anlg = unsigned int(rd_val_anlg/adc_rd_count);
  
#else
  rd_val_anlg = analogRead(A0);
#endif

  String string_rd_val_anlg = String(rd_val_anlg); // INT TO STRING CONVERSION

#ifdef LED_MON_EN  
  if (rd_val_anlg < adc_rd_thresh_val) { // MODIFY CODE ACCORDING TO DEBUG LOGIC
    digitalWrite(mon_led_pin,HIGH);      // NOTE: THERE WILL BE A LAG BETWEEN ACTUAL CHANGE OF
  } else {                               //       STIMULUS AND CHANGE OF LED STATUS DUE TO THE 
    digitalWrite(mon_led_pin,LOW);       //       LOOP USED IN THE CODE
  }
#endif
#endif //------------------------------------------------

// DIGITAL CHANNEL 1 ------------------------------------
#ifdef MON_DIGITAL_CH1
#ifdef EVENT_DRIVEN_MODE

#ifdef LED_MON_EN
#ifndef MON_ANALOG
  digitalWrite(mon_led_pin,HIGH);   // WAITING FOR TRIGGER
#endif
#endif

  while(!digitalRead(dbg_dgtl_ch1_pin)) {}; // WAIT FOR LOW TO HIGH TRANSITION

#ifdef LED_MON_EN
#ifndef MON_ANALOG
  digitalWrite(mon_led_pin,LOW);  // TRIGGER RECEIVED
#endif
#endif

    rd_val_dgtl_ch1 = 1; // SET CHANNEL 1 UPDATE DATA TO HIGH

#else
  rd_val_dgtl_ch1 = digitalRead(dbg_dgtl_ch1_pin);
#endif

  String string_rd_val_dgtl_ch1 = String(rd_val_dgtl_ch1); // INT TO STRING CONVERSION
#endif //------------------------------------------------

// DIGITAL CHANNEL 2 ------------------------------------
#ifdef MON_DIGITAL_CH2
#ifdef EVENT_DRIVEN_MODE

#ifdef LED_MON_EN
#ifndef MON_ANALOG
#ifndef MON_DIGITAL_CH1
  digitalWrite(mon_led_pin,HIGH);   // WAITING FOR TRIGGER
#endif
#endif
#endif

  while(!digitalRead(dbg_dgtl_ch2_pin)) {}; // WAIT FOR LOW TO HIGH TRANSITION

#ifdef LED_MON_EN
#ifndef MON_ANALOG
#ifndef MON_DIGITAL_CH1
  digitalWrite(mon_led_pin,LOW);  // TRIGGER RECEIVED
#endif
#endif
#endif

    rd_val_dgtl_ch2 = 1; // SET CHANNEL 2 UPDATE DATA TO HIGH
  
#else
  rd_val_dgtl_ch2 = digitalRead(dbg_dgtl_ch2_pin);
#endif

  String string_rd_val_dgtl_ch2 = String(rd_val_dgtl_ch2); // INT TO STRING CONVERSION
#endif //--------------------------------------------------

// ESTABLISH CONNECTION WITH SERVER
  String strTemp = "AT+CIPSTART=\"TCP\",\"";
  strTemp += Server_IP_addr;
  strTemp += "\",80";
  
  Serial.println(strTemp);
  delay(push_interval); 

// SEND GET REQUEST MESSAGE LENGTH FOLLOWED BY THE REQUEST
  getString_concat = getString_start;
  getString_concat += API_key; // APPEND API KEY FOR THE CHANNEL

#ifdef MON_ANALOG
  getString_concat += getString_fval1;
  getString_concat += string_rd_val_anlg;
#endif

#ifdef MON_DIGITAL_CH1
  getString_concat += getString_fval2;
  getString_concat += string_rd_val_dgtl_ch1;
#endif

#ifdef MON_DIGITAL_CH2
  getString_concat += getString_fval3;
  getString_concat += string_rd_val_dgtl_ch2;
#endif

  int strLen = getString_concat.length(); // LENGTH OF GET STRING
  strLen = strLen + 2; // 2 BYTES FOR CR(CARRIAGE RETURN) AND NL(NEXT LINE) CHARACTERS
  String string_strLen = String(strLen);

  strTemp = "AT+CIPSEND="; // OVERWRITING PREVIOUS VALUE OF strTemp
  strTemp += string_strLen;
  
  Serial.println(strTemp); // SENDING LENGTH
  delay(push_interval); 
  
  Serial.println(getString_concat); // SENDING GET REQUEST
  delay(push_interval); 

// CLOSE CONNECTION  
  Serial.println("AT+CIPCLOSE");

#ifdef ESP_LOW_PWR_MODE
// PUT ESP8266 TO LOW POWER/SLEEP MODE FOR THE ENTIRE REPEAT INTERVAL
  digitalWrite(ch_pd_ctrl_pin,LOW);
#endif

#ifdef EVENT_DRIVEN_MODE  // RESET CHANNEL READ VALUES
  rd_val_dgtl_ch1 = 0;
  rd_val_dgtl_ch2 = 0;
#endif

// REPEAT INTERVAL (EXCLUDING DELAYS BETWEEN AT COMMANDS AND OTHER LOGIC)  
  delay(10*1000); // 10 SEC INTERVAL

} //-------------------------------------------------------------------------

// END OF CODE --------------------------------------------------------------
