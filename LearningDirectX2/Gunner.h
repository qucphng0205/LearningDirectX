#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "ObjectPooling.h"
#include "GunnerFollowState.h"
#include "GunnerAttackState.h"

class Gunner : public Enemy {
public:
	Gunner();
	~Gunner();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Update(double dt);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetState(EnemyState::State);
	virtual BoxCollider GetCollider();
	virtual void Spawn();
	virtual void SpawnBigBullet();
protected:
	EnemyState
		*gunnerFollowState,
		*gunnerAttackState;

};