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

	void Update(double dt) override;
	void Render() override;

	void SetState(ItemState::State state);
	ItemState::State GetState();
	bool IsAvailable();

	void SetSpawnBox(BoxCollider box);
	//Get real rect in world 
	BoxCollider GetRect() override;
	//Get spawn box in world
	BoxCollider GetSpawnRect();

	void SetActive(bool active) override;

	float GetWidth() override;
	float GetHeight() override;
	void OnCollision(Entity *impactor, SideCollision side, float collisionTime, double dt = 1.0/60) override;
	void MakeInactive();
	void Spawn();
	EarnedData OnDestroy() override;
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


