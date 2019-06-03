#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include "Soldier.h"

#include "gnhpSound.h"

class SoldierAttackState : public EnemyState {
public:
	SoldierAttackState(EnemyData *data);
	~SoldierAttackState();
	void ResetState() override;
	void Update(double dt) override;
private:
	int frame;
};