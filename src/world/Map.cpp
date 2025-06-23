#include "world/Map.h"
#include "utils/IsometricUtils.h"
#include <glm/glm.hpp>
#include <cmath>  // para abs

Map::Map() {
    img = LoadImage("../GameIsometric/assets/isometricblocks.png");
    if (img.data == nullptr) {
        TraceLog(LOG_ERROR, "Erro: Imagem não carregada!");
    }

    texture = LoadTextureFromImage(img);
    UnloadImage(img);

    sourceRect = { 0, 0, 32, 32 };  // Bloco base (dirt)

    // Geração do mapa procedural determinístico
    for (int y = -mapRadius; y <= mapRadius; y++) {
        for (int x = -mapRadius; x <= mapRadius; x++) {
            tileMap[ToIndex(y)][ToIndex(x)] = GenerateTile(x, y);
        }
    }
}

Map::~Map() {
    UnloadTexture(texture);
}

int Map::GetWidth()      const { return mapWidth; }
int Map::GetHeight()     const { return mapHeight; }
int Map::GetTileWidth()  const { return tileWidth; }
int Map::GetTileHeight() const { return tileHeight; }

Vector2 Map::GetCachedOffset() {
    if (!offsetCalculated) {
        cachedOffset = CalculateIsometricOffset(mapWidth, mapHeight, tileWidth, tileHeight);
        offsetCalculated = true;
    }
    return cachedOffset;
}

int Map::ToIndex(int coord) const {
    return coord + mapRadius;  // transforma de [-16, 16] para [0, 32]
}

TileType Map::GenerateTile(int x, int y) const {
    int value = abs((x * 73856093) ^ (y * 19349663)) % 100;

    if (value < 15) return TILE_ROCK;
    if (value < 35) return TILE_DENSE_DIRT;
    return TILE_DIRT;
}

void Map::Draw() {
    Vector2 offset = GetCachedOffset();
    glm::mat3 isoMat = GetIsometricMatrix(tileWidth, tileHeight);

    for (int y = -mapRadius; y <= mapRadius; y++) {
        for (int x = -mapRadius; x <= mapRadius; x++) {
            Vector2 isoPos = IsoToScreen(isoMat, { (float)x, (float)y });

            isoPos.x += offset.x - (tileWidth / 2.0f);
            isoPos.y += offset.y;

            TileType tile = tileMap[ToIndex(y)][ToIndex(x)];

            Rectangle src = sourceRect;
            switch (tile) {
                case TILE_DIRT: src.x = 0; break;
                case TILE_DENSE_DIRT:  src.x = 32; break;
                case TILE_ROCK: src.x = 64; break;
            }

            DrawTextureRec(texture, src, isoPos, WHITE);
        }
    }
}
