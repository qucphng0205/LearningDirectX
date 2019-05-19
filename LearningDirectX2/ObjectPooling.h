#pragma once
#include "Knife.h"
#include "Bullet.h"
#include "Shuriken.h"
#include "BigShuriken.h"
#include "Unit.h"
#include <map>
#include <vector>

class ObjectPooling {
public:
	static ObjectPooling *GetInstance();
	ObjectPooling();
	void AddKnife(int number = KNIFE_QUANTITY);
	void AddBullet(int number = BULLET_QUANTITY);
	void AddShuriken(int number = SHURIKEN_QUANTITY);
	void AddBigShuriken(int number = BIGSHURIKEN_QUANTITY);
	void AddFlames(int number = FLAMES_QUANTITY);
	bool CheckQuantity(int index);
	bool Instantiate(int index, D3DXVECTOR3 position);
private:
	static ObjectPooling *instance;
	//dictionary like objectPooling pattern in unity
	std::map<int, std::vector<Unit*>> pool;
};