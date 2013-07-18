cmake_minimum_required(VERSION 2.6)
project(PandoraIRCBot)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add C++11 definitions
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # Building with Clang (on OS x at least) requires specifying the use of libc++
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif()

# Add src subdirectory
# Will end up populating SOURCES with all files in the project
add_subdirectory(src)

# Include all the directories an hpp file is in
foreach(_file ${SOURCES})
    get_filename_component(_ext ${_file} EXT)
    if(${_ext} STREQUAL ".hpp")
        get_filename_component(_dir ${_file} PATH)
        list(APPEND INCLUDE ${_dir})
    endif()
endforeach()
list(APPEND INCLUDE "${PROJECT_SOURCE_DIR}/include")
list(REMOVE_DUPLICATES INCLUDE)
include_directories(${INCLUDE})

# Define sources and executbale
set(EXECUTABLE_NAME "pbirc")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# Find any version 2.X of SFML
find_package(SFML 2 REQUIRED system network)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# Detect and add Boost
# Only need to include -- No built libs are required here
find_package(Boost 1.53.0 REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()