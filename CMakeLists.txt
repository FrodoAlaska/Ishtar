cmake_minimum_required(VERSION 3.27)
project(Ishtar)

### CMake-specific variables ###
################################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
################################################################

### Directory variables ###
################################################################
set(EXAMPLES_DIR examples)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR})
################################################################

### All of the source files ###
################################################################
set(ISHTAR_EXAMPLES 
  # ${EXAMPLES_DIR}/dynamic_array_example.cpp
  # ${EXAMPLES_DIR}/list_example.cpp
  # ${EXAMPLES_DIR}/queue_example.cpp
  # ${EXAMPLES_DIR}/stack_example.cpp
  # ${EXAMPLES_DIR}/string_example.cpp
  # ${EXAMPLES_DIR}/hashtable_example.cpp
  ${EXAMPLES_DIR}/arena_alloc_example.cpp
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
