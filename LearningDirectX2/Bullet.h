#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "KnifeRotateState.h"

class Bullet : public Weapon {
public:
	Bullet();
	~Bullet();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Update(double dt);
	virtual void Instantiate(D3DXVECTOR3 position);
};