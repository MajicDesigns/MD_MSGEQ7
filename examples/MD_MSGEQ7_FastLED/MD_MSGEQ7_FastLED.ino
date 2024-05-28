/*
Example program for the MD_MSGEQ7 library

Display the data on a WS2812 RGB LED strip

LED strip hardware used is a strip of 8 WS2812 RGB LEDs
FastLED library, updates and news used can be found at http://fastled.io
*/
#include <FastLED.h>
#include <MD_MSGEQ7.h>

#define DEBUG 0
#if DEBUG
#define	PRINT(s, x)	{ Serial.print(F(s)); Serial.print(x); }
#define	PRINTS(x)	Serial.print(F(x))
#define	PRINTD(x)	Serial.println(x, DEC)
#else
#define	PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)
#endif

// Information about the LED strip itself
#define MAX_LED   8
#define LED_PIN   11
#define CHIPSET   WS2812
#define COLOR_ORDER GRB
#define BRIGHTNESS  128

CRGB leds[MAX_LED];

//MD_MSGEQ7
const uint8_t DATA_PIN = A5;
const uint8_t RESET_PIN = 6;
const uint8_t STROBE_PIN = 7;
const uint32_t READ_DELAY = 50;  // milliseconds

MD_MSGEQ7 MSGEQ7(RESET_PIN, STROBE_PIN, DATA_PIN, READ_DELAY);

void setup(void) 
{
#if DEBUG
  Serial.begin(57600);
#endif
  PRINTS("[MD_MSGEQ7_FastLED]");

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, MAX_LED).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.setDither(0);
  FastLED.show();

  MSGEQ7.begin();
}

void loop(void) 
{
  static uint8_t  bandHue[MD_MSGEQ7::MAX_BAND] = 
  { 
    HUE_PURPLE, HUE_PINK, HUE_RED, HUE_YELLOW, HUE_GREEN, HUE_AQUA, HUE_BLUE 
  };
 
  if (MSGEQ7.read()) 
  {
    for (int i = 0; i < MD_MSGEQ7::MAX_BAND; i++) 
    {
      leds[i].setHSV(bandHue[i], 255, MSGEQ7.get(i) & 0xff);
    }

    FastLED.show();
  }
}
