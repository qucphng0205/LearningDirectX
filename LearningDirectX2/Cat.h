#pragma once
#include "Enemy.h"
#include "CatFollowState.h"

class Cat : public Enemy {
public:
	Cat();
	~Cat();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, float dt) override;
	void Update(double dt) override;
	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);
	void SetState(EnemyState::State) override;
	BoxCollider GetCollider() override;
	void Spawn() override;
protected:
	EnemyState *catFollowState;
};