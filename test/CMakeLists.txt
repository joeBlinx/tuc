add_executable(test_tuc)

target_link_libraries(test_tuc PRIVATE tuc::tuc)
target_sources(test_tuc PRIVATE main.c)
