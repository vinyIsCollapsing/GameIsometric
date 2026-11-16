#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <glm/glm.hpp>
#include "raylib.h"
#include "utils/IsometricUtils.h"

using Catch::Approx;

namespace {
    constexpr float TOL = 1e-4f;
}

TEST_CASE("IsoToScreen é afim (linear + translação)") {
    glm::mat3 m = GetIsometricMatrix(32.0f, 32.0f);

    Vector2 o = IsoToScreen(m, {0.0f, 0.0f});
    Vector2 a = IsoToScreen(m, {1.0f, 0.0f});
    Vector2 b = IsoToScreen(m, {2.0f, 0.0f});

    // f(2v) - f(0) == 2 * (f(v) - f(0)) para qualquer transformação afim
    REQUIRE(b.x - o.x == Approx(2.0f * (a.x - o.x)).margin(TOL));
    REQUIRE(b.y - o.y == Approx(2.0f * (a.y - o.y)).margin(TOL));
}

TEST_CASE("IsoToScreen trata eixos x e y de forma simétrica") {
    glm::mat3 m = GetIsometricMatrix(32.0f, 32.0f);

    Vector2 px = IsoToScreen(m, {1.0f, 0.0f});   // avança no eixo x da grid
    Vector2 py = IsoToScreen(m, {0.0f, 1.0f});   // avança no eixo y da grid

    // Num sistema isométrico padrão, os dois eixos se projetam em direções opostas em X
    // e na mesma direção em Y.
    REQUIRE(px.y == Approx(py.y).margin(TOL));
    // Não exigimos sinal específico, só que não colapsem para o mesmo ponto
    REQUIRE(std::abs(px.x - py.x) > TOL);
}

TEST_CASE("CalculateIsometricOffset não retorna NaN/Inf") {
    Vector2 o = CalculateIsometricOffset(33, 33, 32, 32);
    REQUIRE(std::isfinite(o.x));
    REQUIRE(std::isfinite(o.y));
}

TEST_CASE("CalculateIsometricOffset é determinístico") {
    Vector2 a = CalculateIsometricOffset(33, 33, 32, 32);
    Vector2 b = CalculateIsometricOffset(33, 33, 32, 32);
    REQUIRE(a.x == Approx(b.x));
    REQUIRE(a.y == Approx(b.y));
}