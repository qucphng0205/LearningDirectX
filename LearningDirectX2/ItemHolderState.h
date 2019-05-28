#pragma once
#include "ItemState.h"
#include "Textures.h"
#include "Animation.h"

class ItemHolderState : public ItemState {
public:
	ItemHolderState(ItemData *data, int stage);
	void ResetState() override;
	void Update(double dt) override;
	ItemState::State GetState() override;
};