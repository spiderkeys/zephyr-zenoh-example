cmake_minimum_required(VERSION 3.20.0)

# Dependencies
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(app)

# Include
target_include_directories( app 
PRIVATE 
    ${CMAKE_BINARY_DIR}/app/include
    src
)

# Source
target_sources( app 
PRIVATE 
    src/main.c
)

# Dependencies
target_link_libraries( app 
PRIVATE 
    zenoh-pico 
)