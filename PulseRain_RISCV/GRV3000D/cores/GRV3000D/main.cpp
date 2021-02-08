/*
###############################################################################
# Copyright (c) 2019, PulseRain Technology LLC 
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

#include "Arduino.h"



static ISR timer_isr = 0;
static ISR uart_rx_isr = 0;
static ISR INTx_isr[INT_EXTERNAL_LAST - INT_EXTERNAL_1ST + 1] = {0};

//-----------------------------------------------------------------------------
// The main ISR
//-----------------------------------------------------------------------------

static void shared_isr(void)__attribute__((interrupt));
static void shared_isr(void) {
    uint32_t t = read_csr (mcause);
    uint8_t  i, code = t & 0xFF;
    uint32_t old_mstatus_value = read_csr (mstatus);
    write_csr(mstatus, 0);
    
    if ((t & MCAUSE_INTERRUPT) == 0) { // Exception
        Serial.print ("Exception !!!!! Exception Code = 0x");
        Serial.println (code, HEX);
        Serial.print ("MEPC = 0x");
        Serial.println (read_csr(mepc), HEX);
    } else { // Interrupt
        
        if (code == MCAUSE_TIMER) {
          
            t = read_csr (mip);
            t &= ~MCAUSE_TIMER_MASK;
            write_csr (mip, t);

            if (timer_isr) {
                timer_isr();
            }
          
        } else {
            
            t = *REG_INT_SOURCE;
            
            if (t & (1 << INT_UART_RX_INDEX)) {
            
                if (uart_rx_isr) {
                    uart_rx_isr ();
                }
                
            } 
            
            for (i = INT_EXTERNAL_1ST; i <= INT_EXTERNAL_LAST; ++i) {
                if (t & ( 1 << i)) {
                    
                    if (INTx_isr[i - INT_EXTERNAL_1ST]) {
                       
                            INTx_isr[i - INT_EXTERNAL_1ST]();
                       
                    }
                }
            } // End of for loop
            
            
            t = read_csr (mip);
            t &= ~MCAUSE_PERIPHERAL_MASK;
            write_csr (mip, t);
            
      }
    }

    write_csr(mstatus, old_mstatus_value);

} // End of shared_isr()

//-----------------------------------------------------------------------------
// attachInterrupt()
//
// Parameters:
//      int_index : INT_TIMER_INDEX, INT_UART_RX_INDEX etc
//      isr       : function pointer for ISR hook
//      mode      : at this point, only RISING is supported
//
// Return Value:
//      None
//
// Remarks:
//      function to install the ISR hook
//-----------------------------------------------------------------------------

void attachInterrupt (uint8_t int_index, ISR isr, uint8_t mode)
{
    if (mode == RISING) {
        if (int_index == INT_TIMER_INDEX) {
            timer_isr = isr;
        } else if (int_index == INT_UART_RX_INDEX) {
            uart_rx_isr = isr;
            (*REG_INT_ENABLE) |= 1 << INT_UART_RX_INDEX;
        } else if ((int_index >= INT_EXTERNAL_1ST) && (int_index <= INT_EXTERNAL_LAST)) {
            INTx_isr [int_index - INT_EXTERNAL_1ST] = isr;
            (*REG_INT_ENABLE) |= 1 << int_index;
        } else {
            Serial.print ("unknown interrupt index ");
            Serial.println(int_index);
        }
        
    } else {
        Serial.print ("unsupported mode ");
        Serial.print (mode);
        Serial.println (" for attachInterrupt");
        
        return;
    }
} // End of attachInterrupt() 

//-----------------------------------------------------------------------------
// detachInterrupt()
//
// Parameters:
//      int_index : INT_TIMER_INDEX, INT_UART_RX_INDEX etc
//
// Return Value:
//      None
//
// Remarks:
//      function to clear the ISR hook
//-----------------------------------------------------------------------------

void detachInterrupt (uint8_t int_index)
{
  
    if (int_index == INT_TIMER_INDEX) {
        timer_isr = 0;
    } else if (int_index == INT_UART_RX_INDEX) {
        uart_rx_isr = 0;
        (*REG_INT_ENABLE) &= ~(1 << INT_UART_RX_INDEX);
    } else if ((int_index >= INT_EXTERNAL_1ST) && (int_index <= INT_EXTERNAL_LAST)) {
        INTx_isr [int_index - INT_EXTERNAL_1ST] = 0;
        (*REG_INT_ENABLE) &= ~(1 << int_index);
    } else {
        Serial.print ("unknown interrupt index ");
        Serial.println(int_index);
    }
} // End of detachInterrupt()

//-----------------------------------------------------------------------------
// main()
//
// Parameters:
//      None
//
// Return Value:
//      None
//
// Remarks:
//      main function
//-----------------------------------------------------------------------------
 
int main()
{          
    noInterrupts();
    Serial.begin(115200);
    write_csr (mtvec, (uint32_t)shared_isr);

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // ARDUINO sketch
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        setup();
        
        while (1) {
          loop();
        } // End of while loop
        
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    return 0;
} // End of main()
