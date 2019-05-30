#pragma once
#include "Animation.h"
#include "GameConfig.h"
#include "Enemy.h"
#include "SpartaFollowState.h"

class Sparta : public Enemy {
public:
	Sparta();
	~Sparta();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60);
	virtual void Update(double dt);
	//virtual float GetWidth();
	//virtual float GetHeight();
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetState(EnemyState::State);
	virtual BoxCollider GetCollider();
	virtual void Spawn();
protected:
	EnemyState *spartaFollowState;
};