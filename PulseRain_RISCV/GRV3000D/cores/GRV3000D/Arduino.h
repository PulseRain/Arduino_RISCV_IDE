/*
###############################################################################
# Copyright (c) 2018, PulseRain Technology LLC 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License (LGPL) as 
# published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################
*/

#ifndef _ARDUINO_H
#define _ARDUINO_H

#include "encoding.h"
#include "common_type.h"
#include "peripherals.h"
#include "HardwareSerial.h"

//============================================================================================
// Timer Resolution in Hz
//============================================================================================
constexpr uint32_t TIMER_RESOLUTION = 1000000;

//============================================================================================
// csr
//============================================================================================
#define mstatus   0x300
#define mie       0x304
#define mtvec     0x305
#define mip       0x344
#define mepc      0x341

//============================================================================================
// Constant definition
//============================================================================================

constexpr uint8_t INPUT  = 0;
constexpr uint8_t OUTPUT = 1;

constexpr uint8_t HIGH   = 1;
constexpr uint8_t LOW    = 0;

constexpr uint8_t CHANGE  = 2;
constexpr uint8_t RISING  = 3;
constexpr uint8_t FALLING = 4;



#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

//============================================================================================
// serial port
//============================================================================================
extern HardwareSerial Serial;

//============================================================================================
// Function prototype
//============================================================================================
extern uint32_t micros ();
extern uint32_t millis ();


extern void setup();
extern void loop();

extern void delay (uint32_t ms);

extern void interrupts();
extern void noInterrupts();

extern uint8_t isDigit(uint8_t c);

typedef void (*ISR)();

extern void attachInterrupt (uint8_t int_index, ISR isr, uint8_t mode);
extern void detachInterrupt (uint8_t int_index);

extern void timer_advance_ (uint32_t count);

extern uint8_t isDigit(uint8_t c);
extern uint8_t isAscii(uint8_t c);
extern uint8_t isAlpha(uint8_t c);
extern uint8_t isAlphaNumeric(uint8_t c);
extern uint8_t isControl(uint8_t c);
extern uint8_t isGraph (uint8_t c);
extern uint8_t isHexadecimalDigit(uint8_t c);
extern uint8_t toLowerCase(uint8_t c);
extern uint8_t toUpperCase(uint8_t c);
extern uint8_t isLowerCase(uint8_t c);
extern uint8_t isUpperCase(uint8_t c);
extern uint8_t isPrintable(uint8_t c);
extern uint8_t isPunct(uint8_t c);
extern uint8_t isSpace(uint8_t c);
extern uint8_t isWhitespace(uint8_t c);
extern uint8_t toAscii(uint8_t c);
extern uint8_t digitalRead(uint8_t pin);
extern void digitalWrite(uint8_t pin, uint8_t value);

#endif
