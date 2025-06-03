#ifndef ENTITIES_IDLESTATE_H
#define ENTITIES_IDLESTATE_H

#include "PlayerState.h"

class IdleState : public PlayerState {
public:
    void Update(Player* player) override;
};

#endif // IDLESTATE_H
