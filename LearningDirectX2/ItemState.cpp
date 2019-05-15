#include "ItemState.h"
#include "Item.h"

ItemState::ItemState(ItemData *data) {
	itemData = data;
}

ItemState::~ItemState() {
	delete m_Animation;
	m_Animation = NULL;
}

void ItemState::Update(double dt) {
	if (m_Animation)
		m_Animation->Update(dt);
}

void ItemState::Render() {
	m_Animation->Render(itemData->item->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void ItemState::OnCollision(Entity * impactor, Entity::SideCollision side) {

}

void ItemState::ResetState() {
	m_Animation->ResetAnimation();
}

ItemState::State ItemState::GetState() {
	return ItemState::Holder;
}
