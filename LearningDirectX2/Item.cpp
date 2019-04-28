#include "Item.h"

Item::Item() {
	type = Entity::ItemType;
	itemData = new ItemData(this);
}

Item::~Item() {
}

void Item::Update(double dt) {
	itemData->state->Update(dt);
}
