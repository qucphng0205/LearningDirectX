#include "ItemHolderState.h"
#include "Item.h"

ItemHolderState::ItemHolderState(ItemData *data, int stage) : ItemState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_HOLDER);
	m_Animation = new Animation();
	//stage = 0 means stage 3-1, 1 means stage 3-2, 2 means stage 3-3, boss
	if (stage == 0) 
		m_Animation->AddFramesA(texture, 1, 1, 2, 2, 2, HOLDER_FRAME * (1 / 60.0f));
	else
		m_Animation->AddFramesA(texture, 2, 2, 2, 2, 2, HOLDER_FRAME * (1 / 60.0f));
}

void ItemHolderState::ResetState() {
	auto item = itemData->item;
	item->onGround = false;
}

void ItemHolderState::Update(double dt) {
	m_Animation->Update(dt);
}

ItemState::State ItemHolderState::GetState() {
	return ItemState::Holder;
}
