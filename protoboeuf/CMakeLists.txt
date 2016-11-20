cmake_minimum_required(VERSION 2.8)
project(protoboeuf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

file(
        GLOB_RECURSE
        ${PROJECT_NAME}_SRCS
        include/network/utils/INetworkUtil.hh
        include/network/utils/NetworkInteger.hh
        include/network/utils/NetworkString.hh
        include/network/utils/NetworkVector.hh
        include/network/packet/IPacket.hh
        include/network/packet/APacket.hh
        include/network/packet/APacketData.hh
        src/network/utils/NetworkInteger.cpp
        src/network/utils/NetworkString.cpp
        src/network/utils/NetworkVector.cpp
        src/network/packet/APacket.cpp
        src/network/packet/APacketData.cpp
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

if (PROTOBOEUF_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(PROTOBOEUF_TESTS)