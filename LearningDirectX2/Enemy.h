#pragma once
#include "Entity.h"
#include "EnemyData.h"
#include "GameConfig.h"
#include "EnemyState.h"

class Enemy : public Entity {
public:

	Enemy();
	~Enemy();
	virtual BoxCollider GetRect();
	virtual void SetSpawnBox(BoxCollider box, int direction);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual BoxCollider GetCollider();
	virtual void Spawn();

protected:
	D3DXVECTOR3 spawnPosition;
	Entity::EntityDirection spawnDirection;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
	EnemyData *enemyData;
	BoxCollider spawnBox;
};