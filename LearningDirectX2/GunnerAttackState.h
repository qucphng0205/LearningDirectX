#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include "Gunner.h"

class GunnerAttackState : public EnemyState {
public:
	GunnerAttackState(EnemyData *data);
	~GunnerAttackState();
	void ResetState() override;
	void Update(double dt) override;
};