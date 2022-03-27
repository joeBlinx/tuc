add_library(tuc SHARED)
add_library(tuc::tuc ALIAS tuc)


if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL AppleClang OR CMAKE_C_COMPILER_ID STREQUAL Clang)
	target_compile_options(tuc PRIVATE -Wall -Wextra)
endif()

target_include_directories(tuc PUBLIC include PRIVATE include/tuc)
target_compile_features(tuc PUBLIC c_std_11)

set(_headers 
	include/tuc/tuc.h
	include/tuc/print.h)
target_sources(tuc PRIVATE
				tuc.c
				print.c
				${_headers}
				)
				
