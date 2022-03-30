add_library(tuc SHARED)
add_library(tuc::tuc ALIAS tuc)

include(GNUInstallDirs)
include(GenerateExportHeader)
generate_export_header(tuc EXPORT_FILE_NAME tuc/tuc_export.h)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL AppleClang OR CMAKE_C_COMPILER_ID STREQUAL Clang)
	target_compile_options(tuc PRIVATE -Wall -Wextra)
	if(CMAKE_C_COMPILER_ID STREQUAL Clang)
		target_link_options(tuc PRIVATE -stdlib=libstdc)
	endif()
endif()

target_include_directories(tuc 
					PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
						   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
					PRIVATE include/tuc)
target_compile_features(tuc PUBLIC c_std_11)
target_compile_definitions(tuc PRIVATE tuc_EXPORTS)

set(_headers 
	${CMAKE_CURRENT_BINARY_DIR}/tuc/tuc_export.h
	include/tuc/tuc.h
	include/tuc/print.h
	include/tuc/allocator.h)

set_target_properties(tuc PROPERTIES
				PUBLIC_HEADER "${_headers}"
				VERSION ${PROJECT_VERSION}
				VISIBILITY_INLINES_HIDDEN YES
				C_VISIBILITY_PRESET hidden
				)
target_sources(tuc PRIVATE
				tuc.c
				print.c
				allocator.c
				${_headers}
				)
install(TARGETS tuc
		EXPORT tucTargets
			RUNTIME DESTINATION lib
			PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tuc
			)
install(EXPORT  tucTargets
		FILE tucTargets.cmake
		NAMESPACE tuc::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
			${CMAKE_CURRENT_BINARY_DIR}/tucConfig.cmake
			INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/tucConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
	)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tucConfig.cmake 
				${CMAKE_CURRENT_BINARY_DIR}/tucConfigVersion.cmake
				DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
