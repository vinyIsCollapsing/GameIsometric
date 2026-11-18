#include "entities/Player.h"
#include "entities/PlayerState.h"
#include "utils/Collision.h"
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

void Player::Update(float dt) {
    if (currentState) currentState->Update(this, dt);
}

void Player::Draw() {
    const Vector2 tileTopLeft = map->GridToScreen(position);
    
    const Vector2 drawPos = {
        tileTopLeft.x + map->GetTileWidth() / 2.0f - sourceRect.width  / 2.0f,
        tileTopLeft.y + map->GetTileHeight() / 2.0f - sourceRect.height
    };
    DrawTextureRec(texture, sourceRect, drawPos, WHITE);
}

void Player::TryMove(Vector2 delta) {
    position = Collision::TryMove(position, delta, [this](int x, int y) {
        return map->IsWalkable(x, y);
    });
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