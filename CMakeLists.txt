cmake_minimum_required(VERSION 3.10)
project(RaylibCrossPlatformTemplate)

set(CMAKE_CXX_STANDARD 17)

# Adiciona os headers se tiver algo em include/
include_directories(include)

# Adiciona o Raylib manualmente (Windows)
if (WIN32)
    message("Compilando para Windows")
    include_directories("C:/raylib/include")
    link_directories("C:/raylib/lib")
    set(EXTRA_LIBS raylib winmm gdi32 opengl32)
endif()

# Linux (quando alternar futuramente)
if (UNIX)
    message("Compilando para Linux")
    find_package(raylib REQUIRED)
    set(EXTRA_LIBS raylib m pthread dl rt X11)
endif()

# Pega todos os arquivos .cpp do src/
file(GLOB_RECURSE SOURCES src/*.cpp)

option(SKIP_MENU "Pula o menu e vai direto para o jogo" OFF)

if(SKIP_MENU)
    add_definitions(-DSKIP_MENU)
endif()

# Cria o executável
add_executable(game ${SOURCES})
target_link_libraries(game ${EXTRA_LIBS})
