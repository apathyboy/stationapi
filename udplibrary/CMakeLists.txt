
if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_library(udplibrary
    hashtable.hpp
    PointerDeque.hpp
    priority.hpp
    UdpHandler.hpp
    UdpLibrary.cpp
    UdpLibrary.hpp)
