cmake_minimum_required(VERSION 3.17)
project(figure_counter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_COLOR_MAKEFILE OFF)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(test.exe PUBLIC external)

set(SOURCES
  test_main.cpp

  lib/figure_counter.cpp

  lib/figure_counter_test.cpp
)

set(HEADERS
  lib/figure_counter.hpp
  lib/grid.hpp
)

add_executable(test.exe ${SOURCES} ${HEADERS})
