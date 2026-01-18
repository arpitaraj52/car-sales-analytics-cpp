# car-sales-analytics-cpp
High-performance C++17 analytics engine for global car-sales data

🛠 Build Instructions
Option 1: g++
g++ -std=gnu++17 -O2 src/main.cpp -o carSalesAnalysis

Option 2: CMake

CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(CarSalesAnalysis)

set(CMAKE_CXX_STANDARD 17)
add_executable(carSalesAnalysis src/main.cpp)

mkdir build
cd build
cmake ..
make

▶ Execution
./carSalesAnalysis world_car_sales_1m.csv
