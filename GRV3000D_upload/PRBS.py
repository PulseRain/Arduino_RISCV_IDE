#! python3
###############################################################################
# Copyright (c) 2021, PulseRain Technology LLC 
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


###############################################################################
# References:
# https://en.wikipedia.org/wiki/Pseudorandom_binary_sequence
###############################################################################

class PRBS:

    def reset(self, prbs_length, start_value):
        if (prbs_length == 7):
            self.poly = 0xC1 >> 1
        elif (prbs_length == 9):
            self.poly = 0x221 >> 1
        elif (prbs_length == 11):
            self.poly = 0xA01 >> 1
        elif (prbs_length == 15):
            self.poly = 0xC001 >> 1
        elif (prbs_length == 20):
            self.poly = 0x80005 >> 1
        elif (prbs_length == 23):
            self.poly = 0x840001 >> 1
        else:
            assert (prbs_length == 31)
            self.poly = 0xA0000001 >> 1
        self.state = start_value
        self.prbs_length = prbs_length
                
    def __init__ (self, prbs_length, start_value):
        self.reset (prbs_length, start_value)
    
    def get_next (self):
        next_bit = 0
        for i in range(self.prbs_length):
            if ((self.poly >> i) & 1):
                next_bit = next_bit ^ ((self.state >> i) & 1) 
        
        self.state = ((self.state << 1) | next_bit) & ((2**(self.prbs_length + 1)) - 1)
        
        return self.state
        
    
    
def main():
    init = 2
    p = PRBS (15, init)
    
    i = 0
    while(1):
        x = p.get_next()
        print ("%d 0x%x" % (i, x))
        
        if (x == init):
            print ("period = %d" % (i + 1))
            break
            
        
        i = i + 1
    
if __name__ == "__main__":
    main()
    