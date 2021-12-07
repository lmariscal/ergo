file(GLOB_RECURSE ERGO_TEST_SOURCES
  ${CMAKE_SOURCE_DIR}/test/*.cc
)

add_executable(ergo_tests ${ERGO_TEST_SOURCES})

target_link_libraries(ergo_tests ergo)

# Source Files to IDEs

file(GLOB_RECURSE ERGO_TEST_HEADERS
  ${CMAKE_SOURCE_DIR}/test/*.hh
)

list(APPEND ERGO_TEST_SOURCES ${ERGO_TEST_HEADERS})

message("Test sources: ${ERGO_TEST_SOURCES}")
target_sources(ergo_tests PUBLIC ${ERGO_TEST_SOURCES})
