cmake_minimum_required(VERSION 3.27)
project(Ishtar)

### CMake-specific variables ###
################################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
################################################################

### Directory variables ###
################################################################
set(SRC_DIR src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR})
################################################################

### All of the source files ###
################################################################
set(ISHTAR_EXAMPLES 
  # examples/dynamic_array_example.cpp
  # examples/list_example.cpp
  # examples/queue_example.cpp
  # examples/stack_example.cpp
  examples/string_example.cpp
)
################################################################

### Executable ###
################################################################
add_executable(${PROJECT_NAME} ${ISHTAR_EXAMPLES})
################################################################

### Adding last touches ###
################################################################
target_compile_options(${PROJECT_NAME} PUBLIC -lm -Wall)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PUBLIC BEFORE ${INCLUDE_DIR})
################################################################
