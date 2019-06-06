#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "BatFollowState.h"

class Bat : public Enemy {
public:
	Bat();
	~Bat();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60);

	void Update(double dt) override;
	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);
	void SetState(EnemyState::State) override;
	BoxCollider GetCollider() override;
	void Spawn() override;
protected:
	EnemyState *batFollowState;
	int state;
};