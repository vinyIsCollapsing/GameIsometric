#include <catch2/catch_test_macros.hpp>

#include "world/MapGenerator.h"

TEST_CASE("ToIndex maps grid coordinates to a flat index") {
    MapGenerator g(0);  // construtor inicializa dimensões padrão

    constexpr int R = MapGenerator::DEFAULT_RADIUS;
    constexpr int S = MapGenerator::DEFAULT_SIZE;

    // Cantos do mapa
    REQUIRE(g.ToIndex(-R, -R) == 0);
    REQUIRE(g.ToIndex( R,  R) == S * S - 1);

    // Centro
    REQUIRE(g.ToIndex(0, 0) == R * S + R);

    // Bordas (linhas e colunas extremas)
    REQUIRE(g.ToIndex(-R, 0) == R * S + 0);          // coluna 0, meio
    REQUIRE(g.ToIndex( R, 0) == R * S + (S - 1));    // coluna S-1, meio
    REQUIRE(g.ToIndex(0, -R) == 0 * S + R);          // linha 0, meio
    REQUIRE(g.ToIndex(0,  R) == (S - 1) * S + R);    // linha S-1, meio
}

TEST_CASE("ToIndex returns -1 for coordinates outside the grid") {
    MapGenerator g(0);
    constexpr int R = MapGenerator::DEFAULT_RADIUS;

    REQUIRE(g.ToIndex(-R - 1, 0) == -1);
    REQUIRE(g.ToIndex( R + 1, 0) == -1);
    REQUIRE(g.ToIndex(0, -R - 1) == -1);
    REQUIRE(g.ToIndex(0,  R + 1) == -1);
}

TEST_CASE("The same seed produces the same map") {
    MapGenerator a(12345);
    MapGenerator b(12345);
    a.Generate();
    b.Generate();
    REQUIRE(a.Tiles() == b.Tiles());
}

TEST_CASE("Different seeds produce different maps") {
    MapGenerator a(1);
    MapGenerator b(2);
    a.Generate();
    b.Generate();
    REQUIRE(a.Tiles() != b.Tiles());
}

TEST_CASE("Get returns TILE_DIRT outside the range") {
    MapGenerator g(42);
    g.Generate();
    constexpr int R = MapGenerator::DEFAULT_RADIUS;

    REQUIRE(g.Get(-R - 1, 0) == TILE_DIRT);
    REQUIRE(g.Get( R + 1, 0) == TILE_DIRT);
    REQUIRE(g.Get(0, -R - 1) == TILE_DIRT);
    REQUIRE(g.Get(0,  R + 1) == TILE_DIRT);
}

TEST_CASE("The northwest region has more rock than southeast") {
    MapGenerator g(12345);
    g.Generate();
    constexpr int R = MapGenerator::DEFAULT_RADIUS;

    int rockNW = 0, rockSE = 0;
    for (int y = -R; y <  0; ++y)
        for (int x = -R; x <  0; ++x)
            if (g.Get(x, y) == TILE_ROCK) ++rockNW;

    for (int y = 1; y <= R; ++y)
        for (int x = 1; x <= R; ++x)
            if (g.Get(x, y) == TILE_ROCK) ++rockSE;

    REQUIRE(rockNW > rockSE);
}

TEST_CASE("Reseed changes the map") {
    MapGenerator g(1);
    g.Generate();
    const auto first = g.Tiles();
    g.Reseed(999);
    REQUIRE(g.Tiles() != first);
}

TEST_CASE("IsSolid identifies only TILE_ROCK") {
    REQUIRE_FALSE(IsSolid(TILE_DIRT));
    REQUIRE_FALSE(IsSolid(TILE_DENSE_DIRT));
    REQUIRE(IsSolid(TILE_ROCK));
}

TEST_CASE("IsSolidAt returns false out of bounds") {
    MapGenerator g(42);
    g.Generate();
    constexpr int R = MapGenerator::DEFAULT_RADIUS;

    REQUIRE_FALSE(g.IsSolidAt(-R - 1, 0));
    REQUIRE_FALSE(g.IsSolidAt( R + 1, 0));
    REQUIRE_FALSE(g.IsSolidAt(0, -R - 1));
    REQUIRE_FALSE(g.IsSolidAt(0,  R + 1));
}