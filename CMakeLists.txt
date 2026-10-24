cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(Bismuth VERSION 1.0.0)

if (NOT ANDROID)
    message(FATAL_ERROR "This community port currently builds for Android only")
endif()

# Bismuth's desktop compute renderer cannot run in Geometry Dash's Android
# OpenGL ES context. This target uses the conservative GLES2 renderer backend:
# Geometry Dash remains authoritative; only explicitly safe render work is
# GPU-assisted, and unsupported visuals stay on the stock renderer.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
set(CMAKE_BUILD_TYPE Release)
target_compile_definitions(${PROJECT_NAME} PRIVATE BISMUTH_GLES_BACKEND=1)

include(FetchContent)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)
FetchContent_MakeAvailable(glm)

# Shared upstream code still names Cocos' historical Win32 GL header directly.
# This shim routes that include to Geode's Android GLES2 declarations and adds
# only the ES2 compatibility wrappers required by the mobile renderer.
target_include_directories(${PROJECT_NAME} BEFORE PRIVATE libs/android-shims)
target_include_directories(${PROJECT_NAME} PRIVATE src)

find_library(BISMUTH_GLESV2_LIBRARY GLESv2 REQUIRED)
target_link_libraries(${PROJECT_NAME} glm::glm ${BISMUTH_GLESV2_LIBRARY})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
endif()
message(STATUS "Found Geode SDK: $ENV{GEODE_SDK}")

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})
