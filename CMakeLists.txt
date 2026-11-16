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
if(WIN32)
    message("Compilando para Windows")
    include_directories("C:/raylib/include")
    link_directories("C:/raylib/lib")
    set(RAYLIB_LIBS raylib winmm gdi32 opengl32)
elseif(UNIX)
    message("Compilando para Linux")
    find_package(raylib REQUIRED)
    set(RAYLIB_LIBS raylib m pthread dl rt X11)
endif()

# --- game_core: tudo exceto main.cpp ---
file(GLOB_RECURSE GAME_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(FILTER GAME_SOURCES EXCLUDE REGEX "/main\\.cpp$")

add_library(game_core STATIC ${GAME_SOURCES})
target_link_libraries(game_core PUBLIC ${RAYLIB_LIBS})

# --- Opção SKIP_MENU (agora afeta o game_core) ---
option(SKIP_MENU "Pula o menu e vai direto para o jogo" OFF)
if(SKIP_MENU)
    target_compile_definitions(game_core PUBLIC SKIP_MENU)
endif()

# --- Executável principal ---
add_executable(game ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(game PRIVATE game_core ${RAYLIB_LIBS})

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
    add_executable(tests
        ${CMAKE_SOURCE_DIR}/tests/testIsometric.cpp
        ${CMAKE_SOURCE_DIR}/tests/testDirection.cpp
    )
    target_link_libraries(tests PRIVATE game_core Catch2::Catch2WithMain)
    add_test(NAME unit_tests COMMAND tests)
endif()