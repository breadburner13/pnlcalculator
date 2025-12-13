cmake_minimum_required(VERSION 3.10)
project(pnl_calculator)

set(CMAKE_CXX_STANDARD 17)

# List all source files
set(SRC_FILES 
    src/main.cpp
    src/trade.cpp
    src/csv_parser.cpp
    src/position.cpp
    src/pnl_calculator.cpp
)

add_executable(pnl_calculator ${SRC_FILES})
target_include_directories(pnl_calculator PRIVATE src)