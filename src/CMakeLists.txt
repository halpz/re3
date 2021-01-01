set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(${REVC_AUDIO} STREQUAL "OAL")
        find_package(OpenAL REQUIRED)
        find_package(MPG123 REQUIRED)
        find_package(SndFile REQUIRED)
endif()

file(GLOB_RECURSE Sources "*.cpp" "*.h")

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.cpp)
    SET(dir_list "animation"
            "audio"
            "collision"
            "control"
            "core"
            "entities"
            "extras"
            "fakerw"
            "math"
            "modelinfo"
            "objects"
            "peds"
            "render"
            "rw"
            "save"
            "skel"
            "text"
            "vehicles"
            "weapons")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(header_list)
include_directories(${header_list})


add_executable(reVC ${Sources})
target_link_libraries(reVC librw)
target_link_libraries(reVC Threads::Threads)

if(${REVC_AUDIO} STREQUAL "OAL")
        target_link_libraries(reVC ${OPENAL_LIBRARY})
        target_link_libraries(reVC ${MPG123_LIBRARIES})
        target_link_libraries(reVC ${SNDFILE_LIBRARIES})
endif()

target_include_directories(reVC
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    )

target_compile_definitions(reVC
    PRIVATE
        "$<IF:$<CONFIG:DEBUG>,DEBUG,NDEBUG>"
    PUBLIC
        "RW_${REVC_PLATFORM}"
    )

target_compile_definitions(reVC PRIVATE LIBRW=1 AUDIO_OAL=1)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(reVC
        PRIVATE
            "-Wall"
        )
    if (NOT REVC_PLATFORM_PS2)
        target_compile_options(reVC
            PRIVATE
                "-Wextra"
                "-Wdouble-promotion"
                "-Wpedantic"
            )
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(reVC
        PUBLIC
            /wd4996 /wd4244
        )
endif()

set_target_properties(reVC
    PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        PREFIX ""
    )

if(REVC_INSTALL)
    target_include_directories(reVC
        INTERFACE
            $<INSTALL_INTERFACE:${REVC_INSTALL_INCLUDEDIR}>
        )

    install(
        TARGETS reVC
        EXPORT reVC-targets
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
endif()
