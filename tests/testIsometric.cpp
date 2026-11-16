#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <glm/glm.hpp>
#include "raylib.h"
#include "utils/IsometricUtils.h"

using Catch::Approx;

namespace {
    constexpr float TOL = 1e-4f;
}

TEST_CASE("IsoToScreen is affine (linear + translation)") {
    glm::mat3 m = GetIsometricMatrix(32.0f, 32.0f);

    Vector2 o = IsoToScreen(m, {0.0f, 0.0f});
    Vector2 a = IsoToScreen(m, {1.0f, 0.0f});
    Vector2 b = IsoToScreen(m, {2.0f, 0.0f});

    // f(2v) - f(0) == 2 * (f(v) - f(0))  for any affine transformation
    REQUIRE(b.x - o.x == Approx(2.0f * (a.x - o.x)).margin(TOL));
    REQUIRE(b.y - o.y == Approx(2.0f * (a.y - o.y)).margin(TOL));
}

TEST_CASE("IsoToScreen treats the x and y axes symmetrically") {
    glm::mat3 m = GetIsometricMatrix(32.0f, 32.0f);

    Vector2 px = IsoToScreen(m, {1.0f, 0.0f});   // moves along the x-axis of the grid
    Vector2 py = IsoToScreen(m, {0.0f, 1.0f});   // moves along the y-axis of the grid

    // In a standard isometric system, the two axes project in opposite directions along the X-axis
    // and in the same direction along the Y-axis.
    REQUIRE(px.y == Approx(py.y).margin(TOL));
    // We do not require a specific sign; we only require that they do not collapse to the same point
    REQUIRE(std::abs(px.x - py.x) > TOL);
}

TEST_CASE("CalculateIsometricOffset does not return NaN/Inf") {
    Vector2 o = CalculateIsometricOffset(33, 33, 32, 32);
    REQUIRE(std::isfinite(o.x));
    REQUIRE(std::isfinite(o.y));
}

TEST_CASE("CalculateIsometricOffset is deterministic") {
    Vector2 a = CalculateIsometricOffset(33, 33, 32, 32);
    Vector2 b = CalculateIsometricOffset(33, 33, 32, 32);
    REQUIRE(a.x == Approx(b.x));
    REQUIRE(a.y == Approx(b.y));
}