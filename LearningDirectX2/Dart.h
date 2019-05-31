#pragma once
#include "Weapon.h"
#include "Player.h"

class Dart : public Weapon {
public:
	static int quantity;

	Dart();
	~Dart();
	void Update(double dt) override;
	void Instantiate(D3DXVECTOR3 position) override;

private:
	int index;
	float delay;
};