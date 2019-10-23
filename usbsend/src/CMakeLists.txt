include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(. SRC_LIST)

add_executable(usbsend ${SRC_LIST})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
