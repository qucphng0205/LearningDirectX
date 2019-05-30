#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerInjuredState : public PlayerState {
public:
	PlayerInjuredState(PlayerData *data);
	~PlayerInjuredState();
	void Render() override;
	void Update(double dt) override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60) override;
	State GetState() override;
	void ResetState(int dummy) override;
};