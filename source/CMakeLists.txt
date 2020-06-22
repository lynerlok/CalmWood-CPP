##==============================================================================
## General.
##==============================================================================
cmake_minimum_required(VERSION 3.14)
project(unigine_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

##==============================================================================
## Environment.
##==============================================================================
set(UNIGINE_DOUBLE FALSE)
set(UNIGINE_SDK_PATH ${PROJECT_SOURCE_DIR}/../)
set(UNIGINE_BIN_DIR ${UNIGINE_SDK_PATH}bin)
set(UNIGINE_LIB_DIR ${UNIGINE_SDK_PATH}lib)
set(UNIGINE_INCLUDE_DIR ${UNIGINE_SDK_PATH}include)

##==============================================================================
## Dependencies.
##==============================================================================
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

set(target "CalmWood-ROS")

# Engine.
find_package(Engine REQUIRED MODULE QUIET)

file(GLOB_RECURSE UNIGINE_SOURCES "*.cpp")

add_executable(${target} ${UNIGINE_SOURCES})

target_include_directories(${target}
	PRIVATE
	${UNIGINE_INCLUDE_DIR}
	)

target_link_libraries(${target}
	PRIVATE
	Unigine::Engine
	)

target_compile_definitions(${target}
	PRIVATE
	$<$<BOOL:${UNIX}>:_LINUX>
	)

set(binary_name ${target})
string(APPEND binary_name "_x64")
set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "d")
set_target_properties(${target} PROPERTIES OUTPUT_NAME ${binary_name})

set_target_properties(${target}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${UNIGINE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${UNIGINE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${UNIGINE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${UNIGINE_BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELMINSIZE ${UNIGINE_BIN_DIR}
	)
