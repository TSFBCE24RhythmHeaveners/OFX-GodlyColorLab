cmake_minimum_required(VERSION 3.15)
project(ColorCorrectionPlugin VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find OpenFX SDK (you'll need to set OFX_PATH environment variable)
if(NOT DEFINED OFX_PATH)
    if(DEFINED ENV{OFX_PATH})
        set(OFX_PATH $ENV{OFX_PATH})
    else()
        message(FATAL_ERROR "OpenFX SDK path not found. Set OFX_PATH environment variable.")
    endif()
endif()

# OpenFX headers
set(OFX_INCLUDE_DIR "${OFX_PATH}/include")

if(NOT EXISTS "${OFX_INCLUDE_DIR}")
    message(FATAL_ERROR "OpenFX headers not found at ${OFX_INCLUDE_DIR}")
endif()

# Plugin source files
set(PLUGIN_SOURCES
    src/PluginMain.cpp
    src/ColorCorrectionPlugin.cpp
)

# Create the plugin library
add_library(ColorCorrection SHARED ${PLUGIN_SOURCES})

# Include directories
target_include_directories(ColorCorrection PRIVATE
    ${OFX_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Platform-specific settings
if(WIN32)
    set_target_properties(ColorCorrection PROPERTIES SUFFIX ".ofx")
    target_compile_definitions(ColorCorrection PRIVATE WINDOWS)
elseif(APPLE)
    set_target_properties(ColorCorrection PROPERTIES
        SUFFIX ".ofx"
        BUNDLE ON
    )
    target_compile_definitions(ColorCorrection PRIVATE MACOS)
else()
    set_target_properties(ColorCorrection PROPERTIES SUFFIX ".ofx.so")
    target_compile_definitions(ColorCorrection PRIVATE LINUX)
endif()

# Compiler flags
if(MSVC)
    target_compile_options(ColorCorrection PRIVATE /W4 /O2)
else()
    target_compile_options(ColorCorrection PRIVATE -Wall -Wextra -O2)
endif()
