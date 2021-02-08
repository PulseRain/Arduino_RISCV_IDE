#!/usr/bin/env bash

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

Reindeer_version=1.3.9
Rattlesnake_version=1.3.4

Reindeer_compiler_version=1.1.0
Reindeer_upload_version=2.1.0

Rattlesnake_compiler_version=1.1.0
Rattlesnake_upload_version=1.1.0

hex_total_size_version=1.0.0



Reindeer_pkg_name="Reindeer_"
Reindeer_pkg_name+=$Reindeer_version
Reindeer_pkg_name+=".tar.gz"
if [ -f "./package/$Reindeer_pkg_name" ]
then
    echo "=====================> $Reindeer_pkg_name already exists!"
else
    cd ./PulseRain_RISCV/Reindeer;tar zcf ../../package/$Reindeer_pkg_name .;cd ../..
fi
sha256_Reindeer=$(sha256sum ./package/$Reindeer_pkg_name | awk '{print $1}')
size_Reindeer=$(stat -c %s ./package/$Reindeer_pkg_name)


Rattlesnake_pkg_name="Rattlesnake_"
Rattlesnake_pkg_name+=$Rattlesnake_version
Rattlesnake_pkg_name+=".tar.gz"
if [ -f "./package/$Rattlesnake_pkg_name" ]
then
    echo "=====================> $Rattlesnake_pkg_name already exists!"
else
    cd ./PulseRain_RISCV/Rattlesnake;tar zcf ../../package/$Rattlesnake_pkg_name .;cd ../..
fi
sha256_Rattlesnake=$(sha256sum ./package/$Rattlesnake_pkg_name | awk '{print $1}')
size_Rattlesnake=$(stat -c %s ./package/$Rattlesnake_pkg_name)



Reindeer_compiler_name="Reindeer_compiler_"
Reindeer_compiler_name+=$Reindeer_compiler_version
Reindeer_compiler_name+=".tar.gz"
#echo "Reindeer_compiler_name = $Reindeer_compiler_name"
if [ -f "./package/$Reindeer_compiler_name" ]
then
    echo "=====================> $Reindeer_compiler_name already exists!"
else
    cd ./Reindeer_compiler;tar zcf ../package/$Reindeer_compiler_name .;cd ..
fi
sha256_Reindeer_compiler=$(sha256sum ./package/$Reindeer_compiler_name | awk '{print $1}')
size_Reindeer_compiler=$(stat -c %s ./package/$Reindeer_compiler_name)


Reindeer_upload_name="Reindeer_upload_"
Reindeer_upload_name+=$Reindeer_upload_version
Reindeer_upload_name+=".tar.gz"
#echo "Reindeer_upload_name = $Reindeer_upload_name"
if [ -f "./package/$Reindeer_upload_name" ]
then
    echo "=====================> $Reindeer_upload_name already exists!"
else
    cd ./Reindeer_upload;tar zcf ../package/$Reindeer_upload_name .;cd ..
fi
sha256_Reindeer_upload=$(sha256sum ./package/$Reindeer_upload_name | awk '{print $1}')
size_Reindeer_upload=$(stat -c %s ./package/$Reindeer_upload_name)



Rattlesnake_compiler_name="Rattlesnake_compiler_"
Rattlesnake_compiler_name+=$Rattlesnake_compiler_version
Rattlesnake_compiler_name+=".tar.gz"
if [ -f "./package/$Rattlesnake_compiler_name" ]
then
    echo "=====================> $Rattlesnake_compiler_name already exists!"
else
    cd ./Reindeer_compiler;tar zcf ../package/$Rattlesnake_compiler_name .;cd ..
fi
sha256_Rattlesnake_compiler=$(sha256sum ./package/$Rattlesnake_compiler_name | awk '{print $1}')
size_Rattlesnake_compiler=$(stat -c %s ./package/$Rattlesnake_compiler_name)


