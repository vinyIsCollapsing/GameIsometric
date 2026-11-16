#include <catch2/catch_test_macros.hpp>

#include "raylib.h"
#include "entities/Player.h"
#include "entities/PlayerState.h"


TEST_CASE("GetDirectionFromVector covers the 8 isometric directions") {
    // Mapping according to the current implementation in PlayerState.cpp
    REQUIRE(GetDirectionFromVector({ 1.0f,  0.0f}) == SOUTHEAST);
    REQUIRE(GetDirectionFromVector({ 0.0f, -1.0f}) == NORTHEAST);
    REQUIRE(GetDirectionFromVector({-1.0f,  0.0f}) == NORTHWEST);
    REQUIRE(GetDirectionFromVector({ 0.0f,  1.0f}) == SOUTHWEST);

    REQUIRE(GetDirectionFromVector({ 1.0f,  1.0f}) == SOUTH);
    REQUIRE(GetDirectionFromVector({ 1.0f, -1.0f}) == EAST);
    REQUIRE(GetDirectionFromVector({-1.0f, -1.0f}) == NORTH);
    REQUIRE(GetDirectionFromVector({-1.0f,  1.0f}) == WEST);
}

TEST_CASE("GetDirectionFromVector returns SOUTH when there is no direction") {
    REQUIRE(GetDirectionFromVector({0.0f, 0.0f}) == SOUTH);
}

TEST_CASE("GetDirectionFromVector does not confuse cardinal directions") {
    auto d1 = GetDirectionFromVector({ 1.0f,  0.0f});
    auto d2 = GetDirectionFromVector({ 0.0f, -1.0f});
    auto d3 = GetDirectionFromVector({-1.0f,  0.0f});
    auto d4 = GetDirectionFromVector({ 0.0f,  1.0f});

    REQUIRE(d1 != d2);
    REQUIRE(d1 != d3);
    REQUIRE(d1 != d4);
    REQUIRE(d2 != d3);
    REQUIRE(d2 != d4);
    REQUIRE(d3 != d4);
}