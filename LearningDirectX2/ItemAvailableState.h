#pragma once
#include "ItemState.h"
#include "Textures.h"
#include "Animation.h"

class ItemAvailableState : public ItemState {
public:
	ItemAvailableState(ItemData *data, Entity::EntityTag tag);
	virtual void ResetState();
	virtual void Update(double dt);
	virtual State GetState();
};