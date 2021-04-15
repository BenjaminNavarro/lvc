cmake_minimum_required(VERSION 3.14)

project(llcTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/windows-set-path.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(llc REQUIRED VERSION 11.1.0)
  enable_testing()
endif()

find_package(GTest REQUIRED)

add_executable(
  llc_test 
  source/main.cpp
  source/SmallVectorTest.cpp
)
target_link_libraries(llc_test PRIVATE llc::llc GTest::gtest)
target_compile_features(llc_test PRIVATE cxx_std_11)

add_test(NAME llc_test COMMAND llc_test)
windows_set_path(llc_test llc::llc)
