/*
MD_MSGEQ7xx - Library for using a MSGEQ7 equalizer IC
  
See header file for comments

This file contains class and hardware related methods.
  
Copyright (C) 2015 Marco Colli. All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include "MD_MSGEQ7.h"

/**
 * \file
 * \brief Implements class definition and general methods
 */

void MD_MSGEQ7::begin(void)
{
	// Initialize the IC
	pinMode(_resetPin, OUTPUT);
	pinMode(_strobePin, OUTPUT);
	pinMode(_dataPin, INPUT);
	reset();
}

void MD_MSGEQ7::reset(void)
{
	// Reset the IC according to the chart in the data sheet
	digitalWrite(_strobePin, LOW);
	digitalWrite(_resetPin, HIGH);
  delayMicroseconds(1); // tr = 100 nanoseconds here - likely the Arduino library will be slower than this anyway
	digitalWrite(_resetPin, LOW);
  delayMicroseconds(72);  // trs = 72 microseconds
}

void MD_MSGEQ7::read(bool bReset)
// Read all the values from the IC and store in local object array
{
	if (bReset) reset(); 	// reset the IC if required

	// read all MAX_BAND channels 
	for (int i = 0; i < MAX_BAND; i++)
  {
		// trigger next value
		digitalWrite(_strobePin, HIGH);
    delayMicroseconds(18);  // ts = 18 microseconds
	  digitalWrite(_strobePin, LOW);

		// allow the output to settle
		delayMicroseconds(36);  // to = 36 microseconds

		// read pin
		_data[i] = analogRead(_dataPin);
    
    delayMicroseconds(18);
  }
}

uint16_t MD_MSGEQ7::get(uint8_t band)
// Read the data from the local data array
{
	// don't read out of bounds
	if (band >= MAX_BAND) return 0;

	return _data[band];
}
