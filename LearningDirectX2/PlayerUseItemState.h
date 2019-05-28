#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerUseItemState : public PlayerState {
public:
	PlayerUseItemState(PlayerData *data);
	~PlayerUseItemState();
	void Update(double dt) override;
	void Render() override;
	void HandleInput() override;
	void OnCollision(Entity *impactor, Entity::SideCollision side) override;
	State GetState() override;
	void ResetState(int dummy) override;
private:
	int currentState;
};