#include "Map.h"

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

void Map::Draw() {
    // Calcular o offset para centralizar o grid
    int gridWidthPixels = (mapWidth + mapHeight) * (tileWidth / 2);
    int gridHeightPixels = (mapWidth + mapHeight) * (tileHeight / 4);

    int offsetX = (GetScreenWidth() - gridWidthPixels);
    int offsetY = (GetScreenHeight() - gridHeightPixels) / 2;

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int screenX = (((x - y) * tileWidth / 2) - (tileWidth / 2)) + offsetX;
            int screenY = ((x + y) * (tileHeight * 0.5) / 2) + offsetY;

            DrawTextureRec(texture, sourceRect, { (float)screenX, (float)screenY }, WHITE);
        }
    }
}
