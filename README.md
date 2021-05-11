# Arduino_RISCV_IDE
PulseRain RISC-V Board Support Package for Arduino IDE

## Install Arduino IDE
On Windows 10, the Arduino IDE can be installed directly from Microsoft Store. For other platform, it can be downloaded from [Arduino Website](https://www.arduino.cc/en/software)
## Install this Board Support Package

* Launch the Arduino IDE, and open Menu File / Preferences

  ![Preference Menu](https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/docs/picture/arduino_preference.png "Preference Menu")
  

* Add "https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/package_pulserain.com_index.json" to **Additional Boards Manager URLs**

  ![Add JSON File](https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/docs/picture/arduino_json.png "Add JSON File")


* Open **Board Manager** under Menu Tools / Board / Board Manager...

  ![Board Manager](https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/docs/picture/arduino_board_manager.png "Board Manager")
  
* Type in "PulseRain" in the Search Box to find relevant Boards and install

  ![Search PulseRain](https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/docs/picture/arduino_board_pulserain.png "Search PulseRain")
  
## Use the Board
  1. Connect the board to PC through USB cable
  2. Select the board from Menu Tools / Board / ...
  3. Select the correspondent COM port for the Board
     ![COM Port](https://github.com/PulseRain/Arduino_RISCV_IDE/raw/master/docs/picture/arduino_com.png "COM Port")
  4. Create new sketch, use CTRL + U to compile and program the board
