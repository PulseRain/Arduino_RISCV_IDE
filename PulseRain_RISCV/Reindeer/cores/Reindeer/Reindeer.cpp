/*
###############################################################################
# Copyright (c) 2018, PulseRain Technology LLC 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or 
# (at your option) any later version.
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
#include <stdarg.h>

#include "WString.h"
#include "Printable.h"
#include "Print.h"
#include "Stream.h"

#include "HardwareSerial.h"
#include "peripherals.h"

HardwareSerial Serial;

//----------------------------------------------------------------------------
// micros()
//
// Parameters:
//      None
//
// Return Value:
//      number of microseconds passed since reset
//
// Remarks:
//      function to keep track of time since reset
//----------------------------------------------------------------------------

uint32_t micros ()
{
    return (*REG_MTIME_LOW);
} // End of micros()


//----------------------------------------------------------------------------
// millis()
//
// Parameters:
//      None
//
// Return Value:
//      number of milliseconds passed since reset
//
// Remarks:
//      function to keep track of time since reset
//----------------------------------------------------------------------------

uint32_t millis ()
{
    uint32_t low;
    
    low  = (*REG_MTIME_LOW);
    
    low /= 1000;
    
    return (low);
} // End of millis()

static uint32_t interrupt_saved_mstatus;

static void interrupt_save_and_disable_ ()
{
    interrupt_saved_mstatus    = read_csr (mstatus);
    write_csr (mstatus, 0);
 
}

static void interrupt_restore_saved_value_ ()
{
    write_csr (mstatus, interrupt_saved_mstatus);
   
}


//----------------------------------------------------------------------------
// interrupts()
//
// Parameters:
//      None
//
// Return Value:
//      None
//
// Remarks:
//      Enable Interrupt
//----------------------------------------------------------------------------

void interrupts()
{
    write_csr (mie, MCAUSE_TIMER_MASK | MCAUSE_PERIPHERAL_MASK);
    write_csr (mstatus, MSTATUS_MIE_BIT);
}

//----------------------------------------------------------------------------
// noInterrupts()
//
// Parameters:
//      None
//
// Return Value:
//      None
//
// Remarks:
//      Disable Interrupt
//----------------------------------------------------------------------------

void noInterrupts()
{
    write_csr (mie, 0);
    write_csr (mstatus, 0);
}

//----------------------------------------------------------------------------
// delay()
//
// Parameters:
//      ms : delay in milliseconds
//
// Return Value:
//      None
//
// Remarks:
//      delay by milliseconds
//----------------------------------------------------------------------------

void delay (uint32_t ms)
{
    uint32_t low, high;
    uint64_t finish_time, current_time;
    
    uint32_t delay_interrupt_saved_mstatus    = read_csr (mstatus);
    
    write_csr (mstatus, 0);
        low  = (*REG_MTIME_LOW);
        high = (*REG_MTIME_HIGH);
    write_csr (mstatus, delay_interrupt_saved_mstatus);
    
    finish_time = ((uint64_t)high << 32) + (uint64_t)(low) + (uint64_t)ms*1000;
    
    do {
        
        write_csr (mstatus, 0);
            low  = (*REG_MTIME_LOW);
            high = (*REG_MTIME_HIGH);
        write_csr (mstatus, delay_interrupt_saved_mstatus);
        
        current_time = ((uint64_t)high << 32) + (uint64_t)(low);
    } while (finish_time > current_time);

} // End of delay()

static void _putchar(char n)
{
    while ((*REG_UART_TX) & 0x80000000);
    (*REG_UART_TX) = n;
    while ((*REG_UART_TX) & 0x80000000);
}

static void _puts (char p[])
{
    int i = 0;
    
    while (p[i]) {
        _putchar (p[i]);
        ++i;
    }
  
}

static char *convert(unsigned int num, unsigned int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[200]; 
    char *ptr; 
    
    ptr = &buffer[199]; 
    *ptr = '\0'; 
    
    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 
    
    return(ptr); 
}

void myprint(const char* str, ...)
{

    char *traverse; 
    int i; 
    char *s; 
    
    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, str); 
    
    traverse = (char*) str;
    while (*traverse) {
        if ((*traverse) != '%') {
            _putchar (*traverse);
            ++traverse;   
        } else {
            ++traverse;
            
            switch(*traverse++) { 
                case 'c' : i = va_arg(arg,int);     //Fetch char argument
                            _putchar(i);
                            break; 
                            
                case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                            if(i<0) 
                            { 
                                i = -i;
                                _putchar('-'); 
                            } 
                            _puts(convert(i,10));
                            break; 
                            
                case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                            _puts(convert(i,8));
                            break; 
                            
                case 's': s = va_arg(arg,char *);       //Fetch string
                            _puts(s); 
                            break; 
                            
                case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                            _puts(convert(i,16));
                            break; 
            }
            
        }
        
        
    }
    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 

}

void _exit (int status)
{
    while (1) {}        /* Make sure we hang here */
}



 //----------------------------------------------------------------------------
// isDigit()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if the value input is in [0-9]
//
// Remarks:
//      determine if the input char is a digit
//----------------------------------------------------------------------------

uint8_t isDigit(uint8_t c)
{
  if ((c >= '0') && (c <= '9')) {
    return 1;
  } 

  return 0;
  
} // End of isDigit()
