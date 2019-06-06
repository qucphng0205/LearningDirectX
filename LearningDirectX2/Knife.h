#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "KnifeRotateState.h"

class Knife : public Weapon {
public:
	Knife();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60) override;
	void Update(double dt) override;
	void Instantiate(D3DXVECTOR3 position) override;
private:
	//purpose: linear interpolation
	D3DXVECTOR2 startVelocity;
	float tParam;
	//speed multiply with tParam to determine how many times to reach the destination
};