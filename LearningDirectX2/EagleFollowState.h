#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class EagleFollowState : public EnemyState {
public:
	EagleFollowState(EnemyData *data);
	~EagleFollowState();
	void ResetState() override;
	void Update(double dt) override;
};