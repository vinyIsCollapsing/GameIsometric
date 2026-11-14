#ifndef MAP_H
#define MAP_H

#include "raylib.h"

// Tipos de tiles disponíveis no mundo
enum TileType {
    TILE_DIRT = 0,
    TILE_DENSE_DIRT = 1,
    TILE_ROCK = 2
};

class Map {
public:
    Map();
    ~Map();

    int GetWidth() const;
    int GetHeight() const;
    int GetTileWidth() const;
    int GetTileHeight() const;

    Vector2 GetCachedOffset();  // Calcula e armazena o offset isométrico
    void Draw();                // Desenha o mapa inteiro

private:
    static const int mapRadius = 16;
    static const int mapWidth = mapRadius * 2 + 1;
    static const int mapHeight = mapRadius * 2 + 1;
    const int tileWidth = 32;
    const int tileHeight = 32;

    TileType tileMap[mapHeight][mapWidth]; // Mapa de tiles

    Image img;
    Texture2D texture;
    Rectangle sourceRect;

    Vector2 cachedOffset;
    bool offsetCalculated = false;

    unsigned int seed; // Seed aleatória por execução

    int ToIndex(int coord) const;                 // Converte coordenada de [-R, +R] para [0, 2R]
    TileType GenerateTile(int x, int y) const;    // Geração procedural com seed variável
    TileType SmoothTile(int x, int y) const;      // Suavização baseada na vizinhança
};

#endif
