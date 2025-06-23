#ifndef MAP_H
#define MAP_H

#include "raylib.h"

enum TileType {
    TILE_DIRT,
    TILE_DENSE_DIRT,
    TILE_ROCK
};

class Map {
    public:
        Map();
        ~Map();

        int GetWidth() const;
        int GetHeight() const;
        int GetTileWidth() const;
        int GetTileHeight() const;

        Vector2 GetCachedOffset();  // Novo método para retornar o offset calculado uma vez
        void Draw();

    private:
        static const int mapRadius = 16;
        static const int mapWidth = mapRadius * 2 + 1;
        static const int mapHeight = mapRadius * 2 + 1;
        const int tileWidth = 32;
        const int tileHeight = 32;

        TileType tileMap[mapHeight][mapWidth];

        Image img;
        Texture2D texture;
        Rectangle sourceRect;

        Vector2 cachedOffset;
        bool offsetCalculated = false;

        int ToIndex(int coord) const;
        TileType GenerateTile(int x, int y) const;
};

#endif
