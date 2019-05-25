#pragma once
#include "PlayerState.h"
#include "Player.h"

#include "Item.h"

class PlayerSlashState : public PlayerState {
public:
	PlayerSlashState(PlayerData *data);
	~PlayerSlashState();
	void Update(double dt) override;
	void Render() override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side) override;
	State GetState() override;
	void ResetState(int dummy) override;
	BoxCollider GetBody();
	bool CollideWithKatana(BoxCollider r);
	bool CollideWithBody(BoxCollider r);
};