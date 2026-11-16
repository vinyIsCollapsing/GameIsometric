cmake_minimum_required(VERSION 3.16)
project(GameIsometric LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Assets embutidos no binário ---
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
add_compile_definitions(ASSETS_PATH="${ASSETS_DIR}")

# --- Includes ---
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/entities
    ${CMAKE_SOURCE_DIR}/external/glm
)

# --- Raylib ---
find_package(raylib QUIET)

if(NOT raylib_FOUND)
    message(STATUS "Raylib não encontrada no sistema — baixando via FetchContent")
    include(FetchContent)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5          
        GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable(raylib)
endif()

# --- game_core: tudo exceto main.cpp ---
file(GLOB_RECURSE GAME_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/main\\.cpp$")

add_library(game_core STATIC ${GAME_SOURCES})
target_link_libraries(game_core PUBLIC raylib)

# --- Opção SKIP_MENU (agora afeta o game_core) ---
option(SKIP_MENU "Pula o menu e vai direto para o jogo" OFF)
if(SKIP_MENU)
    target_compile_definitions(game_core PUBLIC SKIP_MENU)
endif()

# --- Executável principal ---
add_executable(game ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(game PRIVATE game_core)

# --- Testes ---
option(BUILD_TESTS "Compilar testes unitários" ON)
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cpp)
    add_executable(tests ${TEST_SOURCES})
    target_link_libraries(tests PRIVATE game_core Catch2::Catch2WithMain)
    add_test(NAME unit_tests COMMAND tests)
endif()