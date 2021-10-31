/*
###############################################################################
# Copyright (c) 2016, PulseRain Technology LLC 
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
#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "common_type.h"
#include "HardwareSerial.h"


//============================================================================================
// MTIME 
//============================================================================================
volatile uint32_t* const REG_MTIME_LOW  = (uint32_t*) 0x20000000;
volatile uint32_t* const REG_MTIME_HIGH = (uint32_t*) 0x20000004;

//============================================================================================
// MTIMECMP 
//============================================================================================

volatile uint32_t* const REG_MTIMECMP_LOW  = (uint32_t*)0x20000008;
volatile uint32_t* const REG_MTIMECMP_HIGH = (uint32_t*)0x2000000C;


//============================================================================================
// UART 
//============================================================================================

volatile uint32_t* const REG_UART_TX = (uint32_t*) 0x20000010;
volatile uint32_t* const REG_UART_RX = (uint32_t*) 0x20000014;

constexpr uint32_t REG_UART_RX_READ_REQ_BIT        = 1 << 31;
constexpr uint32_t REG_UART_RX_FIFO_FULL_BIT       = 1 << 30;
constexpr uint32_t REG_UART_RX_FIFO_NOT_EMPTY_BIT  = 1 << 29;
constexpr uint32_t REG_UART_RX_FIFO_SYNC_RESET_BIT = 1 << 28;

//============================================================================================
// GPIO 
//============================================================================================
volatile uint8_t* const REG_GPIO     = (uint8_t*)0x20000018;
volatile uint8_t* const REG_GPIO_OUT = (uint8_t*)0x20000030;

#define GPIO_P0  (REG_GPIO[0])
#define GPIO_P1  (REG_GPIO[1])
#define GPIO_P2  (REG_GPIO[2])
#define GPIO_P3  (REG_GPIO[3])

//============================================================================================
// I2C
//============================================================================================

volatile uint8_t* const REG_I2C_CSR  = (uint8_t*) 0x20000024;
volatile uint8_t* const REG_I2C_DATA = (uint8_t*) 0x20000028;

//============================================================================================
// Interrupt 
//============================================================================================
volatile uint32_t* const REG_INT_SOURCE = (uint32_t*)0x2000001C;
volatile uint32_t* const REG_INT_ENABLE = (uint32_t*)0x20000020;

constexpr uint32_t INT_TIMER_INDEX      = 0;
constexpr uint32_t INT_UART_RX_INDEX    = 1;
constexpr uint32_t INT_EXTERNAL_1ST     = 30;
constexpr uint32_t INT_EXTERNAL_LAST    = 31;


constexpr uint32_t MCAUSE_INTERRUPT    = 1 << 31;
constexpr uint32_t MCAUSE_TIMER        = 0x7;
constexpr uint32_t MCAUSE_PERIPHERAL   = 0xB;

constexpr uint32_t MCAUSE_TIMER_MASK       = 1 << MCAUSE_TIMER;
constexpr uint32_t MCAUSE_PERIPHERAL_MASK  = 1 << MCAUSE_PERIPHERAL;

constexpr uint32_t MSTATUS_MIE_BIT         = 1 << 3;


//============================================================================================
// Rotary Encoder
//============================================================================================
volatile uint32_t* const REG_ROTARY_ENCODER = (uint32_t*)0x20000030;

#endif
