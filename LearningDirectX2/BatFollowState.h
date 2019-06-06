#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class BatFollowState : public EnemyState {
public:
	BatFollowState(EnemyData *data);
	~BatFollowState();
	void ResetState() override;
	void Update(double dt) override;
};