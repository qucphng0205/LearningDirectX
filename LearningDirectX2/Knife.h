#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "Animation.h"
#include "KnifeRotateState.h"

class Knife : public Enemy {
public:
	Knife(EntityDirection dir);
	~Knife();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Update(double dt);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetState(EnemyState::State);
	virtual BoxCollider GetCollider();
	virtual void Spawn();
	virtual void Spawn(EntityDirection dir);
protected:
	EnemyState *knifeRotateState;
};