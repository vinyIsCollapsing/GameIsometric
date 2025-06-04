#include "PlayerState.h"
#include "Player.h"
#include "raylib.h"

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
    // Lógica básica de movimento
    Vector2 pos = player->GetPosition();
    if (IsKeyDown(KEY_RIGHT)) pos.x += .20f;
    if (IsKeyDown(KEY_LEFT))  pos.x -= .20f;
    if (IsKeyDown(KEY_UP))    pos.y -= .20f;
    if (IsKeyDown(KEY_DOWN))  pos.y += .20f;

    player->SetPosition(pos);


    // Se nenhuma tecla pressionada, volta para Idle
    if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) &&
        !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) {
        player->ChangeState(new IdleState());
    }
}
