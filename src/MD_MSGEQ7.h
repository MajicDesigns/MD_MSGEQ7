/**
\mainpage Arduino MSGEQ7 Graphic Equalizer Library
The MSGEQ7 Seven Band Graphic Equalizer IC
------------------------------------------
The seven band graphic equalizer IC is a CMOS chip that divides the 
audio spectrum into seven bands, 63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 
6.25kHz and 16kHz. The seven frequencies are peak detected and multiplexed 
to the output to provide a DC representation of the amplitude of each band. 
The multiplexor is controlled by a reset and a strobe, permitting multiplexor
readout with only two pins.

This library implements functions that allow the IC to be controlled and the
data read into an internal buffer, from which it can be conveniently accessed.

The Hardware
------------
The hardware implementation is user dependent. Most hardware will 
follow the typical circuit given in the IC datasheet.

![MSGEQ7 Standard circuit from the datasheet] (MSGEQ7_Circuit.jpg "MSGEQ7 Circuit")

Connections to the Arduino Board
--------------------------------
The Arduino interface is implemented with 2 digital outputs and one Analog input
whose identifiers are passed through to the class constructor.
- The library controls the IC using _Reset_ and _Strobe_. 
- The _DC Out_ signal is connected to an analog input to read the value from the IC.


Revision History 
----------------
April 2015 version 1.0
- First implementation

Copyright
---------
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
#ifndef MD_MSGEQ7H
#define MD_MSGEQ7H

#include <Arduino.h>

/**
 * \file
 * \brief Main header file for the MD_MSGEQ7 library
 */

#define MAX_BAND 7		///< Number of bands output by the hardware IC

/**
 * Core object for the MD_MSGEQ7 library
 */
class MD_MSGEQ7
{
public:
  /** 
   * Class Constructor - arbitrary digital interface.
   *
   * Instantiate a new instance of the class. The parameters passed are used to 
   * connect the software to the hardware. Multiple instances may co-exist. 
   * 
   * \param resetPin	Arduino output pin for IC reset.
   * \param strobePin	Arduino output for strobing the device during read.
   * \param dataPin		Arduino input where data gets read from the IC.
   */
 	MD_MSGEQ7(uint8_t resetPin, uint8_t strobePin, uint8_t dataPin):
		_resetPin(resetPin), _strobePin(strobePin), _dataPin(dataPin) 
		{};

  /** 
   * Class Destructor.
   *
   * Does the necessary to clean up once the object is no longer required.
   */
  ~MD_MSGEQ7(void) {};

  /** 
   * Initialize the object.
   *
   * Initialise the object data. This needs to be called during setup() to 
	 * initialise new data for the class that cannot be done during the object 
	 * creation.
	 *
	 * \return	No return value.
   */
	void begin(void);

  //--------------------------------------------------------------
  /** \name Methods for object and hardware control.
   * @{
   */

  /**
   * Reset the IC before initiating a read.
   *
   * \return No return value.
   */
	void reset(void);
	
  /**
   * Read the next set of data from the IC.
   *
	 * Read a full set of MAX_BAND values from the IC. The optional parameter
	 * is used to suppress a reset before the read - default is to reset.
	 * 
   * \param bReset	enables a device reset prior to read if true, disables if false.
   * \return No Return value.
   */
	void read(bool bReset = true);
	
  /**
   * Get a specific value from the data read.
	 *
	 * Read data elements from the device buffer filled by a previous read() call.
	 * The elements referenced are numbered 0..MAX_BAND-1 for IC values centered 
	 * around the 63Hz, 160Hz, 400Hz, 1KHz, 2.5KHz, 6.25KHz and 16kHz bands 
	 * respectively.
   *
   * \param band		index of the data point requested [0..MAX_BAND-1].
   * \return The value requested from the buffer.
   */
	uint16_t get(uint8_t band);
  /** @} */

private:
	// pins to interact with the IC
	uint8_t _resetPin;
	uint8_t _strobePin;
	uint8_t _dataPin;

	// array of all input values
	uint16_t _data[MAX_BAND];
};

#endif

