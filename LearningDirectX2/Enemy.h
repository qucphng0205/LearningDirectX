#pragma once
#include "Entity.h"
#include "EnemyData.h"
#include "GameConfig.h"
#include "EnemyState.h"
#include "Camera.h"
#include "Player.h"

class Enemy : public Entity {
public:
	Enemy();
	~Enemy();

	virtual void Update(double dt);
	virtual void Render();

	virtual BoxCollider GetRect();
	virtual BoxCollider GetSpawnRect();
	virtual void SetActive(bool active);
	virtual void SetRect(BoxCollider box);
	virtual void SetSpawnBox(BoxCollider box, int direction);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	//Get collilder width
	virtual float GetWidth();
	//Get collider height;
	virtual float GetHeight();
	virtual BoxCollider GetCollider();
	virtual void OnCollision(Entity *impactor, SideCollision side, float collisionTime);
	virtual void MakeInactive();
	virtual void Spawn();

protected:

	D3DXVECTOR3 spawnPosition;
	Entity::EntityDirection spawnDirection;
	BoxCollider spawnBox;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
	EnemyData *enemyData;
};