cmake_minimum_required(VERSION 3.12)
project(TUC
VERSION 0.0.1)
enable_testing()
include(CPack.cmake)
include(CPack)
add_subdirectory(test)
add_subdirectory(src)
