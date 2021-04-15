include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(
    DIRECTORY
    "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT llc_Development
)

install(
    TARGETS llc_llc
    EXPORT llcTargets
    RUNTIME #
    COMPONENT llc_Runtime
    LIBRARY #
    COMPONENT llc_Runtime
    NAMELINK_COMPONENT llc_Development
    ARCHIVE #
    COMPONENT llc_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    llcConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
)

set(
    llc_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/llc"
    CACHE STRING "CMake package config location relative to the install prefix"
)

mark_as_advanced(llc_INSTALL_CMAKEDIR)

install(
    FILES
    "${PROJECT_SOURCE_DIR}/cmake/llcConfig.cmake"
    "${PROJECT_BINARY_DIR}/llcConfigVersion.cmake"
    DESTINATION "${llc_INSTALL_CMAKEDIR}"
    COMPONENT llc_Development
)

install(
    EXPORT llcTargets
    NAMESPACE llc::
    DESTINATION "${llc_INSTALL_CMAKEDIR}"
    COMPONENT llc_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
