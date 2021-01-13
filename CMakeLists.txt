cmake_minimum_required(VERSION 3.8)

project(reVC C CXX)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if(WIN32)
    set(REVC_AUDIOS "NULL" "OAL" "MSS")
else()
    set(REVC_AUDIOS "NULL" "OAL")
endif()

set(REVC_AUDIO "OAL" CACHE STRING "Audio")

set_property(CACHE REVC_AUDIO PROPERTY STRINGS ${REVC_AUDIOS})
message(STATUS "REVC_AUDIO = ${REVC_AUDIO} (choices=${REVC_AUDIOS})")
set("REVC_AUDIO_${REVC_AUDIO}" ON)
if(NOT REVC_AUDIO IN_LIST REVC_AUDIOS)
    message(FATAL_ERROR "Illegal REVC_AUDIO=${REVC_AUDIO}")
endif()

if(REVC_INSTALL)
    include(GNUInstallDirs)
    set(REVC_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/reVC")
endif()

add_subdirectory("vendor/librw")
add_subdirectory(src)

if(REVC_INSTALL)
    include(CMakePackageConfigHelpers)
    configure_package_config_file(reVC-config.cmake.in reVC-config.cmake
        INSTALL_DESTINATION "${CMAKE_INSTALL_PREFIX}"
        )
    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/reVC-config.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        )
    install(
        EXPORT reVC-targets
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        )

    include(CMakeCPack.cmake)
endif()
