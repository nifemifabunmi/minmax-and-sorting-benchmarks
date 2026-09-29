cmake_minimum_required(VERSION 3.16)
project(minmax_sorting_benchmarks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
    add_compile_options(/W4 /O2)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

add_library(algos STATIC
    src/minmax.cpp
    src/sorts.cpp
    src/median.cpp
)
target_include_directories(algos PUBLIC src)

add_executable(bench src/main.cpp src/benchmark.cpp)
target_link_libraries(bench PRIVATE algos)

enable_testing()
add_executable(test_correctness tests/test_correctness.cpp)
target_link_libraries(test_correctness PRIVATE algos)
add_test(NAME correctness COMMAND test_correctness)