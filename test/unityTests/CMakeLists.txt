add_subdirectory(Flash)
add_subdirectory(LedDriver)

add_library(Unity STATIC
${UNITY_PATH}/src/unity.c
)

target_include_directories(Unity PUBLIC
  ${UNITY_PATH}/src
)

add_library(cmock STATIC
    ${CMOCK_PATH}/src/cmock.c
)

target_include_directories(cmock PRIVATE
  ${CMOCK_PATH}/src
)

target_include_directories(cmock PUBLIC
  ${UNITY_PATH}/src
  ${CMOCK_PATH}/src/
)

add_custom_command(TARGET cmock PRE_BUILD
  COMMAND ruby ${CMOCK_PATH}/lib/cmock.rb 
  ARGS -o${CMAKE_CURRENT_LIST_DIR}/maconfig.yml 
  ARGS ${CMAKE_SOURCE_DIR}/src/Flash/IO.h
)