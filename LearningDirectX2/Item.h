#pragma once
#include "Entity.h"
#include "ItemData.h"
#include "GameConfig.h"
#include "Camera.h"
#include "ItemState.h"
#include "Textures.h"

class Item : public Entity {
public:
	//enum ItemType {
	//	SpiritPoints5,
	//	SpiritPoints10,
	//	Scores500,
	//	Scores1000,
	//	TimeFreeze,
	//	Health,
	//	ThrowingStar,
	//	WindmillStar,
	//	Flames
	//};

	Item(int stage, EntityTag tag);
	~Item();

	virtual void Update(double dt);
	virtual void Render();

	virtual void SetState(ItemState::State state);

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
	virtual void OnDestroy();
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


