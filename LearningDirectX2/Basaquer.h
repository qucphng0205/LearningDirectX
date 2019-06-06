#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "BasaquerIdleState.h"
#include "BasaquerJumpingState.h"
#include "ObjectPooling.h"
#include "BigExplosion.h"

class Basaquer : public Enemy {
public:
	Basaquer();
	~Basaquer();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	void Update(double dt) override;
	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);
	void SetVelocity(D3DXVECTOR2 vel) override;
	void SetVx(float vx) override;
	void SetVy(float vy) override;
	void SetState(EnemyState::State) override;
	BoxCollider GetCollider() override;
	void SetActive(bool active) override;
	void Spawn() override;
	EarnedData OnDestroy() override;
	void SpawnDarts();
protected:
	EnemyState
		*basaquerJumpingState,
		*basaquerIdleState;
	enum EnemyState::State state;
	bool isDead;
	float explosionTime;

	int jumpTimes;
};