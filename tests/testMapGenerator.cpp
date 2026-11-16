#include <catch2/catch_test_macros.hpp>

#include "world/MapGenerator.h"

TEST_CASE("ToIndex mapeia [-RADIUS, RADIUS] para [0, SIZE)") {
    REQUIRE(MapGenerator::ToIndex(-MapGenerator::RADIUS) == 0);
    REQUIRE(MapGenerator::ToIndex(0)                     == MapGenerator::RADIUS);
    REQUIRE(MapGenerator::ToIndex(MapGenerator::RADIUS)  == MapGenerator::SIZE - 1);
}

TEST_CASE("Mesma seed produz o mesmo mapa") {
    MapGenerator a(12345);
    MapGenerator b(12345);
    a.Generate();
    b.Generate();
    REQUIRE(a.Tiles() == b.Tiles());
}

TEST_CASE("Seeds diferentes produzem mapas diferentes") {
    MapGenerator a(1);
    MapGenerator b(2);
    a.Generate();
    b.Generate();
    REQUIRE(a.Tiles() != b.Tiles());
}

TEST_CASE("Get retorna TILE_DIRT fora da faixa") {
    MapGenerator g(42);
    g.Generate();
    REQUIRE(g.Get(-MapGenerator::RADIUS - 1, 0) == TILE_DIRT);
    REQUIRE(g.Get( MapGenerator::RADIUS + 1, 0) == TILE_DIRT);
    REQUIRE(g.Get(0, -MapGenerator::RADIUS - 1) == TILE_DIRT);
    REQUIRE(g.Get(0,  MapGenerator::RADIUS + 1) == TILE_DIRT);
}

TEST_CASE("Região noroeste tem mais rocha que a sudeste") {
    MapGenerator g(12345);
    g.Generate();

    int rockNW = 0, rockSE = 0;
    for (int y = -MapGenerator::RADIUS; y <  0; ++y)
        for (int x = -MapGenerator::RADIUS; x <  0; ++x)
            if (g.Get(x, y) == TILE_ROCK) ++rockNW;

    for (int y = 1; y <= MapGenerator::RADIUS; ++y)
        for (int x = 1; x <= MapGenerator::RADIUS; ++x)
            if (g.Get(x, y) == TILE_ROCK) ++rockSE;

    REQUIRE(rockNW > rockSE);
}

TEST_CASE("Reseed muda o mapa") {
    MapGenerator g(1);
    g.Generate();
    const auto first = g.Tiles();
    g.Reseed(999);
    REQUIRE(g.Tiles() != first);
}