#include "entities/Player.h"
#include "entities/PlayerState.h"
#include "utils/ResourcePath.h"

Player::Player(Vector2 startPos, Map* gameMap) : map(gameMap) {
    position = startPos;
    size = {32.0f, 32.0f};
    color = BLUE;
    texture = LoadTexture(
        ResourcePath("Player/player_movement.png").c_str()
    );

    sourceRect = {0.0f, 0.0f, 32.0f, 32.0f};
    currentDirection = SOUTH;

    currentState = new IdleState();
}

Player::~Player() {
    UnloadTexture(texture);
    delete currentState;
}

void Player::Update() {
    if (currentState)
        currentState->Update(this);
}

void Player::Draw() {
    const Vector2 isoPos = map->GridToScreen(position);
    const Vector2 drawPos = {
        isoPos.x - sourceRect.width  / 2.0f,
        isoPos.y - sourceRect.height
    };
    DrawTextureRec(texture, sourceRect, drawPos, WHITE);
}

void Player::ChangeState(PlayerState* newState) {
    delete currentState;
    currentState = newState;
}

Vector2 Player::GetPosition() const {
    return position;
}

void Player::SetPosition(Vector2 newPos){
    position = newPos;
}