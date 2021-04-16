include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(
    DIRECTORY
    "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT lvc_Development
)

install(
    TARGETS lvc_lvc
    EXPORT lvcTargets
    RUNTIME #
    COMPONENT lvc_Runtime
    LIBRARY #
    COMPONENT lvc_Runtime
    NAMELINK_COMPONENT lvc_Development
    ARCHIVE #
    COMPONENT lvc_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    lvcConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
)

set(
    lvc_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/lvc"
    CACHE STRING "CMake package config location relative to the install prefix"
)

mark_as_advanced(lvc_INSTALL_CMAKEDIR)

install(
    FILES
    "${PROJECT_SOURCE_DIR}/cmake/lvcConfig.cmake"
    "${PROJECT_BINARY_DIR}/lvcConfigVersion.cmake"
    DESTINATION "${lvc_INSTALL_CMAKEDIR}"
    COMPONENT lvc_Development
)

install(
    EXPORT lvcTargets
    NAMESPACE lvc::
    DESTINATION "${lvc_INSTALL_CMAKEDIR}"
    COMPONENT lvc_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
