cmake_minimum_required(VERSION 3.12)
project(test_export)
add_executable(test_export main.c)

set(CMAKE_PREFIX_PATH ${INSTALL_DIR}/lib64/cmake ${CMAKE_PREFIX_PATH})
find_package(tuc ${PROJECT_VERSION} REQUIRED)

target_link_libraries(test_export PRIVATE tuc::tuc)
