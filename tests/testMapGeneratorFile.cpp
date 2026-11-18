#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "world/MapGenerator.h"
#include "world/TileType.h"

#include <cstdio>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace {
    fs::path MakeTempFile(const std::string& content, const std::string& name) {
        const fs::path p = fs::temp_directory_path() / name;
        std::ofstream f(p);
        f << content;
        return p;
    }
}

TEST_CASE("SaveToFile + LoadFromFile preservam o mapa") {
    MapGenerator src(12345);
    src.Generate();

    const auto path = fs::temp_directory_path() / "gameisometric_roundtrip.map";
    REQUIRE(src.SaveToFile(path.string()));

    MapGenerator dst(0);
    REQUIRE(dst.LoadFromFile(path.string()));

    REQUIRE(dst.GetWidth()  == src.GetWidth());
    REQUIRE(dst.GetHeight() == src.GetHeight());
    REQUIRE(dst.Tiles()     == src.Tiles());

    fs::remove(path);
}

TEST_CASE("LoadFromFile infers dimensions and maps (x,y) as (column,row)") {
    // Layout do arquivo (linha 0 = topo, coluna 0 = esquerda):
    //   linha 0: "..."   →  y=-1
    //   linha 1: ".#."   →  y=0   (centro)
    //   linha 2: ".,."   →  y=1
    const auto content = std::string(
        "...\n"
        ".#.\n"
        ".,.\n"
    );
    const auto path = MakeTempFile(content, "gameisometric_dim.map");

    MapGenerator g(0);
    REQUIRE(g.LoadFromFile(path.string()));
    REQUIRE(g.GetWidth()  == 3);
    REQUIRE(g.GetHeight() == 3);

    // Centro do arquivo (linha 1, coluna 1) = origem do jogo (0, 0)
    REQUIRE(g.Get(0, 0) == TILE_ROCK);

    // "x" move ao longo de colunas (horizontal no arquivo)
    REQUIRE(g.Get(1,  0) == TILE_DIRT);         // coluna 2
    REQUIRE(g.Get(-1, 0) == TILE_DIRT);         // coluna 0

    // "y" move ao longo de linhas (vertical no arquivo)
    REQUIRE(g.Get(0,  1) == TILE_DENSE_DIRT);   // linha 2
    REQUIRE(g.Get(0, -1) == TILE_DIRT);         // linha 0

    // Cantos
    REQUIRE(g.Get(-1, -1) == TILE_DIRT);        // topo-esquerda
    REQUIRE(g.Get( 1, -1) == TILE_DIRT);        // topo-direita
    REQUIRE(g.Get(-1,  1) == TILE_DIRT);        // base-esquerda
    REQUIRE(g.Get( 1,  1) == TILE_DIRT);        // base-direita

    fs::remove(path);
}

TEST_CASE("LoadFromFile rejeita caractere inválido") {
    const auto content = std::string(
        "...\n"
        "..#\n"
        "..?\n"   // '?' inválido
    );
    const auto path = MakeTempFile(content, "gameisometric_bad.map");

    MapGenerator g(0);
    REQUIRE_FALSE(g.LoadFromFile(path.string()));

    fs::remove(path);
}

TEST_CASE("LoadFromFile rejeita larguras inconsistentes") {
    const auto content = std::string(
        "...\n"
        "..\n"    // linha menor
        "...\n"
    );
    const auto path = MakeTempFile(content, "gameisometric_ragged.map");

    MapGenerator g(0);
    REQUIRE_FALSE(g.LoadFromFile(path.string()));

    fs::remove(path);
}

TEST_CASE("LoadFromFile em arquivo inexistente retorna false") {
    MapGenerator g(0);
    REQUIRE_FALSE(g.LoadFromFile("/caminho/que/nao/existe/nada.map"));
}

TEST_CASE("Colisão funciona em mapa carregado") {
    // Mapa com rocha isolada no centro
    const auto content = std::string(
        "...\n"
        ".#.\n"
        "...\n"
    );
    const auto path = MakeTempFile(content, "gameisometric_collision.map");

    MapGenerator g(0);
    REQUIRE(g.LoadFromFile(path.string()));

    REQUIRE(g.IsSolidAt(0, 0));    // centro = rock
    REQUIRE_FALSE(g.IsSolidAt(-1, 0));
    REQUIRE_FALSE(g.IsSolidAt(1, 0));
    REQUIRE_FALSE(g.IsSolidAt(0, -1));
    REQUIRE_FALSE(g.IsSolidAt(0, 1));

    fs::remove(path);
}