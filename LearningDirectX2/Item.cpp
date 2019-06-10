#include "Item.h"
#include "ItemHolderState.h"
#include "ItemAvailableState.h"

Item::Item(int stage, enum Tag Tag) {
	type = Layer::ItemHolderType;
	this->Tag = Tag;
	itemData = new ItemData(this);
	auto textures = Textures::GetInstance();
	textures->Add(TEX_HOLDER, "Resources/Sprites/holderspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	textures->Add(TEX_ITEM, "Resources/Sprites/itemspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	itemHolderState = new ItemHolderState(itemData, stage);
	itemAvailableState = new ItemAvailableState(itemData, Tag);

	isDisappeared = false;
	isActive = false;
}

Item::~Item() {
	delete itemData;
	itemData = NULL;
	delete itemHolderState;
	itemHolderState = NULL;
	delete itemAvailableState;
	itemAvailableState = NULL;
}

void Item::Update(double dt) {
	if (isActive)
		itemData->state->Update(dt);
	Entity::Update(dt);
}

void Item::Render() {
	itemData->state->Render();
}

void Item::SetState(ItemState::State state) {
	if (state == ItemState::Holder)
		itemData->state = itemHolderState;
	else {
		itemData->state = itemAvailableState;
		type = Layer::ItemAvailableType;
	}
	itemData->state->ResetState();
}

void Item::SetColliderTop(int top) {
	collider.top = top;
}

void Item::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -left;
}

void Item::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Item::SetColliderRight(int right) {
	collider.right = right;
}

ItemState::State Item::GetState() {
	return itemData->state->GetState();
}

bool Item::IsAvailable() {
	return GetState() == ItemState::Available;
}

void Item::SetSpawnBox(BoxCollider box) {
	position = D3DXVECTOR3(box.GetCenter());
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
}

BoxCollider Item::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

BoxCollider Item::GetSpawnRect() {
	return spawnBox;
}

void Item::SetActive(bool active) {

	if (active == isActive)
		return;
	
	if (active && !isDisappeared)
		//BUG
		Spawn();
	else
		MakeInactive();
}

float Item::GetWidth() {
	return collider.right - collider.left;
}

float Item::GetHeight() {
	return collider.top - collider.bottom;
}

void Item::OnCollision(Entity * impactor, SideCollision side, float collisionTime, double dt) {
	if (!itemData->state->GetState() == ItemState::Available)
		return;
	if (side == Entity::Bottom && impactor->GetType() == Layer::StaticType) {
		velocity.y *= collisionTime;
		onGround = true;
	}
}

void Item::MakeInactive() {
	isActive = false;
	if (itemData->state->GetState() == ItemState::Available)
		isDisappeared = true;
}

void Item::Spawn() {
	isActive = true;
	SetState(ItemState::Holder);
}

EarnedData Item::OnDestroy() {
	if (itemData->state->GetState() == ItemState::Available) {
		SetActive(false);
		gnhpSound::GetInstance()->PlayFX(SOUND_EATITEM);
		return EarnedData(Tag);
	}
	SetState(ItemState::Available);
	return EarnedData(0);
}
