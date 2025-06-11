#include "world/Map.h"
#include "utils/IsometricUtils.h"

Map::Map() {
    img = LoadImage("../GameIsometric/assets/isometricblocks.png");
    if (img.data == nullptr) {
        TraceLog(LOG_ERROR, "Erro: Imagem não carregada!");
    }

    texture = LoadTextureFromImage(img);
    
    UnloadImage(img);

    // Seleciona o primeiro bloco da imagem: posição (0,0), tamanho 32x32
    sourceRect = { 0, 0, 32, 32 };
}

Map::~Map() {
    UnloadTexture(texture);
}

// Getters and Setters
int Map::GetWidth()      const { return mapWidth; }
int Map::GetHeight()     const { return mapHeight; }
int Map::GetTileWidth()  const { return tileWidth; }
int Map::GetTileHeight() const { return tileHeight; }

void Map::Draw() {
    Vector2 offset = CalculateIsometricOffset(mapWidth, mapHeight, tileWidth, tileHeight);

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            Vector2 isoPos = IsoToScreen({ (float)x, (float)y }, tileWidth, tileHeight);

            isoPos.x += offset.x - (tileWidth / 2.0f);
            isoPos.y += offset.y;

            DrawTextureRec(texture, sourceRect, isoPos, WHITE);
        }
    }
}
