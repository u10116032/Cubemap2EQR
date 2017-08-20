cmake_minimum_required(VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project(Cubemap2Eqr)

SET(EXECUTABLE_OUTPUT_PATH ./Build/)
file(GLOB SOURCES src/*.cpp src/*.hpp)

find_package(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

add_executable(Cubemap2Eqr_exe ${SOURCES})
TARGET_LINK_LIBRARIES(Cubemap2Eqr_exe ${OpenCV_LIBS})
