#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class SoldierFollowState : public EnemyState {
public:
	SoldierFollowState(EnemyData *data);
	~SoldierFollowState();
	void ResetState() override;
	void Update(double dt) override;
};