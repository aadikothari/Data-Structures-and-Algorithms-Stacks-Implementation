cmake_minimum_required(VERSION 3.5)
project(P3_2 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build the image library
ADD_SUBDIRECTORY(lib)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

set(NODE_SOURCE
  Node.hpp)

set(STACK_SOURCE
  Stack.hpp)

set(REGION_SOURCE
  region_grower.hpp region_grower.cpp)

set(SOURCE ${STACK_SOURCE} ${NODE_SOURCE} ${REGION_SOURCE})

add_executable(student-tests catch.hpp student_catch.cpp ${SOURCE} student_tests.cpp)
TARGET_LINK_LIBRARIES(student-tests image)
add_executable(fillregion ${SOURCE} fillregion.cpp)
TARGET_LINK_LIBRARIES(fillregion image)
add_executable (compare compare.cpp)
TARGET_LINK_LIBRARIES(compare image)

# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
   region_grower.hpp region_grower.cpp fillregion.cpp student_tests.cpp
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
