#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerClimbState : public PlayerState {
public:
	PlayerClimbState(PlayerData *data);
	~PlayerClimbState();
	void Render() override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side) override;
	State GetState() override;
	void ResetState(int dummy) override;
};