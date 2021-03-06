
#include <EEPROM.h>

int address = 5;  // the current address in the EEPROM (i.e. which byte we're going to write to next)
int input_value = 36; // Random value
int output_value;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  
  EEPROM.write(address, input_value); // Keeps overwrinting in every loop
    
 // CODE SNIPPET TO INCREMENT ADDRESS
  /*
    address = address + 1;       //  Advance to the next address.
    if (address == 1024)         //  There are 1024 bytes in the EEPROM of Atmega328 based Arduino, so go back to 0 when we hit 1024.
    address = 0;
   
  */
  
  delay(2000); // Just a gap between read and write operations. Not mandatory.
  
  output_value = EEPROM.read(address);
  
  Serial.print(address);
  Serial.print("\t");
  Serial.print(output_value, DEC); // DEC stands for decimal system. Another example can be BIN which stands for binary.
  Serial.println();
  
}
