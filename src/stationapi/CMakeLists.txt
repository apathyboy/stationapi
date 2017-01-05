
add_library(stationapi
    Node.hpp
    NodeClient.cpp
    NodeClient.hpp
    Serialization.hpp
    SQLite3.hpp
    StreamUtils.cpp
    StreamUtils.hpp
    StringUtils.cpp
    StringUtils.hpp)

target_include_directories(stationapi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/externals/catch
    ${PROJECT_SOURCE_DIR}/externals/easyloggingpp
    ${PROJECT_SOURCE_DIR}/externals/udplibrary
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIR})

add_executable(stationapi_tests
    Serialization_Tests.cpp
    StringUtils_Tests.cpp)

target_link_libraries(stationapi_tests
    stationapi)
