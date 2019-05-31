#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include "Player.h"

class BasaquerJumpingState : public EnemyState {
public:
	BasaquerJumpingState(EnemyData *data);
	~BasaquerJumpingState();
	void ResetState() override;
	void Update(double dt) override;
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTIme, double dt = 1.0 / 60) override;
private:
	float timeState;
	float vx;
};
