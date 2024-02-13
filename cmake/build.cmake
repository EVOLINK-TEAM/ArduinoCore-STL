set(arduino_api_src
    ${ARDUINO_CORE_API_DIR}/CanMsg.cpp
    ${ARDUINO_CORE_API_DIR}/CanMsgRingbuffer.cpp
    ${ARDUINO_CORE_API_DIR}/Common.cpp
    ${ARDUINO_CORE_API_DIR}/IPAddress.cpp
    # ${ARDUINO_CORE_API_DIR}/PluggableUSB.cpp
    ${ARDUINO_CORE_API_DIR}/Print.cpp
    ${ARDUINO_CORE_API_DIR}/Stream.cpp
    ${ARDUINO_CORE_API_DIR}/String.cpp
)

set(arduino_core_src
    ${ARDUINO_CORE_DIR}/hooks.c
    ${ARDUINO_CORE_DIR}/HW_COUT.cpp
    ${ARDUINO_CORE_DIR}/itoa.c
    ${ARDUINO_CORE_DIR}/wiring.cpp
)
# aux_source_directory(${ARDUINO_CORE_API_DIR} arduino_api_src)
# aux_source_directory(${ARDUINO_CORE_DIR} arduino_core_src)

add_library(arduino STATIC ${arduino_api_src} ${arduino_core_src})
target_include_directories(arduino PUBLIC ${ARDUINO_CORE_DIR})
target_compile_options(arduino INTERFACE "-iquote" ${ARDUINO_CORE_API_DIR})
target_include_directories(arduino INTERFACE ${ARDUINO_CORE_API_DIR}/deprecated)