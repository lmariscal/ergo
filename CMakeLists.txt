cmake_minimum_required(VERSION 3.11)

project(ergo CXX C)

if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

option(BUILD_TESTS "Build tests" ON)

set(ERGO_VERSION_MAJOR 0 CACHE STRING "major version" FORCE)
set(ERGO_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(ERGO_VERSION_PATCH 0 CACHE STRING "patch version" FORCE)
set(ERGO_VERSION ${ERGO_VERSION_MAJOR}.${ERGO_VERSION_MINOR}.${ERGO_VERSION_PATCH} CACHE STRING "version" FORCE)

set(ERGO_MAIN_INSTALL_DIR "lib/ergo")
set(ERGO_INSTALL_DIR "${ERGO_MAIN_INSTALL_DIR}/${CMAKE_BUILD_TYPE}")
set(ERGO_INCLUDE_DIR "include/ergo")

file(GLOB_RECURSE ERGO_SOURCES
  ${CMAKE_SOURCE_DIR}/src/*.cc
)

add_library(ergo ${ERGO_SOURCES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(ergo PUBLIC ERGO_DEBUG=1)
endif()

target_include_directories(ergo PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${ERGO_INCLUDE_DIR}>
)

# Source Files for IDEs

file(GLOB_RECURSE ERGO_HEADERS
  ${CMAKE_SOURCE_DIR}/include/**/*.hh
)

list(APPEND ERGO_SOURCES ${ERGO_HEADERS})

target_sources(ergo PRIVATE ${ERGO_SOURCES})

# Install

# https://www.foonathan.net/2016/03/cmake-install/

install(TARGETS ergo EXPORT ergo DESTINATION ${ERGO_INSTALL_DIR})
install(FILES ${ERGO_HEADERS} DESTINATION ${ERGO_INCLUDE_DIR})
install(FILES ${CMAKE_SOURCE_DIR}/ergo-config.cmake DESTINATION ${ERGO_MAIN_INSTALL_DIR})
install(EXPORT ergo DESTINATION "${ERGO_INSTALL_DIR}")

# Tests

if(BUILD_TESTS AND CMAKE_BUILD_TYPE MATCHES Debug)
  add_subdirectory(test)
endif()
