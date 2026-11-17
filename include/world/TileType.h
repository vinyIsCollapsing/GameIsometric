#ifndef TILE_TYPE_H
#define TILE_TYPE_H

enum TileType {
    TILE_DIRT = 0,
    TILE_DENSE_DIRT,
    TILE_ROCK,
    TILE_COUNT
};

// Only rule (for now) to block movement
inline bool IsSolid(TileType t){ return t == TILE_ROCK; }
#endif