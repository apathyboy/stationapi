# don't allow in-source project generation
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(WARNING "\n\nCMake generation is not allowed within the source directory!\n")
    message(STATUS "Cancelling CMake and cleaning up source tree...")
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/CMakeFiles")
    math(EXPR Crash 0/0)
    message(FATAL_ERROR "CMake should have crashed - this is a failsafe in case the call used to trigger the crash gets fixed.")
endif()

cmake_minimum_required(VERSION 2.8)

project(swgchat CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(ModernCpp)

add_definitions(-DBOOST_ALL_NO_LIB)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(SQLite3 REQUIRED)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
endif ()

add_subdirectory(externals)
add_subdirectory(src)

configure_file(extras/logger.cfg.dist src/logger.cfg COPYONLY)
configure_file(extras/swgchat.cfg.dist src/swgchat.cfg COPYONLY)
