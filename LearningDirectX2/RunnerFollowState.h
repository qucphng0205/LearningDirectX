#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class RunnerFollowState : public EnemyState {
public:
	RunnerFollowState(EnemyData *data);
	~RunnerFollowState();
	virtual void ResetState();
	virtual void Update(double dt);
};