set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(${RE3_AUDIO} STREQUAL "OAL")
    find_package(OpenAL REQUIRED)
    find_package(mpg123 REQUIRED)
    find_package(SndFile REQUIRED)
endif()

file(GLOB_RECURSE RE3_SOURCES "*.cpp" "*.h")

function(header_directories RETURN_LIST)
    file(GLOB_RECURSE ALL_SRCS *.h *.cpp *.c)
    set(RELDIRS)
    foreach(SRC ${ALL_SRCS})
        file(RELATIVE_PATH RELSRC "${CMAKE_CURRENT_SOURCE_DIR}" "${SRC}")
        get_filename_component(RELDIR "${RELSRC}" DIRECTORY)
        list(APPEND RELDIRS ${RELDIR})
    endforeach()
    list(REMOVE_DUPLICATES RELDIRS)
    set(${RETURN_LIST} ${RELDIRS} PARENT_SCOPE)
endfunction()

header_directories(RE3_INCLUDES)
include_directories(${RE3_INCLUDES})

add_executable(re3 ${RE3_SOURCES})
target_link_libraries(re3 PRIVATE
    librw::librw
    Threads::Threads
)

if(RE3_AUDIO STREQUAL "OAL")
    target_link_libraries(re3 PRIVATE ${OPENAL_LIBRARY})
    target_link_libraries(re3 PRIVATE MPG123::libmpg123)
    target_link_libraries(re3 PRIVATE SndFile::SndFile)
endif()

target_include_directories(re3
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${RE3_INSTALL_INCLUDEDIR}>
    )

target_compile_definitions(re3
    PRIVATE
        "$<IF:$<CONFIG:DEBUG>,DEBUG,NDEBUG>"
    )

target_compile_definitions(re3 PRIVATE LIBRW=1 AUDIO_OAL=1)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(re3
        PRIVATE
            "-Wall"
        )
    if (NOT LIBRW_PLATFORM_PS2)
        target_compile_options(re3
            PRIVATE
                "-Wextra"
                "-Wdouble-promotion"
                "-Wpedantic"
            )
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(re3
        PUBLIC
            /wd4996 /wd4244
        )
endif()

set_target_properties(re3
    PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
    )

if(RE3_INSTALL)
    install(
        TARGETS re3
        EXPORT re3-targets
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
endif()
