#pragma once
#include "Animation.h"
#include "GameConfig.h"
#include "Enemy.h"
#include "RunnerFollowState.h"

class Runner : public Enemy {
public:
	Runner();
	~Runner();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, float dt) override;
	void Update(double dt) override;
	//virtual float GetWidth();
	//virtual float GetHeight();
	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);
	void SetState(EnemyState::State) override;
	BoxCollider GetCollider() override;
	void Spawn() override;
protected:
	EnemyState *runnerFollowState;
};