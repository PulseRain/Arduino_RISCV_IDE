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
} // End of _putchar()

static void _puts (char p[])
{
    int i = 0;
    
    while (p[i]) {
        _putchar (p[i]);
        ++i;
    }
  
}

// for printf to serial port

extern "C"
{
    int _write(int file, char *data, int len)
    {
      
       int i;
       
        for (i = 0; i < len; ++i) {
            while ((*REG_UART_TX) & 0x80000000);
                (*REG_UART_TX) = data[i];
            while ((*REG_UART_TX) & 0x80000000);
        }
     
       // return # of bytes written - as best we can tell
       return len; 
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


//----------------------------------------------------------------------------
// isAscii()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if the value input is less than 128
//
// Remarks:
//      determine if the input char is a ASCII character 
//----------------------------------------------------------------------------

uint8_t isAscii(uint8_t c)
{
    if (c & 0x80) {
        return 1;
    } 
    
    return 0;
} // End of isAscii()


//----------------------------------------------------------------------------
// isAlpha()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if the value input is a letter (capital letter or small letter)
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t isAlpha(uint8_t c)
{
    if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
        return 1;
    } 
    
    return 0;
}


//----------------------------------------------------------------------------
// isAlphaNumeric()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if the value input is a letter or digit
//
// Remarks:
//     
//----------------------------------------------------------------------------

uint8_t isAlphaNumeric(uint8_t c)
{
    if (isDigit(c) || isAlpha(c)) {
        return 1;
    }

    return 0;
}

//----------------------------------------------------------------------------
// isControl()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if the value input is a control character
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t isControl(uint8_t c)
{
  return iscntrl (c);
}


//----------------------------------------------------------------------------
// isGraph()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if the value input is a character with graphical representation
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t isGraph (uint8_t c)
{
    return (isgraph (c));
}


//----------------------------------------------------------------------------
// isHexadecimalDigit()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if the value input is a character is a hexadecimal digit character
//      (0-9, a-f, A-F)
//
// Remarks:
//      
//----------------------------------------------------------------------------
uint8_t isHexadecimalDigit(uint8_t c)
{
  return (isxdigit (c));
}

//----------------------------------------------------------------------------
// toLowerCase()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      The lower case of the input
//
// Remarks:
//      
//----------------------------------------------------------------------------
uint8_t toLowerCase(uint8_t c)
{
  return tolower (c);
} // End of toLowerCase()


//----------------------------------------------------------------------------
// toUpperCase()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      The upper case of the input
//
// Remarks:
//      
//----------------------------------------------------------------------------
uint8_t toUpperCase(uint8_t c)
{
  return (toupper (c));
} // End of toUpperCase()


//----------------------------------------------------------------------------
// isLowerCase()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if it is a lower case letter
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t isLowerCase(uint8_t c)
{
  return (islower (c));
} // End of isLowerCase()

//----------------------------------------------------------------------------
// isUpperCase()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if it is a upper case letter
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t isUpperCase(uint8_t c)
{
  return (isupper (c));
} // End of isUpperCase()


//----------------------------------------------------------------------------
// isPrintable()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if it is a printable character 
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t isPrintable(uint8_t c)
{
  return (isprint (c));
} // End of isPrintable()


//----------------------------------------------------------------------------
// isPunct()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if it is a punctuation character
//
// Remarks:
//      
//----------------------------------------------------------------------------
uint8_t isPunct(uint8_t c)
{
  return (ispunct (c));
} // End of isPunct()


//----------------------------------------------------------------------------
// isSpace()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if it is a space character
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t isSpace(uint8_t c)
{
    if (c == ' ') {
        return 1;
    }

    return 0;
  
} // End of isSpace()

//----------------------------------------------------------------------------
// isWhitespace()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      1 if it is a space or tab
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t isWhitespace(uint8_t c)
{
    if ((c == ' ') || (c == '\t')) {
        return 1;
    }

    return 0;
} // End of isWhitespace()

//----------------------------------------------------------------------------
// toAscii()
//
// Parameters:
//      c : char value input
//
// Return Value:
//      The lower 7 bits of the input
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t toAscii(uint8_t c)
{
    return (c & 0x7F);
} // End of toAscii()


//----------------------------------------------------------------------------
// digitalRead()
//
// Parameters:
//      pin : index to the GPIO
//
// Return Value:
//      The HIGH/LOW status of the GPIO
//
// Remarks:
//      
//----------------------------------------------------------------------------

uint8_t digitalRead(uint8_t pin)
{
    uint8_t n = pin >> 3;
    uint8_t i = pin % 8;
    
    uint8_t t = REG_GPIO[n];
    
    t = (t >> i) & 1;
    
    return t;
} // End of digitalRead()



void digitalWrite(uint8_t pin, uint8_t value)
{
    uint8_t n = pin >> 3;
    uint8_t i = pin % 8;
    
    uint8_t t = REG_GPIO_OUT[n];
    
    if (value) {
        t |= 1 << i; 
    } else {
        t &= ~(1 << i);
    }

} // End of digitalWrite()

