cmake_minimum_required(VERSION 3.15)
project(SynapseEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

INCLUDE_DIRECTORIES(include)

file(GLOB_RECURSE SOURCES "src/*.cpp" )
add_executable(synapse ${SOURCES})
target_compile_options(synapse PRIVATE -Wall -Wextra -Wpedantic)

