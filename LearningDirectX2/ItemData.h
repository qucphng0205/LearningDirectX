#pragma once
class ItemState;
class Item;

class ItemData {
public:
	Item *item;
	ItemState *state;
	ItemData(Item *item) : item(item) {}
};