#pragma once
#include "ItemState.h"
#include "Textures.h"
#include "Animation.h"

class ItemHolderState : public ItemState {
public:
	ItemHolderState(ItemData *data, int sTage);
	virtual void ResetState();
	virtual void Update(double dt);
	virtual State GetState();
};