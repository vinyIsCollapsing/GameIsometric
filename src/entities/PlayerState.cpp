#include <cstdio> // para printf[
#include <cmath>

#include "raylib.h"

#include "Player.h"
#include "PlayerState.h"

// Implementação de IdleState
void IdleState::Update(Player* player) {
    // Se alguma tecla for pressionada, pode "mudar" para RunningState
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) ||
        IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)) {
        // Exemplo: trocando de estado
        player->ChangeState(new RunningState());
    }
}

// Implementação de RunningState

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

    // Calcular magnitude antes do ajuste
    // float magBefore = sqrtf(moveDir.x * moveDir.x + moveDir.y * moveDir.y);

    // Ajuste apenas para diagonais
    if (moveDir.x != 0.0f && moveDir.y != 0.0f) {
    //    moveDir.x /= 0.7071f;
    //    moveDir.y /= 0.7071f;
    }

    // Calcular magnitude depois do ajuste
    // float magAfter = sqrtf(moveDir.x * moveDir.x + moveDir.y * moveDir.y);

    // Debug: imprimir as magnitudes
    // if (magBefore != 0){
    //     printf("Magnitude antes: %.4f | depois: %.4f\n", magBefore, magAfter);
    // }
    

    Vector2 pos = player->GetPosition();
    pos.x += moveDir.x * speed;
    pos.y += moveDir.y * speed;

    player->SetPosition(pos);
}
