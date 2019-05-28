#pragma once
#include "ItemState.h"
#include "Textures.h"
#include "Animation.h"

class ItemAvailableState : public ItemState {
public:
	ItemAvailableState(ItemData *data, Tag Tag);
	void ResetState() override;
	void Update(double dt) override;
	ItemState::State GetState() override;
};