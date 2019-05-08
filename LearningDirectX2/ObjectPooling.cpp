#include "ObjectPooling.h"
#include <iterator>

ObjectPooling *ObjectPooling::instance = NULL;

ObjectPooling * ObjectPooling::GetInstance() {
	//USED TO BUG: su dung addKnife ma khong instantiate doi tuong ObjectPooling
	if (instance == NULL)
		instance = new ObjectPooling();
	return instance;
}

void ObjectPooling::AddKnife(int number) {
	Unit *unit;
	for (int i = 0; i < number; i++) {
		Knife* knife = new Knife();
		unit = new Unit(Grid::GetInstance(), knife);
		pool[KNIFE_POOL_INDEX].push_back(unit);
	}
	auto knives = pool[KNIFE_POOL_INDEX];
}

bool ObjectPooling::CheckQuantity(int index) {
	auto knives = pool[index];
	for (size_t i = 0; i < knives.size(); i++)
		if (!knives[i]->GetEntity()->IsActive())
			return true;
	return false;
}

bool ObjectPooling::InstantiateKnife(D3DXVECTOR3 position) {
	auto knives = pool[KNIFE_POOL_INDEX];
	for (size_t i = 0; i < knives.size(); i++) {
		Knife *knife = (Knife*)knives[i]->GetEntity();
		if (!knife->IsActive()) {
			knife->Instantiate(position);
			knives[i]->Move(knife->GetPosition());
			return true;
		}
	}
	return false;
}

ObjectPooling::ObjectPooling() {
	if (instance != NULL)
		delete this;
	instance = this;
}
