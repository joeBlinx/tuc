add_executable(test_tuc)

target_link_libraries(test_tuc PRIVATE tuc::tuc)
add_test(NAME test_tuc COMMAND test_tuc)
target_sources(test_tuc PRIVATE main.c)
