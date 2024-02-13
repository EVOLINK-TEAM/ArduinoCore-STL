# ArduinoCore-STL
ArduinoCore using STL only, used on the HOST.  
This repository contains the source code of the Arduino Core.Used to emulate the Arduino development environment on the host using only C++ STL without the need for a real development board.

# quick start
- Clone this repo: `git clone https://github.com/EVOLINK-TEAM/ArduinoCore-STL.git ArduinoCore-STL`
- Change directories: `cd ArduinoCore-STL/cores/arduino`
- Copy or symlink the `api` folder from the [ArduinoCore-API](https://github.com/arduino/ArduinoCore-API) repo.

## cmake
If need to build a static library, we provide some cmake tools.You need to actually replace the text `your_target_name`
``` cmake
set(ARDUINO_CORE_DIR ./ArduinoCore-STL)#Default to the cmake folder

set(ARDUINO_CORE_API_DIR ./ArduinoCore-STL/api)#Default

set(ARDUINO_CORE_API_SYMBOLINK ON)#Default.
#If specified ARDUINO_CORE_API_DIR, symbolic linking is automated (Administrator required)

add_subdirectory(./ArduinoCore-STL/cmake)
target_link_libraries(your_target_name INTERFACE arduino)

```
If you need to reference the header file in the ArduinoCore API, you need to use include quotes in your code instead of angle brackets.
```c++
#include "String.h" //right
#include <String.h> //wrong
```