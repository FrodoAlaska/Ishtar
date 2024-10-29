cmake_minimum_required(VERSION 3.27)
project(Ishtar)

### CMake-specific variables ###
################################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
################################################################

### Directory variables ###
################################################################
set(SRC_DIR src)
set(INCLUDE_DIR src)
################################################################

### All of the source files ###
################################################################
set(ISHTAR_SOURCES 
  # Core
  ${SRC_DIR}/main.cpp
)
################################################################

### Executable ###
################################################################
add_executable(${PROJECT_NAME} ${ISHTAR_SOURCES})
################################################################

### Adding last touches ###
################################################################
target_compile_options(${PROJECT_NAME} PUBLIC -lm -Wall)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PUBLIC BEFORE ${INCLUDE_DIR})
################################################################
