#pragma once
#include "Textures.h"
#include "Animation.h"
#include "GameConfig.h"
#include "Enemy.h"
#include "EnemyData.h"
#include "EnemyState.h"

class Sparta : public Enemy {
public:
	Sparta();
	~Sparta();
	virtual void Render();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	//virtual int GetWidth();
	//virtual int GetHeight();
	virtual void SetVelocity(D3DXVECTOR2 velocity);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetStage(EnemyState::State);
	virtual BoxCollider GetCollider();

protected:
	EnemyState *spartaFollowState;
};