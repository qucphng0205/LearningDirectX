#pragma once
class Item;
class ItemState;

class ItemData {
public:
	Item *item;
	ItemState *state;
	ItemData(Item *item) : item(item) {}
};