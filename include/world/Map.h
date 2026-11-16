#ifndef MAP_H
#define MAP_H

#include <memory>

#include "raylib.h"
#include "MapGenerator.h"

class Map {
public:
    Map();
    ~Map();

    int GetMapWidth() const;
    int GetMapHeight() const;
    int GetTileWidth() const;
    int GetTileHeight() const;

    // Converts isometric grid coordinates to screen position,
    // already including the map's center offset.
    // Consolidates the formula that was previously duplicated in 
    Vector2 GridToScreen(Vector2 gridPos) const;

    void Draw();                // Draw map

private:
    Vector2 GetCachedOffset() const;

    std::unique_ptr<MapGenerator> generator;
    
    const int mapWidth;
    const int mapHeight;
    const int tileWidth = 32;
    const int tileHeight = 32;

    Image img;
    Texture2D texture;
    Rectangle sourceRect;

    // mutable: cache populated on demand in GetCachedOffset() const
    mutable Vector2 cachedOffset{};
    mutable bool offsetCalculated = false;
};

#endif
