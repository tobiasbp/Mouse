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

#ifndef MOUSE_h
#define MOUSE_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//================================================================================
//================================================================================
//  Mouse

#define DRUM_BASS 0x1000
#define DRUM_RED  0x0404

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
  
  void press(uint16_t b);   // press LEFT by default
  void release(uint16_t b); // release LEFT by default
  //bool isPressed(uint8_t b = MOUSE_LEFT); // check LEFT by default
};
extern RockbandDrums_ RockbandDrums;

#endif
#endif
