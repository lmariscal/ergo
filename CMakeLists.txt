cmake_minimum_required(VERSION 3.21)

project(ergo
  VERSION 0.1.0
  DESCRIPTION "Ergo is a C++ util library which provides a set of useful types, functions, and macros for C++ development."
)

if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

option(BUILD_TESTS "Build tests" ON)

set(ERGO_MAIN_INSTALL_DIR "lib/ergo")
set(ERGO_INSTALL_DIR "${ERGO_MAIN_INSTALL_DIR}/${CMAKE_BUILD_TYPE}")
set(ERGO_INCLUDE_DIR "include/ergo")

file(GLOB_RECURSE ERGO_SOURCES
  ${PROJECT_SOURCE_DIR}/src/*.cc
)

add_library(ergo ${ERGO_SOURCES})

set_target_properties(ergo PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(ergo PUBLIC ERGO_DEBUG=1)
endif()

target_include_directories(ergo PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${ERGO_INCLUDE_DIR}>
)

target_sources(ergo PRIVATE ${ERGO_SOURCES})

# Source Files for IDEs

file(GLOB_RECURSE ERGO_HEADERS
  ${PROJECT_SOURCE_DIR}/include/**/*.hh
)

target_sources(ergo PRIVATE ${ERGO_HEADERS})

# Install

install(TARGETS ergo EXPORT ergo DESTINATION ${ERGO_INSTALL_DIR})
install(FILES ${ERGO_HEADERS} DESTINATION ${ERGO_INCLUDE_DIR})
install(FILES ${CMAKE_SOURCE_DIR}/ergo-config.cmake DESTINATION ${ERGO_MAIN_INSTALL_DIR})
install(EXPORT ergo DESTINATION "${ERGO_INSTALL_DIR}")

# Tests

if(PROJECT_IS_TOP_LEVEL AND BUILD_TESTS)
  add_subdirectory(test)
endif()
