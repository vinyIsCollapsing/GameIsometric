#ifndef UTILS_COLLISION_H
#define UTILS_COLLISION_H

#include <cmath>

#include "raylib.h"

namespace Collision{
    template <typename IsWalkableFn>
    Vector2 TryMove(Vector2 pos, Vector2 delta, IsWalkableFn&& isWalkable){
        Vector2 result = pos;

        // X axis
        {
            const Vector2 tryX = {
                result.x + delta.x, result.y
            };
            const int tx = static_cast<int>(std::lround(tryX.x));
            const int ty = static_cast<int>(std::lround(tryX.y));
            if(isWalkable(tx, ty)){
                result = tryX;
            }
        }

        // Y axis
        {
            const Vector2 tryY = {
                result.x, result.y + delta.y
            };
            const int tx = static_cast<int>(std::lround(tryY.x));
            const int ty = static_cast<int>(std::lround(tryY.y));
            if (isWalkable(tx, ty)) {
                result = tryY;
            }
        }
        return result;
    }
    
}

#endif