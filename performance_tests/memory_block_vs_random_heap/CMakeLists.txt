cmake_minimum_required(VERSION 3.10)

# Export compile commands (useful for LSP tools)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_OSX_ARCHITECTURES "arm64")

project(foo VERSION 0.5
  DESCRIPTION "bar zoo"
  LANGUAGES CXX)

include_directories(include)

# Add all source files in the src directory
set(SOURCES
    main.cpp
)

# You can do this if needed
file(GLOB SOURCES src/*.cpp)

add_executable(main ${SOURCES})

## Codelldb
# Add build type options (Debug and Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)  # Default to Debug build if no type is specified
endif()

# Enable Debug Symbols
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Building in Debug mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # Add the -g flag for debugging symbols
endif()
