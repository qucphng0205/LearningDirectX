#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class KnifeRotateState : public EnemyState {
public:
	KnifeRotateState(EnemyData *data);
	~KnifeRotateState();
	virtual void ResetState();
	virtual void Update(double dt);
};