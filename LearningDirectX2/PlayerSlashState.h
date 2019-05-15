#pragma once
#include "PlayerState.h"
#include "Player.h"

#include "Item.h"

class PlayerSlashState : public PlayerState {
public:
	PlayerSlashState(PlayerData *data);
	~PlayerSlashState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void ResetState(int dummy);
	virtual bool CollideWithKatana(BoxCollider r);
	virtual bool CollideWithBody(BoxCollider r);
};