cmake_minimum_required(VERSION 3.10)
project(GameIsometric)

set(CMAKE_CXX_STANDARD 17)

# Assets folder
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
add_compile_definitions(ASSETS_PATH="${ASSETS_DIR}")

# Headers
include_directories(
    include
    include/entities
    external/glm
)

# Raylib (Windows)
if (WIN32)
    message("Compiling for Windows")
    include_directories("C:/raylib/include")
    link_directories("C:/raylib/lib")
    set(EXTRA_LIBS raylib winmm gdi32 opengl32)
endif()

# Raylib (Linux) 
if (UNIX)
    message("Compiling for Linux")
    find_package(raylib REQUIRED)
    set(EXTRA_LIBS raylib m pthread dl rt X11)
endif()

# Featch for all .cpp files in src/
file(GLOB_RECURSE SOURCES src/*.cpp)

# Option to skip menu
option(SKIP_MENU "Skip menu" OFF)

if(SKIP_MENU)
    add_definitions(-DSKIP_MENU)
endif()

# Creates exec
add_executable(game ${SOURCES})
target_link_libraries(game ${EXTRA_LIBS})
