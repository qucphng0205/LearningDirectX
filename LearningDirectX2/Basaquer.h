#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "BasaquerIdleState.h"
#include "BasaquerJumpingState.h"
#include "ObjectPooling.h"

class Basaquer : public Enemy {
public:
	Basaquer();
	~Basaquer();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	void Update(double dt) override;
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	void SetState(EnemyState::State) override;
	BoxCollider GetCollider() override;
	void SetActive(bool active) override;
	void Spawn() override;
	void SpawnDarts();
protected:
	EnemyState
		*basaquerJumpingState,
		*basaquerIdleState;
	enum EnemyState::State state;
};