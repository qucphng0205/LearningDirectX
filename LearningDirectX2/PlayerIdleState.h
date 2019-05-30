#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerIdleState : public PlayerState {
public:
	PlayerIdleState(PlayerData *data);
	~PlayerIdleState();
	void Render() override;
	void Update(double dt) override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60) override;
	State GetState() override;
	void ResetState(int dummy) override;
};