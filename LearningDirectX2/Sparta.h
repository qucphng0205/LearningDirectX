#pragma once
#include "Entity.h"
#include "Textures.h"
#include "Animation.h"
#include "GameConfig.h"

class Sparta : public Entity {
public:
	Sparta();
	~Sparta();
	virtual void Update(double dt);
	virtual void Render();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	BoxCollider GetRect();
	//virtual int GetWidth();
	//virtual int GetHeight();
	virtual void SetVelocity(D3DXVECTOR2 velocity);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual BoxCollider GetCollider();

protected:
	Animation *anim;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
};