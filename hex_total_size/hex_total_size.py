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


import sys
from ROM_Hex_Format import *


#==============================================================================
# main            
#==============================================================================

if __name__ == "__main__":

    #=========================================================================
    # print banner
    #=========================================================================
    
    print ("===============================================================================")
    print ("# Copyright (c) 2019, PulseRain Technology LLC ")
    print ("# Utility for Hex File Total Size, Version 1.0")
    print (" ")
    
    #=========================================================================
    # get command line options
    #=========================================================================
    
    if (len(sys.argv) < 2):
        print ("Please provide file name for hex file.")
        sys.exit(1)
    
    file_name = sys.argv[1]
    
    intel_hex_file =  Intel_Hex(file_name)
    
    print ("Total ", intel_hex_file.total_size)
    