#include <cmath>
#include <iostream>
#include "raylib.h"
#include "Player.h"
#include "PlayerState.h"

// Helper function to determine direction from a vector
Direction8 GetDirectionFromVector(Vector2 dir) {
    // Isometric direction: based on diagonals
    if (dir.x > 0 && dir.y > 0)     return SOUTH;         // OK
    if (dir.x > 0 && dir.y == 0)    return SOUTHEAST;    // OK
    if (dir.x > 0 && dir.y < 0)     return EAST;           // OK
    if (dir.x == 0 && dir.y < 0)    return NORTHEAST;    // OK
    if (dir.x < 0 && dir.y < 0)     return NORTH;         // OK
    if (dir.x < 0 && dir.y == 0)    return NORTHWEST;     // OK
    if (dir.x < 0 && dir.y > 0)     return WEST;           // OK
    if (dir.x == 0 && dir.y > 0)    return SOUTHWEST;     // OK

    return SOUTH; // stationary or no defined direction
}


// IdleState
void IdleState::Update(Player* player) {
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) ||
        IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)) {
        player->ChangeState(new RunningState());
    }
}

// RunningState
void RunningState::Update(Player* player) {
    Vector2 moveDir = { 0.0f, 0.0f };
    float speed = 0.05f;

    if (IsKeyDown(KEY_UP)) {
        moveDir.x -= 1.0f;
        moveDir.y -= 1.0f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        moveDir.x += 1.0f;
        moveDir.y += 1.0f;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        moveDir.x += 1.0f;
        moveDir.y -= 1.0f;
    }
    if (IsKeyDown(KEY_LEFT)) {
        moveDir.x -= 1.0f;
        moveDir.y += 1.0f;
    }

    // Movement
    if (moveDir.x != 0.0f || moveDir.y != 0.0f) {
        Vector2 pos = player->GetPosition();
        pos.x += moveDir.x * speed;
        pos.y += moveDir.y * speed;
        player->SetPosition(pos);

        Direction8 dir = GetDirectionFromVector(moveDir);
        player->currentDirection = dir;

        // Updates the sprite
        int spriteIndex = static_cast<int>(dir);
        player->sourceRect.x = 32.0f * spriteIndex;
        player->sourceRect.y = 0.0f;

        // Prints the direction to the terminal
        if (dir != player->lastDirectionPrinted) {
            switch (dir) {
                case SOUTH:      printf("Moving to: SOUTH\n"); break;
                case SOUTHEAST:  printf("Moving to: SOUTHEAST\n"); break;
                case EAST:       printf("Moving to: EAST\n"); break;
                case NORTHEAST:  printf("Moving to: NORTHEAST\n"); break;
                case NORTH:      printf("Moving to: NORTH\n"); break;
                case NORTHWEST:  printf("Moving to: NORTHWEST\n"); break;
                case WEST:       printf("Moving to: WEST\n"); break;
                case SOUTHWEST:  printf("Moving to: SOUTHWEST\n"); break;
            }
            player->lastDirectionPrinted = dir;
        }

    }

    // Return to the Idle state if no key is pressed
    if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) &&
        !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
        player->ChangeState(new IdleState());
    }
}
