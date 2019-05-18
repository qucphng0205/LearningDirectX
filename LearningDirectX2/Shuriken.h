#pragma once
#include "Weapon.h"
class Shuriken : public Weapon {
public:
	Shuriken();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Instantiate(D3DXVECTOR3 position);
};