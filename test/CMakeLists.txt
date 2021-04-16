cmake_minimum_required(VERSION 3.14)

project(lvcTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/windows-set-path.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(lvc REQUIRED VERSION 11.1.0)
  enable_testing()
endif()

find_package(GTest REQUIRED)

add_executable(
  lvc_test 
  source/main.cpp
  source/SmallVectorTest.cpp
)
target_link_libraries(lvc_test PRIVATE lvc::lvc GTest::gtest)
target_compile_features(lvc_test PRIVATE cxx_std_11)

add_test(NAME lvc_test COMMAND lvc_test)
windows_set_path(lvc_test lvc::lvc)
