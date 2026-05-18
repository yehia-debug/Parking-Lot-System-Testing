cmake_minimum_required(VERSION 3.10)
project(ParkingLotSystem CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(parking_lot_system
    src/main.cpp
    src/ParkingRepository.cpp
    src/ParkingService.cpp
    src/ParkingConsole.cpp
)

target_include_directories(parking_lot_system PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
