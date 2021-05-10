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
# http://stackoverflow.com/questions/25239423/crc-ccitt-16-bit-python-manual-calculation
###############################################################################

class CRC16_CCITT:
    
    _POLYNOMIAL = 0x1021
    _PRESET = 0xFFFF

    def _initial(self, c):
        crc = 0
        c = c << 8
        for j in range(8):
            if (crc ^ c) & 0x8000:
                crc = (crc << 1) ^ self._POLYNOMIAL
            else:
                crc = crc << 1
            c = c << 1
            
        return crc
   
    def _update_crc(self, crc, c):
        cc = 0xff & c

        tmp = (crc >> 8) ^ cc
        crc = (crc << 8) ^ self._tab[tmp & 0xff]
        crc = crc & 0xffff

        return crc
    
    def __init__ (self):
        self._tab = [ self._initial(i) for i in range(256) ]
    
    def get_crc (self, data_list):
        crc = self._PRESET
        for c in data_list:
            crc = self._update_crc(crc, c)
        return [(crc >> 8) & 0xFF, crc & 0xFF]     
    
    
def main():

    crc = CRC16_CCITT ()
    
    for i in range(256):
        print ("0x{0:08x},".format(crc._tab[i]))
    
if __name__ == "__main__":
    main()
    