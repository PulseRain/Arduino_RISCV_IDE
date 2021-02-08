/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

#include "HardwareSerial.h"

//== Dec, 2018, Modified by PulseRain Technology, LLC

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long baud)
{
    *REG_UART_RX = REG_UART_RX_FIFO_SYNC_RESET_BIT;
}

void HardwareSerial::end()
{

}

int HardwareSerial::available(void)
{
    if ((*REG_UART_RX) & REG_UART_RX_FIFO_NOT_EMPTY_BIT) {
        return 1;
    } else {
        return 0;
    }
}

int HardwareSerial::peek(void)
{
  return 0;
}

int HardwareSerial::read(void)
{
    *REG_UART_RX = REG_UART_RX_READ_REQ_BIT;
    
    return ((*REG_UART_RX) & 0xFF);

}

void HardwareSerial::flush()
{

}



size_t HardwareSerial::_write(uint8_t c)
{
 
  
    while ((*REG_UART_TX) & 0x80000000);
   
    (*REG_UART_TX) = c;
   


    return 1;
}

