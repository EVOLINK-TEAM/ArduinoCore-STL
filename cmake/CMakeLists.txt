#default settings
set(ARDUINO_CORE_TOOL_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT DEFINED ARDUINO_CORE_DIR)
    set(ARDUINO_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cores/Arduino)#ARDUINO_CORE
endif()

if(NOT DEFINED ARDUINO_CORE_API_SYMBOLINK)
    set(ARDUINO_CORE_API_SYMBOLINK ON)
endif()

if(NOT DEFINED ARDUINO_CORE_API_DIR)
    set(ARDUINO_CORE_API_DIR ${ARDUINO_CORE_DIR}/api)#ARDUINO_CORE_API    
endif()

#symbol link
include(${ARDUINO_CORE_TOOL_PATH}/symbol_link.cmake)

#check cores
if(NOT EXISTS ${ARDUINO_CORE_DIR}/Arduino.h)
    message(FATAL_ERROR "can not find the ArduinoCore")
endif()

if(NOT EXISTS ${ARDUINO_CORE_API_DIR}/ArduinoAPI.h)
    message(FATAL_ERROR "can not find the ArduinoCoreAPI")
endif()

#build
include(${ARDUINO_CORE_TOOL_PATH}/build.cmake)

target_compile_definitions(arduino PUBLIC HOST)
target_compile_definitions(arduino PUBLIC ARDUINO=100)