if( NOT (${ARDUINO_CORE_API_DIR} STREQUAL ${ARDUINO_CORE_DIR}/api))
    if(ARDUINO_CORE_API_SYMBOLINK EQUAL ON)
    
        if(IS_DIRECTORY ${ARDUINO_CORE_API_DIR} 
        AND EXISTS ${ARDUINO_CORE_API_DIR}/ArduinoAPI.h)
            execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
                ${ARDUINO_CORE_API_DIR}
                ${ARDUINO_CORE_DIR}/api
                RESULT_VARIABLE link_result
            )

            if(link_result EQUAL 0)
                message("Symbolic link created successfully.")
            else()
                message(WARNING "Symbolic link created error.")
            endif()
        else()
            message(WARNING "${ARDUINO_CORE_DIR} is not ArduinoCoreAPI DIRECTORY.")
        endif()
    else()
        message(WARNING "guess you need symbol link core api,but ${ARDUINO_CORE_API_SYMBOLINK} is not 'on'")
    endif()
endif()

set(ARDUINO_CORE_API_DIR ${ARDUINO_CORE_DIR}/api)