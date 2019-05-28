#pragma once
#include "Weapon.h"
#include "Player.h"

class BigShuriken : public Weapon {
public:
	BigShuriken();
	virtual void Update(double dt);
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0/60);
	virtual void Instantiate(D3DXVECTOR3 position);
	virtual EarnedData OnDestroy();
};