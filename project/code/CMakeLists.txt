cmake_minimum_required(VERSION 3.21)
project(space-invaders)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Builds the unit test library
if(BUILD_TESTING)
	# Based on https://google.github.io/googletest/quickstart-cmake.html
	include(FetchContent)

	SET(GOOGLETEST_URL "https://codeload.github.com/google/googletest/zip/refs/tags/v1.17.0")

	if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.24")
	  FetchContent_Declare(
		googletest
		URL "${GOOGLETEST_URL}"
		DOWNLOAD_EXTRACT_TIMESTAMP true
	  )
	else()
	  FetchContent_Declare(
		googletest
		URL "${GOOGLETEST_URL}"
	  )
	endif()

	FetchContent_MakeAvailable(googletest)
endif()


# Source files (without ./src/main.cpp)
add_library(mylib STATIC
	./src/game_scene.cpp
	./src/initial_menu.cpp
)

target_link_libraries(mylib PUBLIC Qt6::Widgets)

# Build all unit tests
if(BUILD_TESTING)
	include(GoogleTest)
	enable_testing()

	file(GLOB test_files CONFIGURE_DEPENDS "./test/*.cpp" "./tests/*.c")

	foreach(test_file ${test_files})
		get_filename_component(file_name ${test_file} NAME_WE)
		set(test_name "test_${file_name}")

		add_executable(${test_name} ${test_file})
		target_link_libraries(${test_name} PRIVATE mylib gtest_main Qt6::Widgets)

		gtest_discover_tests(
			${test_name} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../ PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
		)
	endforeach()
endif()

if(NOT NO_BUILD_EXECUTABLE)
	add_executable(space-invaders ./src/main.cpp)
	target_link_libraries(space-invaders PRIVATE mylib Qt6::Widgets)
endif()
