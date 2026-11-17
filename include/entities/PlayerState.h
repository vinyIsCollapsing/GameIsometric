#ifndef ENTITIES_PLAYERSTATE_H
#define ENTITIES_PLAYERSTATE_H

#include "raylib.h"
#include "Player.h"

class Player;

// Base state interface
class PlayerState {
public:
    virtual ~PlayerState() {}
    virtual void Update(Player* player, float dt) = 0;
};

Direction8 GetDirectionFromVector(Vector2 dir);

// Idle state
class IdleState : public PlayerState {
public:
    void Update(Player* player, float dt) override;
};

// Running state
class RunningState : public PlayerState {
public:
    void Update(Player* player, float dt) override;
};

#endif // PLAYERSTATE_H
