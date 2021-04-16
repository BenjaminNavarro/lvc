cmake_minimum_required(VERSION 3.14)

include(cmake/fix-paths.cmake)
include(cmake/in-source-guard.cmake)

project(
    lvc
    VERSION 11.1.0
    DESCRIPTION "Collection of C++ containers extracted from LLVM"
    HOMEPAGE_URL "https://github.com/BenjaminNavarro/lvc"
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
    lvc_lvc
    include/lvc/Compiler.h
    include/lvc/DataTypes.h
    include/lvc/ErrorHandling.h
    include/lvc/iterator_range.h
    include/lvc/lvc.h
    include/lvc/MathExtras.h
    include/lvc/MemAlloc.h
    include/lvc/SmallVector.h
    include/lvc/type_traits.h
    source/SmallVector.cpp
    source/ErrorHandling.cpp
)
add_library(lvc::lvc ALIAS lvc_lvc)

check_include_file_cxx(unistd.h HAVE_UNISTD_H)
if(HAVE_UNISTD_H)
  target_compile_definitions(lvc_lvc PUBLIC HAVE_UNISTD_H)
endif()

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(lvc_lvc PUBLIC LVC_STATIC_DEFINE)
endif()

set_target_properties(
    lvc_lvc PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME lvc
    OUTPUT_NAME lvc
)

target_include_directories(
    lvc_lvc
    ${lvc_warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/lvc>"
)

target_compile_features(lvc_lvc PUBLIC cxx_std_14)

# ---- Install rules ----

include(cmake/install-rules.cmake)

# ---- Developer mode ----

if(NOT lvc_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of lvc"
  )
endif()

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
