#include "IdleState.h"
#include "Player.h"
#include "raylib.h"

void IdleState::Update(Player* player) {
    // Exemplo simples: mover para RunningState se uma tecla for pressionada
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) ||
        IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)) {
        // Mudar de estado aqui, ex.: player->ChangeState(new RunningState());
    }
}
