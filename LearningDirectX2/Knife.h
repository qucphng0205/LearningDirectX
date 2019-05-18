#pragma once
#include "Weapon.h"
#include "Animation.h"
#include "KnifeRotateState.h"

class Knife : public Weapon {
public:
	Knife();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Update(double dt);
	virtual void Instantiate(D3DXVECTOR3 position);
private:
	//purpose: linear interpolation
	D3DXVECTOR2 startVelocity;
	float tParam;
	//speed multiply with tParam to determine how many times to reach the destination
};