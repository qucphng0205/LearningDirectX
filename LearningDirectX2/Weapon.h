#pragma once
#include "GameConfig.h"
#include "Entity.h"
#include "Textures.h"
#include "Animation.h"
#include "Camera.h"
#include "Explosion.h"

#include "Unit.h"
#include "Grid.h"

class Weapon : public Entity {
public:
	Weapon();
	~Weapon();

	virtual void Update(double dt);
	virtual void Render();

	virtual BoxCollider GetRect();
	virtual void SetActive(bool active);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetMoveDirection(Entity::EntityDirection dir);
	//Get collilder width
	virtual float GetWidth();
	virtual float GetBigWidth();
	//Get collider height;
	virtual float GetHeight();
	virtual float GetBigHeight();
	virtual void OnCollision(Entity *impactor, SideCollision side, float collisionTime);
	virtual void Instantiate(D3DXVECTOR3 position);
	virtual EarnedData OnDestroy();
protected:
	virtual void MakeInactive();
	virtual void Spawn();
	BoxCollider collider;
	Animation *anim;
	int point;
};




