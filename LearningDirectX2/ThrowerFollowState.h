#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include <ctime>

class ThrowerFollowState : public EnemyState {
public:
	ThrowerFollowState(EnemyData *data);
	~ThrowerFollowState();
	virtual void ResetState();
	virtual void Update(double dt);
private:
	float my_PrecentTime;
};