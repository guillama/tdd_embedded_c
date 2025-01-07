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

add_subdirectory(Flash)
add_subdirectory(LedDriver)
