#pragma once
#include "EnemyState.h"

class CatFollowState : public EnemyState {
public:
	CatFollowState(EnemyData *data);
	~CatFollowState();
	virtual void ResetState();
	virtual void Update(double dt);
};