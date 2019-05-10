#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerJumpingState : public PlayerState {
public:
	PlayerJumpingState(PlayerData *data);
	~PlayerJumpingState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void ResetState(int dummy);
};