#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerCrouchState : public PlayerState {
public:
	PlayerCrouchState(PlayerData *data);
	~PlayerCrouchState();
	void Render() override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side) override;
	State GetState() override;
	void ResetState(int dummy) override;

};