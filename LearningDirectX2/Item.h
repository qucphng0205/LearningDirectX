#pragma once
#include "Entity.h"
#include "ItemData.h"
#include "GameConfig.h"
#include "Camera.h"
#include "ItemState.h"
#include "Textures.h"

class Item : public Entity {
public:

	Item(int stage, enum Tag Tag);
	~Item();

	virtual void Update(double dt);
	virtual void Render();

	virtual void SetState(ItemState::State state);
	virtual ItemState::State GetState();
	virtual bool IsAvailable();

	virtual void SetSpawnBox(BoxCollider box);
	//Get real rect in world 
	virtual BoxCollider GetRect();
	//Get spawn box in world
	virtual BoxCollider GetSpawnRect();

	virtual void SetActive(bool active);

	virtual float GetWidth();
	virtual float GetHeight();
	virtual void OnCollision(Entity *impactor, SideCollision side, float collisionTime);
	virtual void MakeInactive();
	virtual void Spawn();
	virtual EarnedData OnDestroy();
	bool onGround;

protected:
	int stage;
	bool isDisappeared;
	BoxCollider collider;
	D3DXVECTOR3 spawnPosition;
	BoxCollider spawnBox;
	float collisionTime;
	SideCollision side;
	ItemData *itemData;
	ItemState *itemHolderState, *itemAvailableState;
};


