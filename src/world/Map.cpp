#include "world/Map.h"
#include "utils/IsometricUtils.h"
#include "utils/ResourcePath.h"

#include <ctime>

Map::Map(){
    auto seed = static_cast<std::uint32_t>(time(nullptr));
    TraceLog(LOG_INFO, TextFormat("Seed used to generate the map: %u", seed));

    generator = std::make_unique<MapGenerator>(seed);
    generator->Generate();

    mapWidth  = generator->GetWidth();
    mapHeight = generator->GetHeight();

    LoadTileTexture();
}

Map::Map(const std::string& mapPath){
    auto seed = static_cast<std::uint32_t>(time(nullptr));
    generator = std::make_unique<MapGenerator>(seed);

    if (generator->LoadFromFile(mapPath)) {
        TraceLog(LOG_INFO, TextFormat("Map loaded from '%s'", mapPath.c_str()));
    } else {
        TraceLog(LOG_WARNING, "Error to load map; using procedural");
        generator->Generate();
    }

    mapWidth  = generator->GetWidth();
    mapHeight = generator->GetHeight();

    LoadTileTexture();
}

void Map::LoadTileTexture(){
    img = LoadImage(ResourcePath("isometricblocks.png").c_str());

    if (img.data == nullptr) {
        TraceLog(LOG_ERROR, "Error: Image not loaded");
    }
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
    sourceRect = { 0, 0, 32, 32 };
}

Map::~Map() {
    UnloadTexture(texture);
}

int Map::GetMapWidth() const { return mapWidth; }
int Map::GetMapHeight() const { return mapHeight; }
int Map::GetTileWidth() const { return tileWidth; }
int Map::GetTileHeight() const { return tileHeight; }

Vector2 Map::GetCachedOffset() const {
    if (!offsetCalculated) {
        cachedOffset = CalculateIsometricOffset(mapWidth, mapHeight, tileWidth, tileHeight);
        offsetCalculated = true;
    }
    return cachedOffset;
}

Vector2 Map::GridToScreen(Vector2 gridPos) const {
    const glm::mat3 isoMat = GetIsometricMatrix((float)tileWidth, (float)tileHeight);
    Vector2 isoPos = IsoToScreen(isoMat, gridPos);

    const Vector2 offset = GetCachedOffset();
    isoPos.x += offset.x - (tileWidth / 2.0f);
    isoPos.y += offset.y - (tileHeight / 2.0f);
    return isoPos;
}

bool Map::IsWalkable(int x, int y) const {
    return !generator->IsSolidAt(x, y);
}

void Map::Draw() {
    const int halfW = mapWidth  / 2;
    const int halfH = mapHeight / 2;

    for (int y = -halfH; y <= halfH; ++y) {
        for (int x = -halfW; x <= halfW; ++x) {
            const Vector2 isoPos = GridToScreen({ (float)x, (float)y });

            const TileType tile = generator->Get(x, y);

            Rectangle src = sourceRect;
            switch (tile) {
                case TILE_DIRT:       src.x = 0;  break;
                case TILE_DENSE_DIRT: src.x = 32; break;
                case TILE_ROCK:       src.x = 64; break;
                default: break;
            }
            DrawTextureRec(texture, src, isoPos, WHITE);
        }
    }
}
