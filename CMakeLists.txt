cmake_minimum_required (VERSION 4.3.2 FATAL_ERROR)

project(
    nrlmsise00
    LANGUAGES CXX
    VERSION 1.0.0
)

# Compiler options
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}")

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type is set to ${CMAKE_BUILD_TYPE}")

# General testing information
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(CTest)

add_library(
    ${PROJECT_NAME}
    SHARED
        nrlmsise00/Nrlmsise00.hpp
        nrlmsise00/Nrlmsise00.cpp
)
add_library(nrlmsise00::nrlmsise00 ALIAS ${PROJECT_NAME})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE 1
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        nrlmsise00/math.cpp
        nrlmsise00/data.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

install(
    TARGETS  ${PROJECT_NAME}
    LIBRARY  DESTINATION lib
    ARCHIVE  DESTINATION lib
    INCLUDES DESTINATION include
)

install(
    DIRECTORY nrlmsise00/ 
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

# Unit tests (optional, controlled by BUILD_TESTING, default OFF)
option(BUILD_TESTING "Build unit tests" OFF)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# Python bindings (optional, requires pybind11, default OFF)
option(BUILD_PYTHON "Build Python bindings" OFF)
if(BUILD_PYTHON)
    add_subdirectory(python)
endif()

# Doxygen documentation
option(BUILD_DOCS "Build Doxygen documentation" OFF)
if (BUILD_DOCS)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        include(UseDoxygenDoc)
        add_doxygen_doc(
            BUILD_DIR
                ${CMAKE_CURRENT_BINARY_DIR}/docs
            DOXY_FILE
                ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
            TARGET_NAME
                docs
            COMMENT
                "HTML Documentation"
        )
    endif()
endif()