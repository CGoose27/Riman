cmake_minimum_required(VERSION 3.10)

project(Riman)

set(EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)

find_package(LibXml2 REQUIRED)

add_library(Riman SHARED Riman.c)
add_executable(RimworldManager "Rimworld Manager.c")

include_directories(${LIBXML2_INCLUDE_DIR})

target_link_libraries(Riman ${LIBXML2_LIBRARIES})
target_link_libraries(RimworldManager Riman libgtk-3.so)
