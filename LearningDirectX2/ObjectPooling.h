#pragma once
#include "Knife.h"
#include "Unit.h"
#include <map>
#include <vector>

class X {
public:
	int x;
	X() { x = 0; }
};

class ObjectPooling {
public:
	static ObjectPooling *GetInstance();
	ObjectPooling();
	void AddKnife(int number = KNIFE_QUANTITY);
	bool CheckQuantity(int index);
	bool InstantiateKnife(D3DXVECTOR3 position);
	//void AddBullet(int number = BULLET_QUANTITY);
private:
	static ObjectPooling *instance;
	//dictionary like objectPooling pattern in unity
	std::map<int, std::vector<Unit*>> pool;
};