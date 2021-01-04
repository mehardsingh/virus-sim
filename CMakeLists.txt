cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(virus-sim)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND CORE_SOURCE_FILES src/core/person.cc)
list(APPEND CORE_SOURCE_FILES src/core/environment.cc)

list(APPEND SOURCE_FILES    ${CORE_SOURCE_FILES}
        src/visualizer/virus-sim-app.cc
        src/visualizer/environment_painter.cc)

ci_make_app(
        APP_NAME        virus-sim-app
        CINDER_PATH     ${CINDER_PATH}
        SOURCES apps/cinder_app_main.cc ${SOURCE_FILES}
        INCLUDES        include
)