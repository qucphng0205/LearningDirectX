#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class GunnerFollowState : public EnemyState {
public:
	GunnerFollowState(EnemyData *data);
	~GunnerFollowState();
	void ResetState() override;
	void Update(double dt) override;
};