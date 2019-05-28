#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerIdleState : public PlayerState {
public:
	PlayerIdleState(PlayerData *data);
	~PlayerIdleState();
	void Render() override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side) override;
	State GetState() override;
	void ResetState(int dummy) override;
};