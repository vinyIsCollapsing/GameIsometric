#ifndef UTILS_ISOMETRICUTILS_H
#define UTILS_ISOMETRICUTILS_H

#include "raylib.h"
#include <glm/glm.hpp>

inline glm::mat3 GetIsometricMatrix(float tileWidth, float tileHeight) {
    // Matriz de transformação isométrica (3x3)
    return glm::mat3(
        tileWidth / 2.0f,  tileHeight / 4.0f, 0.0f,
       -tileWidth / 2.0f,  tileHeight / 4.0f, 0.0f,
        0.0f,               0.0f,             1.0f
    );
}

inline Vector2 IsoToScreen(glm::mat3 isoMat, Vector2 gridPos) {
    glm::vec3 grid(gridPos.x, gridPos.y, 1.0f);
    glm::vec3 screen = isoMat * grid;
    return { screen.x, screen.y };
}

inline Vector2 CalculateIsometricOffset(int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
    int gridWidthPixels = (mapWidth + mapHeight) * (tileWidth / 2);
    int gridHeightPixels = (mapWidth + mapHeight) * (tileHeight / 4);

    return {
        (float)(GetScreenWidth() - gridWidthPixels),
        (float)(GetScreenHeight() - gridHeightPixels) / 2.0f
    };
}

#endif
