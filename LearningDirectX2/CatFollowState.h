#pragma once
#include "EnemyState.h"

class CatFollowState : public EnemyState {
public:
	CatFollowState(EnemyData *data);
	~CatFollowState();
	void ResetState() override;
	void Update(double dt) override;
};