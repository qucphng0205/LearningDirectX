#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include "Soldier.h"

class SoldierAttackState : public EnemyState {
public:
	SoldierAttackState(EnemyData *data);
	~SoldierAttackState();
	virtual void ResetState();
	virtual void Update(double dt);
private:
	int frame;
};