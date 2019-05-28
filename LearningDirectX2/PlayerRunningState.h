#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningState : public PlayerState {
public:
	PlayerRunningState(PlayerData *data);
	~PlayerRunningState();
	void Update(double dt) override;
	void Render() override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side) override;
	State GetState() override;
	void ResetState(int dummy) override;
};