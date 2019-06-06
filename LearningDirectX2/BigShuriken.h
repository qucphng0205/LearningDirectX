#pragma once
#include "Weapon.h"
#include "Player.h"

class BigShuriken : public Weapon {
public:
	BigShuriken();
	void Update(double dt) override;
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60) override;
	void Instantiate(D3DXVECTOR3 position) override;
	EarnedData OnDestroy() override;
};