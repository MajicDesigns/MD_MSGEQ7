/*
 Example program for the MD_MSGEQ7 library
 
 Reads the input value from the IC and displays a rolling table on the serial monitor.
*/

#include <MD_MSGEQ7.h>

// hardware pin definitions - change to suit circuit
const uint8_t DATA_PIN = A5;
const uint8_t RESET_PIN = 6;
const uint8_t STROBE_PIN = 7;

// frequency reading the IC data
const uint32_t READ_DELAY = 50;

MD_MSGEQ7 MSGEQ7(RESET_PIN, STROBE_PIN, DATA_PIN, READ_DELAY);

void setup(void) 
{
  MSGEQ7.begin();

  Serial.begin(57600);
  Serial.println("[MD_MSG_SEQ7_Serial]");
}

void loop(void) 
{
  if (MSGEQ7.read())
  {
    // Serial output
    for (uint8_t i=0; i<MD_MSGEQ7::MAX_BAND; i++)
    {
      Serial.print(MSGEQ7.get(i));
      Serial.print('\t');
    }
    Serial.println();
  }  
}
