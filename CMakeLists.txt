cmake_minimum_required(VERSION 3.24)
project(pipes)

set(CMAKE_CXX_STANDARD 17)

add_executable(processM processM.cpp)
add_executable(processA processA.cpp)
add_executable(processP processP.cpp)
add_executable(processS processS.cpp)
add_executable(pipes main.cpp)
