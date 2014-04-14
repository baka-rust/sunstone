###
### Let's make buildfiles for Sunstone!
###
#
# Build methods:
# - dynamic libraries (UNIX & Darwin; debug)
# - static libraries (Windows; debug & release) (not implemented)
# - .app; static libraries (Darwin; release) (not implemented)
# - static libraries somehow (UNIX; release) (not implemented)

##
# Project setup
##

# Define cmake version
cmake_minimum_required (VERSION 2.6)

# Configure project
set(PROJECT_NAME "sunstone-client")
project (${PROJECT_NAME})

# Build target
set(TARGET_MODE "debug")

if(TARGET_MODE STREQUAL "debug")
	set(CMAKE_BUILD_TYPE Debug)
elseif(TARGET_MODE STREQUAL "release")
	if(APPLE)
		message(".app builds are unimplemented.")
		add_definitions(-DAPPLE_RELEASE)
	endif()

	set(CMAKE_BUILD_TYPE Release)
endif()

# Executable names
set(DEBUG_EXECUTABLE_NAME ${PROJECT_NAME}-debug)
set(RELEASE_EXECUTABLE_NAME ${PROJECT_NAME}-release)
set(EXECUTABLE_NAME ${PROJECT_NAME}-${TARGET_MODE})

# Enable c++11 on Macs
if(APPLE)
	add_definitions(-Wno-c++11-extensions) # TODO needed for windows?
endif()

# http://www.guyrutenberg.com/2014/01/05/enabling-c11-c0x-in-cmake/
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Add required modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})

##
# Grab the files to compile
##

# Glob headers and srcs
file(GLOB_RECURSE HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}" ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SRC_FILES RELATIVE "${PROJECT_SOURCE_DIR}" ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Grab their directories
foreach(CURRENT_FILE ${HEADER_FILES} ${SRC_FILES})
	get_filename_component(CURRENT_PATH ${CURRENT_FILE} PATH)
	set(INCLUDE_DIRS ${INCLUDE_DIRS} ${CURRENT_PATH})
endforeach()

## 
# Include the files we've grabed
##

include_directories(${INCLUDE_DIRS})

# TODO debug and release copies
add_executable(${EXECUTABLE_NAME} ${SRC_FILES} ${HEADER_FILES})

# Create the project directories for the files (in case we build for IDEs)
foreach(CURRENT_FILE ${HEADER_FILES} ${SRC_FILES})
	get_filename_component(CURRENT_PATH ${CURRENT_FILE} PATH)
	get_filename_component(CURRENT_NAME ${CURRENT_FILE} NAME)
	string(REPLACE "/" "\\\\" PARSED_PATH ${CURRENT_PATH})
	source_group(${PARSED_PATH} FILES ${CURRENT_FILE})
endforeach()

##
# Add SFML
##

# Determine which version of SFML to compile with
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/lib/SFML/")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	if(TARGET_MODE STREQUAL "release")
		# clang SFML on Mac for static linking release
		# TODO untested
		message("Using static SFML.")
		set(SFML_STATIC_LIBRARIES TRUE)
	endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("Using static SFML.")
	set(SFML_STATIC_LIBRARIES TRUE)
else()
	# TODO UNIX code unwritten.
endif()

# Detect and add SFML
# <https://github.com/LaurentGomila/SFML/wiki/Tutorial%3A-Build-your-SFML-project-with-CMake>
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

##
# Add non-code resources
##

# Add /resources folder
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/resources)