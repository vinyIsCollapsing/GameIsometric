#include "world/Map.h"
#include "utils/IsometricUtils.h"
#include <glm/glm.hpp>
#include <cmath>
#include <ctime>  // para time()

Map::Map() {
    seed = static_cast<unsigned int>(time(NULL));  // Gera seed aleatória por execução
    TraceLog(LOG_INFO, TextFormat("Seed usada para gerar o mapa: %u", seed));

    img = LoadImage("../GameIsometric/assets/isometricblocks.png");
    if (img.data == nullptr) {
        TraceLog(LOG_ERROR, "Erro: Imagem não carregada!");
    }

    texture = LoadTextureFromImage(img);
    UnloadImage(img);

    sourceRect = { 0, 0, 32, 32 };  // Bloco base (dirt)

    // Geração do mapa procedural com seed aleatória
    for (int y = -mapRadius; y <= mapRadius; y++) {
        for (int x = -mapRadius; x <= mapRadius; x++) {
            tileMap[ToIndex(y)][ToIndex(x)] = GenerateTile(x, y);
        }
    }

    // Suavização opcional
    for (int y = -mapRadius; y <= mapRadius; y++) {
        for (int x = -mapRadius; x <= mapRadius; x++) {
            tileMap[ToIndex(y)][ToIndex(x)] = SmoothTile(x, y);
        }
    }
}

Map::~Map() {
    UnloadTexture(texture);
}

int Map::GetWidth() const { return mapWidth; }
int Map::GetHeight() const { return mapHeight; }
int Map::GetTileWidth() const { return tileWidth; }
int Map::GetTileHeight() const { return tileHeight; }

Vector2 Map::GetCachedOffset() {
    if (!offsetCalculated) {
        cachedOffset = CalculateIsometricOffset(mapWidth, mapHeight, tileWidth, tileHeight);
        offsetCalculated = true;
    }
    return cachedOffset;
}

int Map::ToIndex(int coord) const {
    return coord + mapRadius;
}

TileType Map::GenerateTile(int x, int y) const {
    // Hash aleatório influenciado pela seed
    int hash = abs(((x + seed) * 73856093) ^ ((y + seed) * 19349663)) % 100;

    // Região Noroeste: mais rochosa
    if (x < 0 && y < 0) {
        if (hash < 80) return TILE_ROCK;
        if (hash < 70) return TILE_DENSE_DIRT;
        return TILE_DIRT;
    }

    // Região Sudeste: mais fértil
    if (x > 0 && y > 0) {
        if (hash < 10) return TILE_ROCK;
        if (hash < 20) return TILE_DENSE_DIRT;
        return TILE_DIRT;
    }

    // Região padrão
    if (hash < 30) return TILE_ROCK;
    if (hash < 70) return TILE_DENSE_DIRT;
    return TILE_DIRT;
}

TileType Map::SmoothTile(int x, int y) const {
    int counts[3] = { 0, 0, 0 };

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (abs(nx) <= mapRadius && abs(ny) <= mapRadius) {
                TileType neighbor = tileMap[ToIndex(ny)][ToIndex(nx)];
                counts[(int)neighbor]++;
            }
        }
    }

    int maxIdx = 0;
    for (int i = 1; i < 3; i++) {
        if (counts[i] > counts[maxIdx]) maxIdx = i;
    }

    return (TileType)maxIdx;
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
                case TILE_DIRT:       src.x = 0;  break;
                case TILE_DENSE_DIRT: src.x = 32; break;
                case TILE_ROCK:       src.x = 64; break;
            }

            DrawTextureRec(texture, src, isoPos, WHITE);
        }
    }
}
