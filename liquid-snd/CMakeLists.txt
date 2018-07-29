cmake_minimum_required(VERSION 3.0.0)
project(liquidsnd VERSION 0.1.0)

include_directories(
    .
    C:/Users/Mark/Source/libs/libsndfile64/include
    C:/Users/Mark/Source/libs/liquid-dsp/include
)

find_library(SNDFILE NAMES "libsndfile-1"
  PATHS "C:/Users/Mark/Source/libs/bin" NO_DEFAULT_PATH)

find_library(LIQUID NAMES "libliquid"
  PATHS "C:/Users/Mark/Source/libs/bin" NO_DEFAULT_PATH)

if(NOT LIQUID)
    message(FATAL_ERROR "liquid-dsp Not Found!")
else()
    message(STATUS "LIQUID: ${LIQUID}")
endif()
  
if(NOT SNDFILE)
    message(FATAL_ERROR "libsndfile Not Found!")
else()
    message(STATUS "SNDFILE: ${SNDFILE}")
endif()


set (CMAKE_CXX_STANDARD 11)

add_executable(liquid-snd main.cpp)
target_link_libraries(liquid-snd ${LIQUID} )
target_link_libraries(liquid-snd ${SNDFILE} )
