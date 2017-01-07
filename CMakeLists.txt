# don't allow in-source project generation
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(WARNING "\n\nCMake generation is not allowed within the source directory!\n")
    message(STATUS "Cancelling CMake and cleaning up source tree...")
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/CMakeFiles")
    math(EXPR Crash 0/0)
    message(FATAL_ERROR "CMake should have crashed - this is a failsafe in case the call used to trigger the crash gets fixed.")
endif()

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(stationapi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(ModernCpp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (EXISTS "${PROJECT_SOURCE_DIR}/externals/udplibrary/CMakeLists.txt")
    message(STATUS "Detected udplibrary")
    set(HAVE_UDPLIBRARY 1)
else()
    message(FATAL_ERROR "udplibrary required... copy from swg source to the externals directory")
endif()

add_definitions(-DBOOST_ALL_NO_LIB)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(SQLite3 REQUIRED)

add_subdirectory(externals)
add_subdirectory(src)
add_subdirectory(tests)

install(FILES
    extras/logger.cfg.dist
    DESTINATION etc/stationapi
    RENAME logger.cfg)

install(FILES
    extras/swgchat.cfg.dist
    DESTINATION etc/stationapi
    RENAME swgchat.cfg)

install(FILES
    extras/stationchat.db.dist
    DESTINATION var/stationapi
    RENAME stationchat.db)

install(FILES
    extras/init_database.sql
    DESTINATION share/stationapi)
