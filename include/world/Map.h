#ifndef MAP_H
#define MAP_H

#include "raylib.h"

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
        const int mapWidth = 10;
        const int mapHeight = 10;
        const int tileWidth = 32;
        const int tileHeight = 32;

        Image img;
        Texture2D texture;
        Rectangle sourceRect;

        Vector2 cachedOffset;  // Novo atributo para cache
        bool offsetCalculated = false;  // Flag para checar se já foi calculado
};

#endif