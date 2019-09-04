/*
  RockbandDrums.cpp

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

#include "RockbandDrums.h"

#if defined(_USING_HID)

static const uint8_t _hidReportDescriptor[] PROGMEM = {

    // Rockband drum controller (Wii)
    
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
    0x26, 0xFF, 0x00, // LOGICAL MAXIMUM (255)
    0x46, 0xFF, 0x00, // PHYSICAL MAXIMUM (255)
    0x09, 0x30,       // USAGE (DIRECTION X)
    0x09, 0x31,       // USAGE (DIRECTION Y)
    0x09, 0x32,       // USAGE (DIRECTION Z)
    0x09, 0x35,       // USAGE (ROTATE Z)
    0x75, 0x08,       // REPORT SIZE (8)
    0x95, 0x04,       // REPORT COUNT (4)
    0x81, 0x02,       // INPUT (Data,Var,Abs)
    0x06, 0x00, 0xFF, // USAGE PAGE (65280)
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
// RockbandDrums

RockbandDrums_::RockbandDrums_(void) : _buttons(0)
{
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}

void RockbandDrums_::begin(void) 
{
}

void RockbandDrums_::end(void) 
{
}


void RockbandDrums_::hit(uint16_t b)
{
    press(b);
    release(b);
}


void RockbandDrums_::send()
{

    // The 27 bytes sent by the drum controller
    // This is the state when no pad/buttons are pressed
    uint8_t d[] = {
      0x00, 0x00, 0x08, 0x7F, 0x7F,
      0x7F, 0x7F, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x02,
      0x00, 0x02, 0x00, 0x02, 0x00,
      0x02, 0x00
    };
    
    // Update two first bytes with button data
    d[0] = highByte(_buttons);
    d[1] = lowByte(_buttons);
    
    // 3rd byte is the dpad state 
    d[2] = _dpad;

    // Send the data
    // 1st argument (an ID) is sent before the rest of the data
    // The drum controller does not use the first byte for an ID,
    // so we will send the 1st byte of the payload as ID.
    // The following 26 bytes follows
    // 1 + 26 = 27 the bytes we want to send
    HID().SendReport(d[0], &d[1], 26);
    
}

void RockbandDrums_::buttons(uint16_t b)
{
    if (b != _buttons)
    {
        _buttons = b;
        send();
    }
}

void RockbandDrums_::press(uint16_t b) 
{
    buttons(_buttons | b);
}

void RockbandDrums_::release(uint16_t b)
{
    buttons(_buttons & ~b);
}

void RockbandDrums_::dpad(uint8_t b)
{
    if (b != _dpad)
    {
        _dpad = b;
        send();
    }
}

RockbandDrums_ RockbandDrums;

#endif
