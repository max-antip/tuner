cmake_minimum_required(VERSION 3.6)
project(sound_learning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

INCLUDE_DIRECTORIES(/usr/local/include ../)
LINK_DIRECTORIES(/usr/local/lib)


set(SOURCE_FILES main.cpp)
add_executable(sound_learning ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(sound_learning pulse pulse-simple)
TARGET_LINK_LIBRARIES(sound_learning openal openal)
