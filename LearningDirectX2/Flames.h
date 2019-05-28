#pragma once
#include "Weapon.h"
#include "Player.h"

class Flames : public Weapon {
public:
	static int quantity;

	Flames();
	virtual void Update(double dt);
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0/60);
	virtual void Instantiate(D3DXVECTOR3 position);
	virtual EarnedData OnDestroy();
private:
	int index;
};