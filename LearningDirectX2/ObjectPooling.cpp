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
}

bool ObjectPooling::CheckQuantity(int index) {
	auto knives = pool[index];
	for (size_t i = 0; i < knives.size(); i++)
		if (!knives[i]->GetEntity()->IsActive())
			return true;
	return false;
}

bool ObjectPooling::Instantiate(int index, D3DXVECTOR3 position) {
	auto weapons = pool[index];
	for (size_t i = 0; i < weapons.size(); i++) {
		Weapon *weapon = (Knife*)weapons[i]->GetEntity();
		if (!weapon->IsActive()) {
			weapon->Instantiate(position);
			weapons[i]->Move(weapon->GetPosition());
			return true;
		}
	}
	return false;
}

void ObjectPooling::AddBullet(int number) {
	Unit *unit;
	for (int i = 0; i < number; i++) {
		Bullet* bullet = new Bullet();
		unit = new Unit(Grid::GetInstance(), bullet);
		pool[BULLET_POOL_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddShuriken(int number) {
	Unit *unit;
	for (int i = 0; i < number; i++) {
		Shuriken* bullet = new Shuriken();
		unit = new Unit(Grid::GetInstance(), bullet);
		pool[BULLET_POOL_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddBigShuriken(int number) {
}

void ObjectPooling::AddFlames(int number) {
}

ObjectPooling::ObjectPooling() {
	if (instance != NULL)
		delete this;
	instance = this;
}
