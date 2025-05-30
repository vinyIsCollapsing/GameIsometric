#ifndef MAP_H
#define MAP_H

#include "raylib.h"

class Map {
    public:
        Map();
        ~Map();
        void Draw();
    private:
        const int mapWidth = 10;
        const int mapHeight = 10;
        const int tileWidth = 32;
        const int tileHeight = 32;

        Image img;
        Texture2D texture;
        Rectangle sourceRect;
};

#endif