#ifndef UTILS_ISOMETRICUTILS_H
#define UTILS_ISOMETRICUTILS_H

#include "raylib.h"

// Converte coordenadas isométricas (grid) para tela
inline Vector2 IsoToScreen(Vector2 gridPos, float tileWidth, float tileHeight) {
    return {
        (gridPos.x - gridPos.y) * (tileWidth / 2.0f),
        (gridPos.x + gridPos.y) * (tileHeight / 4.0f)
    };
}

// Calcula o offset global para centralizar o grid
inline Vector2 CalculateIsometricOffset(int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
    int gridWidthPixels = (mapWidth + mapHeight) * (tileWidth / 2);
    int gridHeightPixels = (mapWidth + mapHeight) * (tileHeight / 4);

    return {
        (float)(GetScreenWidth() - gridWidthPixels),
        (float)(GetScreenHeight() - gridHeightPixels) / 2
    };
}
#endif