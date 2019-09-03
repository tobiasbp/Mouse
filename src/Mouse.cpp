/*
  Mouse.cpp

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

#include "Mouse.h"

#if defined(_USING_HID)

static const uint8_t _hidReportDescriptor[] PROGMEM = {
  
    //  Rockband drum controller (Wii)
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,       // USAGE (Gamepad)
    0xa1, 0x01,       // COLLECTION (Application)
    0x15, 0x00,       // LOGICAL MINIMUM (0)  
    0x25, 0x01,       // LOGICAL MAXIMUM (1)
    0x35, 0x00,       // PHYSICAL MINIMUM (0)
    0x45, 0x01,       // PHYSICAL MAXIMUM (1)
    0x75, 0x01,       // REPORT SIZE (1)
    0x95, 0x0D,       // REPORT COUNT (13)
    0x05, 0x09,       // USAGE PAGE (Buttons)
    0x19, 0x01,       // USAGE MINIMUM (Button 1)
    0x29, 0x0D,       // USAGE MAXIMUM (Button 13)
    0x81, 0x02,       // INPUT (Data,Var,Abs)
    0x95, 0x03,       // REPORT COUNT (3)
    0x81, 0x01,       // INPUT (Cnst,Arr,Abs)
    0x05, 0x01,       // USAGE PAGE (Generic Desktop Controls)
    0x25, 0x07,       // LOGICAL MAXIMUM (7)
    0x46, 0x3B, 0x01, // PHYSICAL MAXIMUM (315)
    0x75, 0x04,       // REPORT SIZE (4)
    0x95, 0x01,       // REPORT COUNT (1)
    0x65, 0x14,       // UNIT (System: English Rotation, Unit: Degrees)
    0x09, 0x39,       // USAGE (Hat Switch)
    0x81, 0x42,       // INPUT (Data,Var,Abs,Null)
    0x65, 0x00,       // UNIT (0)
    0x95, 0x01,       // REPORT COUNT (1)
    0x81, 0x01,       // INPUT (Cnst,Arr,Abs)
    0x26, 0xFF, 0x00  // LOGICAL MAXIMUM (255)
    0x46, 0xFF, 0x00  // PHYSICAL MAXIMUM (255)
    0x09, 0x30,       // USAGE (DIRECTION X)
    0x09, 0x31,       // USAGE (DIRECTION Y)
    0x09, 0x32,       // USAGE (DIRECTION Z)
    0x09, 0x35,       // USAGE (ROTATE Z)
    0x75, 0x08,       // REPORT SIZE (8)
    0x95, 0x04,       // REPORT COUNT (4)
    0x81, 0x02,       // INPUT (Data,Var,Abs)
    0x06, 0x00, 0xFF  // USAGE PAGE (65280)
    0x09, 0x20,       // USAGE (32)
    0x09, 0x21,       // USAGE (33)
    0x09, 0x22,       // USAGE (34)
    0x09, 0x23,       // USAGE (35)
    0x09, 0x24,       // USAGE (36)
    0x09, 0x25,       // USAGE (37)
    0x09, 0x26,       // USAGE (38)
    0x09, 0x27,       // USAGE (39)
    0x09, 0x28,       // USAGE (40)
    0x09, 0x29,       // USAGE (41)
    0x09, 0x2A,       // USAGE (42)
    0x09, 0x2B,       // USAGE (43)
    0x95, 0x0C,       // REPORT COUNT (12)
    0x81, 0x02,       // INPUT (Data,Var,Abs)
    0x0A, 0x21, 0x26, // USAGE (9761)
    0x95, 0x08,       // REPORT COUNT (8)
    0xB1, 0x02,       // FEATURE (2)
    0x0A, 0x21, 0x26, // USAGE (9761)
    0x91, 0x02,       // OUTPUT (Data,Var,Abs)
    0x26, 0xFF, 0x03, // LOGICAL MAXIMUM (1023)
    0x46, 0xFF, 0x03, // PHYSICAL MAXIMUM (1023)
    0x09, 0x2C,       // USAGE (44)
    0x09, 0x2D,       // USAGE (45)
    0x09, 0x2E,       // USAGE (46)
    0x09, 0x2F,       // USAGE (47)
    0x75, 0x10,       // REPORT SIZE (16)
    0x95, 0x04,       // REPORT COUNT (4)
    0x81, 0x02,       // INPUT (Data,Var,Abs)
    0xC0              // END COLLECTION
};

//================================================================================
//================================================================================
//	Mouse

Mouse_::Mouse_(void) : _buttons(0)
{
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}

void Mouse_::begin(void) 
{
}

void Mouse_::end(void) 
{
}

void Mouse_::click(uint8_t b)
{
	_buttons = b;
	move(0,0,0);
	_buttons = 0;
	move(0,0,0);
}

void Mouse_::move(signed char x, signed char y, signed char wheel)
{
	uint8_t m[4];
	m[0] = _buttons;
	m[1] = x;
	m[2] = y;
	m[3] = wheel;
	HID().SendReport(1,m,4);
}

void Mouse_::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		move(0,0,0);
	}
}

void Mouse_::press(uint8_t b) 
{
	buttons(_buttons | b);
}

void Mouse_::release(uint8_t b)
{
	buttons(_buttons & ~b);
}

bool Mouse_::isPressed(uint8_t b)
{
	if ((b & _buttons) > 0) 
		return true;
	return false;
}

Mouse_ Mouse;

#endif
