#pragma once
#include "Entity.h"
#include "ItemData.h"
#include "GameConfig.h"
#include "Camera.h"
#include "ItemState.h"

class Item : public Entity {
public:

	enum ItemState {
		Unavailable,
		Available
	};


	Item();
	~Item();

	virtual void Update(double dt);
	virtual void Render();

	//Get real rect in world 
	virtual BoxCollider GetRect();
	//Get spawn box in world
	virtual BoxCollider GetSpawnRect();

	virtual void SetActive(bool active);
	//= SetCollider
	virtual void SetSpawnBox(BoxCollider box, int direction);
	virtual float GetWidth();
	virtual float GetHeight();
	virtual void OnCollision(Entity *impactor, SideCollision side, float collisionTime);
	virtual void MakeInactive();
	virtual void Spawn();

protected:

	ItemState state;

	D3DXVECTOR3 spawnPosition;
	BoxCollider spawnBox;
	float collisionTime;
	SideCollision side;
	ItemData *itemData;
};


