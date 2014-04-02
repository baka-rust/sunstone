cmake_minimum_required (VERSION 2.6)
project (sunstone)

add_definitions(-Wno-c++11-extensions)
set(BUILD_SHARED_LIBS TRUE)

# GLOB the files
file(GLOB_RECURSE HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}" ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SRC_FILES RELATIVE "${PROJECT_SOURCE_DIR}" ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Include all directories
foreach(CURRENT_FILE ${HEADER_FILES} ${SRC_FILES})
	get_filename_component(CURRENT_PATH ${CURRENT_FILE} PATH)
	set(INCLUDE_DIRS ${INCLUDE_DIRS} ${CURRENT_PATH})
endforeach()

include_directories(${INCLUDE_DIRS})

add_executable(Sunstone ${SRC_FILES} ${HEADER_FILES})

# Create the project directories for the files.
foreach(CURRENT_FILE ${HEADER_FILES} ${SRC_FILES})
	get_filename_component(CURRENT_PATH ${CURRENT_FILE} PATH)
	get_filename_component(CURRENT_NAME ${CURRENT_FILE} NAME)
	string(REPLACE "/" "\\\\" PARSED_PATH ${CURRENT_PATH})
	source_group(${PARSED_PATH} FILES ${CURRENT_FILE})
endforeach()

# Detect and add SFML
# <https://github.com/LaurentGomila/SFML/wiki/Tutorial%3A-Build-your-SFML-project-with-CMake>
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/lib/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_STATIC TRUE)
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(Sunstone ${SFML_LIBRARIES})

# Add resources
# maybe?
# TODO
# add_custom_command(TARGET Sunstone PRE_BUILD 
# 				   COMMAND ${CMAKE_COMMAND} -E copy_directory
# 				   ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Sunstone>/resources)