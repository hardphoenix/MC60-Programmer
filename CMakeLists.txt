cmake_minimum_required(VERSION 3.0.0)

set(PRJ_NAME
mtkflasher)

set(LIB_DIR
Flasher)

set(LIB_FLASHER
FLASHER)

set(LIB_SERIAL
SERIAL)

project(${PRJ_NAME} VERSION 0.1.0)


include(CTest)
enable_testing()

add_executable(${PRJ_NAME} main.c)

add_subdirectory(${LIB_DIR})

target_link_libraries(${PROJECT_NAME} ${LIB_FLASHER} ${LIB_SERIAL}) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
