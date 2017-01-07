include_directories(${PROJECT_SOURCE_DIR}/externals/catch
    ${PROJECT_SOURCE_DIR}/src)

add_executable(stationapi_tests
    main.cpp
    
    stationapi/Serialization_Tests.cpp
    stationapi/StringUtils_Tests.cpp)

target_link_libraries(stationapi_tests
    stationapi)
