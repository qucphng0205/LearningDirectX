#pragma once
#include "Weapon.h"
#include "Animation.h"

class Bullet : public Weapon {
public:
	Bullet();
	~Bullet();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, float dt) override;
	void Update(double dt) override;
	void Instantiate(D3DXVECTOR3 position) override;
};