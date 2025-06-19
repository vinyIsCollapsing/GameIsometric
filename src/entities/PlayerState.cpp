#include <cmath>
#include <iostream>
#include "raylib.h"
#include "Player.h"
#include "PlayerState.h"

// Função auxiliar para determinar direção a partir de vetor
Direction8 GetDirectionFromVector(Vector2 dir) {
    // direção isométrica → baseada em diagonais
    if (dir.x > 0 && dir.y > 0)     return SOUTH;         // OK
    if (dir.x > 0 && dir.y == 0)    return SOUTHEAST;    // OK
    if (dir.x > 0 && dir.y < 0)     return EAST;           // OK
    if (dir.x == 0 && dir.y < 0)    return NORTHEAST;    // OK
    if (dir.x < 0 && dir.y < 0)     return NORTH;         // OK
    if (dir.x < 0 && dir.y == 0)    return NORTHWEST;     // OK
    if (dir.x < 0 && dir.y > 0)     return WEST;           // OK
    if (dir.x == 0 && dir.y > 0)    return SOUTHWEST;     // OK

    return SOUTH; // parado ou sem direção definida
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

    // Movimento
    if (moveDir.x != 0.0f || moveDir.y != 0.0f) {
        Vector2 pos = player->GetPosition();
        pos.x += moveDir.x * speed;
        pos.y += moveDir.y * speed;
        player->SetPosition(pos);

        Direction8 dir = GetDirectionFromVector(moveDir);
        player->currentDirection = dir;

        // Atualiza o sprite
        int spriteIndex = static_cast<int>(dir);
        player->sourceRect.x = 32.0f * spriteIndex;
        player->sourceRect.y = 0.0f;

        // Imprime a direção no terminal
        if (dir != player->lastDirectionPrinted) {
            switch (dir) {
                case SOUTH:      printf("Movendo para: SUL\n"); break;
                case SOUTHEAST:  printf("Movendo para: SUDESTE\n"); break;
                case EAST:       printf("Movendo para: LESTE\n"); break;
                case NORTHEAST:  printf("Movendo para: NORDESTE\n"); break;
                case NORTH:      printf("Movendo para: NORTE\n"); break;
                case NORTHWEST:  printf("Movendo para: NOROESTE\n"); break;
                case WEST:       printf("Movendo para: OESTE\n"); break;
                case SOUTHWEST:  printf("Movendo para: SUDOESTE\n"); break;
            }
            player->lastDirectionPrinted = dir;
        }

    }

    // Voltar ao estado Idle se nenhuma tecla pressionada
    if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) &&
        !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
        player->ChangeState(new IdleState());
    }
}
