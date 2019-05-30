#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "ThrowerFollowState.h"
#include "ThrowerAttackState.h"
#include "ObjectPooling.h"

class Thrower : public Enemy {
public:
	Thrower();
	~Thrower();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60);
	void SetVelocity(D3DXVECTOR2 vel);
	void SetVx(float vx) override;
	void Update(double dt) override;
	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);
	void SetState(EnemyState::State);
	BoxCollider GetCollider();
	void Spawn() override;
	void SpawnKnife();
protected:
	//Knife* knifePrefab;
	EnemyState *throwerFollowState,
		*throwerAttackState;
};