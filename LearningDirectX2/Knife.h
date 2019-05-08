#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "KnifeRotateState.h"

class Knife : public Weapon {
public:
	Knife();
	~Knife();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Update(double dt);
	virtual BoxCollider GetCollider();
	virtual void Instantiate(D3DXVECTOR3 position);
};