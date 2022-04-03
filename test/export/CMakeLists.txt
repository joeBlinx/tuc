cmake_minimum_required(VERSION 3.12)
project(test_export)
include(GNUInstallDirs)
enable_testing()
add_executable(test_export main.c)

set(CMAKE_PREFIX_PATH ${INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake ${CMAKE_PREFIX_PATH})
set(CMAKE_MODULE_PATH ${INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake ${CMAKE_MODULE_PATH})
include(tuc)
find_package(tuc ${PROJECT_VERSION} REQUIRED)

target_link_libraries(test_export PRIVATE tuc::tuc)
tuc_discover_tests(test_export)
