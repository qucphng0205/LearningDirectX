#include "ItemAvailableState.h"
#include "Item.h"

ItemAvailableState::ItemAvailableState(ItemData *data, Tag Tag) : ItemState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_ITEM);
	m_Animation = new Animation();

	int startItemTag = SPIRITPOINTS5;

	//startItemTag = 8, start point
	//item = 9 or item = 10 
	//item 9: 9 - 8 + 1 = 2
	//item 10: 10 - 8 + 1 = 3
	//yeu cau: spritesheet phai sap xep dung thu tu
	int myItemIndex = Tag - startItemTag + 1;
	m_Animation->AddFramesA(texture, myItemIndex, myItemIndex, 1, 9, 1, 100 * (1 / 60));

	//switch (Tag) {
	//case SPIRITPOINTS5:
	//	m_Animation->AddFramesA(texture, 1, 1, 1, 9, 1, 100 * (1.0 / 60));
	//	break;
	//case Entity::SpiritPoints10:
	//	break;
	//case Entity::Scores500:
	//	break;
	//case Entity::Scores1000:
	//	break;
	//case Entity::TimeFreeze:
	//	break;
	//case Entity::Health:
	//	break;
	//case Entity::ThrowingStar:
	//	break;
	//case Entity::WindmillStar:
	//	break;
	//case Entity::Flames:
	//	break;
	//}
}

void ItemAvailableState::ResetState() {
	//auto item = itemData->item;
}

void ItemAvailableState::Update(double dt) {
	m_Animation->Update(dt);
	if (!itemData->item->onGround)
		itemData->item->AddVy(-CAT_GRAVITY);
}

ItemState::State ItemAvailableState::GetState() {
	return ItemState::Available;
}