Rattlesnake_upload_name="Rattlesnake_upload_"
Rattlesnake_upload_name+=$Rattlesnake_upload_version
Rattlesnake_upload_name+=".tar.gz"
if [ -f "./package/$Rattlesnake_upload_name" ]
then
    echo "=====================> $Rattlesnake_upload_name already exists!"
else
    cd ./Rattlesnake_upload;tar zcf ../package/$Rattlesnake_upload_name .;cd ..
fi
sha256_Rattlesnake_upload=$(sha256sum ./package/$Rattlesnake_upload_name | awk '{print $1}')
size_Rattlesnake_upload=$(stat -c %s ./package/$Rattlesnake_upload_name)



hex_total_size_name="hex_total_size_"
hex_total_size_name+=$hex_total_size_version
hex_total_size_name+=".tar.gz"
#echo "hex_total_size_name = $hex_total_size_name"
if [ -f "./package/$hex_total_size_name" ]
then
    echo "=====================> $hex_total_size_name already exists!"
else
    cd ./hex_total_size;tar zcf ../package/$hex_total_size_name .;cd ..
fi
sha256_hex_total_size=$(sha256sum ./package/$hex_total_size_name | awk '{print $1}')
size_hex_total_size=$(stat -c %s ./package/$hex_total_size_name)



echo "                     "
#echo "=============================================================================="
#echo "    package_Reindeer_index.json"
#echo "=============================================================================="
echo '{'
echo '   "packages": ['
echo '     {'
echo '      "name": "PulseRain_RISCV",'
echo '      "maintainer": "PulseRain Technology, LLC",'
echo '      "email": "info@pulserain.com",'
echo '      "help": {'
echo '        "online": "http://riscv.us"'
echo '      },'
echo '      "websiteURL": "http://riscv.us",'
echo '      "platforms": ['

#############################################################################
# Reindeer
#############################################################################
echo '       {'
echo '          "name": "PulseRain Reindeer",'
echo '          "architecture": "Reindeer",'
echo "          \"version\": \"$Reindeer_version\","
echo '          "category": "Contributed",'
echo "          \"url\": \"https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/package/$Reindeer_pkg_name\","
echo "          \"archiveFileName\": \"$Reindeer_pkg_name\","
echo "          \"checksum\": \"SHA-256:$sha256_Reindeer\","
echo "          \"size\": \"$size_Reindeer\","
echo '          "help": {'
echo '            "online": "http://riscv.us"'
echo '          },'
echo '          "boards": ['
echo '            {"name": "Gnarly Grey UPDuinoV2 Board (Lattice UP5K)"},'
echo '            {"name": "STEP CYC10 Board (Intel 10CL016YU256C8G)"},'
echo '            {"name": "Efinix Trion T20 BGA256 Development Kit"},'
echo '            {"name": "Nuand bladeRF"},'
echo '            {"name": "MachXO3D Breakout"}'
echo '          ],'
echo '          "toolsDependencies": ['
echo '            {'
echo '              "packager": "PulseRain_RISCV",'
echo "              \"version\": \"$Reindeer_upload_version\","
echo '              "name": "Reindeer_upload"'
echo '            },'

echo '            {'
echo '              "packager": "PulseRain_RISCV",'
echo "              \"version\": \"$Reindeer_compiler_version\","
echo '              "name": "Reindeer_compiler"'
echo '            },'

echo '            {'
echo '              "packager": "PulseRain_RISCV",'
echo "              \"version\": \"$hex_total_size_version\","
echo '              "name": "hex_total_size"'
echo '            }'

echo '          ]'
echo '        },'       

