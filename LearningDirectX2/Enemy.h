#pragma once
#include "GameConfig.h"
#include "Textures.h"
#include "EnemyData.h"
#include "Entity.h"
#include "EnemyState.h"
#include "Explosion.h"
#include "Camera.h"

#include "Unit.h"
#include "Grid.h"



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
	virtual void SetColliderTop(float top);
	virtual void SetColliderLeft(float left);
	virtual void SetColliderBottom(float bottom);
	virtual void SetColliderRight(float right);
	virtual void SetMoveDirection(Entity::EntityDirection dir);
	virtual void SetState(EnemyState::State state);
	//Get collilder width
	virtual float GetWidth();
	virtual float GetBigWidth();
	//Get collider height;
	virtual float GetHeight();
	virtual float GetBigHeight();
	virtual BoxCollider GetCollider();
	virtual void OnCollision(Entity *impactor, SideCollision side, float collisionTime);
	virtual Entity::EntityDirection GetSpawnDirection();
	virtual EarnedData OnDestroy();
	//virtual void SwapLeftRightCollider();

protected:
	virtual void MakeInactive();
	virtual void Spawn();
	bool onGround;
	D3DXVECTOR3 spawnPosition;
	Entity::EntityDirection spawnDirection;
	BoxCollider spawnBox;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
	EnemyData *enemyData;

	EffectChain *effect;
	int point;
};