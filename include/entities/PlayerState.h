#ifndef ENTITIES_PLAYERSTATE_H
#define ENTITIES_PLAYERSTATE_H

class Player;

// Interface base de estados
class PlayerState {
public:
    virtual ~PlayerState() {}
    virtual void Update(Player* player) = 0;
};

// Estado ocioso
class IdleState : public PlayerState {
public:
    void Update(Player* player) override;
};

// Estado em movimento
class RunningState : public PlayerState {
public:
    void Update(Player* player) override;
};

#endif // PLAYERSTATE_H
