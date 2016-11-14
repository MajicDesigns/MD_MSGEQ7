/*
 Example program for the MD_MSGEQ7 library
 
 Reads the input value from the IC and displays a spectrum on a 8x8 LED matrix.
 
 MD_MAX72xx library can be found at http://arduinocode.codeplex.com
*/

#include <MD_MSGEQ7.h>
#include <MD_MAX72xx.h>

#define DEBUG 0
#if DEBUG

#define	PRINT(s, x)	  { Serial.print(F(s)); Serial.print(x); }
#define	PRINTS(x)	    Serial.print(F(x))
#define	PRINTD(s, x)	{ Serial.print(F(s)); Serial.print(x, DEC); }
#define	PRINTX(s, x)	{ Serial.print(F(s)); Serial.print(x, HEX); }
#else

#define	PRINT(s, x)
#define PRINTS(x)
#define PRINTD(s, x)
#define PRINTX(s, x)
#endif

// MAX72xx settings
// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define	MAX_DEVICES	1

#define	MX_CLK_PIN	13  // or SCK
#define	MX_DATA_PIN	11  // or MOSI
#define	MX_CS_PIN   10  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(MX_CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(MX_DATA_PIN, MX_CLK_PIN, MX_CS_PIN, MAX_DEVICES);

// MSGEQ7 hardware pin definitions - change to suit circuit
#define DATA_PIN    A5
#define RESET_PIN   6
#define STROBE_PIN  7

// frequency reading the IC data
#define READ_DELAY  75    // milliseconds

MD_MSGEQ7 MSGEQ7(RESET_PIN, STROBE_PIN, DATA_PIN);

void setup() 
{
#if DEBUG
  Serial.begin(57600);
#endif
  PRINTS("[MD_MSG_SEQ7_MAX72xx]");
  
  mx.begin();
  
  MSGEQ7.begin();
}

void loop() 
{
  static uint32_t prevTime = 0;
  
  if (millis() - prevTime >= READ_DELAY) 
  {
    prevTime = millis();

    MSGEQ7.read();

    // Matrix output
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    PRINTS("\n");
    for (uint8_t i=0; i<MAX_BAND; i++)
    {
      PRINT("\t", i);
      uint8_t c = ((MSGEQ7.get(i) - 50) & 0xff) >> 5;  // number between 0 and 7
      uint8_t m = 1;
      
      PRINT(": c=", c); 
      for (uint8_t i=1; i<=c; i++)
        m = (m << 1) | 1;
      PRINTX(": m=0x", m);
      
      mx.setColumn(i, m);
    }
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  }  
}
