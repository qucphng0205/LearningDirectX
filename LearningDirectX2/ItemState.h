#pragma once
#include "Entity.h"
#include "Animation.h"
#include "ItemData.h"
#include "GameConfig.h"

class ItemState {
public:
	enum State {
		Holder,
		Available
	};
	ItemState(ItemData *data);
	~ItemState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60);
	virtual void ResetState();
	virtual State GetState();
protected:
	Animation *m_Animation;
	ItemData *itemData;
};
