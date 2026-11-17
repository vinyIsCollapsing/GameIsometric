#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "utils/Collision.h"

using Catch::Approx;

namespace {
    constexpr float EPS = 1e-4f;

    // Reusable scenarios
    auto AllWalkable = [](int, int) { return true; };
    auto AllSolid    = [](int, int) { return false; };
}

TEST_CASE("TryMove moves freely when the destination is walkable") {
    auto p = Collision::TryMove({0.0f, 0.0f}, {0.5f, 0.5f}, AllWalkable);
    REQUIRE(p.x == Approx(0.5f).margin(EPS));
    REQUIRE(p.y == Approx(0.5f).margin(EPS));
}

TEST_CASE("TryMove blocks both axes when the destination is solid") {
    auto p = Collision::TryMove({0.0f, 0.0f}, {0.5f, 0.5f}, AllSolid);
    REQUIRE(p.x == Approx(0.0f).margin(EPS));
    REQUIRE(p.y == Approx(0.0f).margin(EPS));
}

TEST_CASE("TryMove slides along a vertical wall (X blocked, Y free)") {
    // Wall: any tile with x >= 1 is solid; everything else is free.
    auto isWalkable = [](int x, int) { return x < 1; };

    auto p = Collision::TryMove({0.3f, 0.3f}, {0.4f, 0.4f}, isWalkable);
    REQUIRE(p.x == Approx(0.3f).margin(EPS));   // X blocked
    REQUIRE(p.y == Approx(0.7f).margin(EPS));   // Y free
}

TEST_CASE("TryMove slides along a horizontal wall (Y blocked, X free)") {
    auto isWalkable = [](int, int y) { return y < 1; };
    
    auto p = Collision::TryMove({0.3f, 0.3f}, {0.4f, 0.4f}, isWalkable);
    REQUIRE(p.x == Approx(0.7f).margin(EPS));   // X free
    REQUIRE(p.y == Approx(0.3f).margin(EPS));   // Y blocked
}

TEST_CASE("TryMove does not cut through a diagonal corner") {
    // Solid only at tile (1, 1). Player tries to move diagonally to (0.5, 0.5).
    auto isWalkable = [](int x, int y) { return !(x == 1 && y == 1); };

    auto p = Collision::TryMove({0.4f, 0.4f}, {0.2f, 0.2f}, isWalkable);
    // X: new = 0.6 → lround(0.6) = 1, y=0.4 → lround=0 → tile (1,0) free → X accepted
    // Y: new = 0.6 → tile (1,1) solid → Y rejected
    REQUIRE(p.x == Approx(0.6f).margin(EPS));
    REQUIRE(p.y == Approx(0.4f).margin(EPS));
}

TEST_CASE("TryMove does not change position when both axes are blocked") {
    auto isWalkable = [](int, int) { return false; };

    auto p = Collision::TryMove({1.5f, 2.5f}, {-0.3f, 0.3f}, isWalkable);
    REQUIRE(p.x == Approx(1.5f).margin(EPS));
    REQUIRE(p.y == Approx(2.5f).margin(EPS));
}

TEST_CASE("Position 0.5 belongs to tile 1 (round half away from zero)") {
    // Documents that lround(0.5) = 1, so the player at 0.5 is considered
    // to be on tile 1. If the rounding strategy changes
    // (for example, to floor), this test breaks and forces a review.
    auto isWalkable = [](int x, int) { return x < 1; };   // wall at x >= 1

    // Player at 0.4 trying to move to 0.55: lround(0.55) = 1, solid, blocked.
    auto p = Collision::TryMove({0.4f, 0.0f}, {0.15f, 0.0f}, isWalkable);
    REQUIRE(p.x == Approx(0.4f).margin(EPS));
}