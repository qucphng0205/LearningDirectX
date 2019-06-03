#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "gnhpSound.h"

class PlayerCrouchSlashState : public PlayerState {
public:
	PlayerCrouchSlashState(PlayerData *data);
	~PlayerCrouchSlashState();
	void Update(double dt) override;
	void Render() override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60) override;
	State GetState() override;
	void ResetState(int dummy) override;
	BoxCollider GetBody();
	bool CollideWithKatana(BoxCollider r);
	bool CollideWithBody(BoxCollider r);
};