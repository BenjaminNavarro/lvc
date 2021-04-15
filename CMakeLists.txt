cmake_minimum_required(VERSION 3.14)

include(cmake/fix-paths.cmake)
include(cmake/in-source-guard.cmake)

project(
    llc
    VERSION 11.1.0
    DESCRIPTION "Collection of C++ containers extracted from LLVM"
    HOMEPAGE_URL "https://github.com/BenjaminNavarro/llc"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)
include(CheckIncludeFileCXX)

# ---- Declare library ----

if(MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

add_library(
    llc_llc
    include/llc/Compiler.h
    include/llc/DataTypes.h
    include/llc/ErrorHandling.h
    include/llc/iterator_range.h
    include/llc/llc.h
    include/llc/MathExtras.h
    include/llc/MemAlloc.h
    include/llc/SmallVector.h
    include/llc/type_traits.h
    source/SmallVector.cpp
    source/ErrorHandling.cpp
)
add_library(llc::llc ALIAS llc_llc)

check_include_file_cxx(unistd.h HAVE_UNISTD_H)
if(HAVE_UNISTD_H)
  target_compile_definitions(llc_llc PUBLIC HAVE_UNISTD_H)
endif()

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(llc_llc PUBLIC LLC_STATIC_DEFINE)
endif()

set_target_properties(
    llc_llc PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME llc
    OUTPUT_NAME llc
)

target_include_directories(
    llc_llc
    ${llc_warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/llc>"
)

target_compile_features(llc_llc PUBLIC cxx_std_14)

# ---- Install rules ----

include(cmake/install-rules.cmake)

# ---- Developer mode ----

if(NOT llc_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of llc"
  )
endif()

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