#############################################################################
# Rattlesnake
#############################################################################
echo '       {'
echo '          "name": "PulseRain Rattlesnake",'
echo '          "architecture": "Rattlesnake",'
echo "          \"version\": \"$Rattlesnake_version\","
echo '          "category": "Contributed",'
echo "          \"url\": \"https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/package/$Rattlesnake_pkg_name\","
echo "          \"archiveFileName\": \"$Rattlesnake_pkg_name\","
echo "          \"checksum\": \"SHA-256:$sha256_Rattlesnake\","
echo "          \"size\": \"$size_Rattlesnake\","
echo '          "help": {'
echo '            "online": "http://riscv.us"'
echo '          },'
echo '          "boards": ['
echo '            {"name": "Future Electronics Creative Board (Microsemi IGLOO2)"},'
echo '            {"name": "Digilent Arty A7 (Xilinx Arty7-100T)"}'
echo '          ],'
echo '          "toolsDependencies": ['
echo '            {'
echo '              "packager": "PulseRain_RISCV",'
echo "              \"version\": \"$Rattlesnake_upload_version\","
echo '              "name": "Rattlesnake_upload"'
echo '            },'
echo '            {'
echo '              "packager": "PulseRain_RISCV",'
echo "              \"version\": \"$Rattlesnake_compiler_version\","
echo '              "name": "Rattlesnake_compiler"'
echo '            }'
echo '          ]'
echo '        }'       

echo '      ],'


#############################################################################
# Tools
#############################################################################

echo '      "tools": ['
echo '        {'
echo "          \"version\": \"$Reindeer_upload_version\","
echo '          "name": "Reindeer_upload",'
echo '          "systems": ['
echo '            {'
echo '              "host": "i686-mingw32",'
echo "              \"url\": \"https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/package/$Reindeer_upload_name\","
echo "              \"archiveFileName\": \"$Reindeer_upload_name\","
echo "              \"checksum\": \"SHA-256:$sha256_Reindeer_upload\","
echo "              \"size\": \"$size_Reindeer_upload\""
echo '            }'
echo '          ]'
echo '        },'

echo '        {'
echo "          \"version\": \"$Reindeer_compiler_version\","
echo '          "name": "Reindeer_compiler",'
echo '          "systems": ['
echo '            {'
echo '              "host": "i686-mingw32",'
echo "              \"url\": \"https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/package/$Reindeer_compiler_name\","
echo "              \"archiveFileName\": \"$Reindeer_compiler_name\","
echo "              \"checksum\": \"SHA-256:$sha256_Reindeer_compiler\","
echo "              \"size\": \"$size_Reindeer_compiler\""
echo '            }'
echo '          ]'        
echo '        },'

echo '        {'
echo "          \"version\": \"$Rattlesnake_upload_version\","
echo '          "name": "Rattlesnake_upload",'
echo '          "systems": ['
echo '            {'
echo '              "host": "i686-mingw32",'
echo "              \"url\": \"https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/package/$Rattlesnake_upload_name\","
echo "              \"archiveFileName\": \"$Rattlesnake_upload_name\","
echo "              \"checksum\": \"SHA-256:$sha256_Rattlesnake_upload\","
echo "              \"size\": \"$size_Rattlesnake_upload\""
echo '            }'
echo '          ]'
echo '        },'

echo '        {'
echo "          \"version\": \"$Rattlesnake_compiler_version\","
echo '          "name": "Rattlesnake_compiler",'
echo '          "systems": ['
echo '            {'
echo '              "host": "i686-mingw32",'
echo "              \"url\": \"https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/package/$Rattlesnake_compiler_name\","
echo "              \"archiveFileName\": \"$Rattlesnake_compiler_name\","
echo "              \"checksum\": \"SHA-256:$sha256_Rattlesnake_compiler\","
echo "              \"size\": \"$size_Rattlesnake_compiler\""
echo '            }'
echo '          ]'        
echo '        },'


echo '        {'
echo "          \"version\": \"$hex_total_size_version\","
echo '          "name": "hex_total_size",'
echo '          "systems": ['
echo '            {'
echo '              "host": "i686-mingw32",'
echo "              \"url\": \"https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/package/$hex_total_size_name\","
echo "              \"archiveFileName\": \"$hex_total_size_name\","
echo "              \"checksum\": \"SHA-256:$sha256_hex_total_size\","
echo "              \"size\": \"$size_hex_total_size\""
echo '            }'
echo '          ]'        
echo '        }'


echo '      ]'
echo '    }'
echo '  ]'
echo '}'
