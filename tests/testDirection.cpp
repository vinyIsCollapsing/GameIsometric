#include <catch2/catch_test_macros.hpp>

#include "raylib.h"
#include "entities/Player.h"
#include "entities/PlayerState.h"    // traz Direction8 + declaração de GetDirectionFromVector


TEST_CASE("GetDirectionFromVector cobre as 8 direções isométricas") {
    // Mapeamento conforme implementação atual em PlayerState.cpp
    REQUIRE(GetDirectionFromVector({ 1.0f,  0.0f}) == SOUTHEAST);
    REQUIRE(GetDirectionFromVector({ 0.0f, -1.0f}) == NORTHEAST);
    REQUIRE(GetDirectionFromVector({-1.0f,  0.0f}) == NORTHWEST);
    REQUIRE(GetDirectionFromVector({ 0.0f,  1.0f}) == SOUTHWEST);

    REQUIRE(GetDirectionFromVector({ 1.0f,  1.0f}) == SOUTH);
    REQUIRE(GetDirectionFromVector({ 1.0f, -1.0f}) == EAST);
    REQUIRE(GetDirectionFromVector({-1.0f, -1.0f}) == NORTH);
    REQUIRE(GetDirectionFromVector({-1.0f,  1.0f}) == WEST);
}

TEST_CASE("GetDirectionFromVector cai em SOUTH quando não há direção") {
    REQUIRE(GetDirectionFromVector({0.0f, 0.0f}) == SOUTH);
}

TEST_CASE("GetDirectionFromVector não confunde eixos cardeais") {
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