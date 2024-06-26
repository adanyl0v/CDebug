if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and run \"cmake -S ${CMAKE_SOURCE_DIR} -B .\" from there")
endif()

cmake_minimum_required(VERSION 3.5)
project(CDebug VERSION 1.4.3 DESCRIPTION "A tool for displaying debugging information on the console screen" LANGUAGES C)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

set(SYSTEM_BITNESS 64)
if(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
    set(SYSTEM_BITNESS 32)
    set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -m32")
    set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -m32")
    set(CMAKE_SHARED_LINKER_FLAGS_INIT "${CMAKE_SHARED_LINKER_FLAGS_INIT} -m32")
    set(CMAKE_MODULE_LINKER_FLAGS_INIT "${CMAKE_MODULE_LINKER_FLAGS_INIT} -m32")
endif()

message(STATUS "* System: ${CMAKE_SYSTEM_NAME} x${SYSTEM_BITNESS}")
message(STATUS "* CMake build type: ${CMAKE_BUILD_TYPE}")

option(CDEBUG_COMPILE_OPTIONS_DEBUG "" STRING)
option(CDEBUG_COMPILE_OPTIONS_RELEASE "" STRING)

message(STATUS "* CMake Debug C flags: ${CDEBUG_COMPILE_OPTIONS_DEBUG}")
message(STATUS "* CMake Release C flags: ${CDEBUG_COMPILE_OPTIONS_RELEASE}")

add_library(cdebug
    src/cdebug_args.c
    src/cdebug_print.c
    src/cdebug_last.c
)

target_compile_options(cdebug PRIVATE 
	"$<$<CONFIG:Debug>:${CDEBUG_COMPILE_OPTIONS_DEBUG}>"
	"$<$<CONFIG:Release>:${CDEBUG_COMPILE_OPTIONS_RELEASE}>"
)

set_target_properties(cdebug PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
)

include(GenerateExportHeader)
generate_export_header(cdebug
    BASE_NAME CDEBUG
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/cdebug_export.h
    EXPORT_MACRO_NAME CDEBUG_API
    NO_EXPORT_MACRO_NAME CDEBUG_API_PRIVATE
)

target_include_directories(cdebug
    PUBLIC $<INSTALL_INTERFACE:/usr/local/include/>
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${CMAKE_PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS cdebug
    EXPORT ${CMAKE_PROJECT_NAME}-export
    LIBRARY DESTINATION /usr/local/lib/
    ARCHIVE DESTINATION /usr/local/lib/
)

install(
    EXPORT ${CMAKE_PROJECT_NAME}-export
    FILE ${CMAKE_PROJECT_NAME}Targets.cmake
    NAMESPACE ${CMAKE_PROJECT_NAME}::
    DESTINATION /usr/local/lib/cmake/${CMAKE_PROJECT_NAME}/
)

set(CDEBUG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
install(
    FILES
    ${CDEBUG_INCLUDE_DIR}/cdebug_export.h
    ${CDEBUG_INCLUDE_DIR}/cdebug_errno_t.h
    ${CDEBUG_INCLUDE_DIR}/cdebug_args_t.h
    ${CDEBUG_INCLUDE_DIR}/cdebug.h
    DESTINATION /usr/local/include/${CMAKE_PROJECT_NAME}/
)

install(
    FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${CMAKE_PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
    DESTINATION /usr/local/lib/cmake/${CMAKE_PROJECT_NAME}/
)