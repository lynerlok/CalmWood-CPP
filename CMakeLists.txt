cmake_minimum_required(VERSION 3.0)
project(Test C CXX)
project(multiagentsystem)

file(GLOB_RECURSE multiagentsystem_SOURCES "src/*.cpp")
file(GLOB_RECURSE multiagentsystem_HEADERS "src/headers/*.h")

set (multiagentsystem_INCLUDE_DIRS "")

foreach (_headerFile ${multiagentsystem_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND multiagentsystem_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES multiagentsystem_INCLUDE_DIRS)

add_executable (multiagentsystem ${multiagentsystem_SOURCES})
target_include_directories(multiagentsystem PRIVATE ${multiagentsystem_INCLUDE_DIRS})

#install(TARGETS multiagentsystem RUNTIME DESTINATION bin)
