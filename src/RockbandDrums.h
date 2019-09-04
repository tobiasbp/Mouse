/*
  RockbandDrums.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

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
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ROCKBANDDRUMS_h
#define ROCKBANDDRUMS_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//======================================================================
//======================================================================


// Drums
#define DRUM_ORANGE  0x1000
#define DRUM_BLUE    0x0104
#define DRUM_GREEN   0x0204
#define DRUM_RED     0x0404
#define DRUM_YELLOW  0x0804

// Buttons
#define BUTTON_1     0x0100
#define BUTTON_A     0x0200
#define BUTTON_B     0x0400
#define BUTTON_2     0x0800
#define BUTTON_MINUS 0x0001
#define BUTTON_PLUS  0x0002
#define BUTTON_LOGO  0x0010

// Dpad
#define DPAD_UP      0x00
#define DPAD_RIGHT   0x02
#define DPAD_DOWN    0x04
#define DPAD_LEFT    0x06
#define DPAD_CENTER  0x08


class RockbandDrums_
{
private:
  uint16_t _buttons;
  void buttons(uint16_t b);

public:
  RockbandDrums_(void);
  
  void begin(void);
  void end(void);
  
  void hit(uint16_t b);
  void move(signed char x, signed char y, signed char wheel = 0);  
  void press(uint16_t b);
  void release(uint16_t b);

};
extern RockbandDrums_ RockbandDrums;

#endif
#endif
