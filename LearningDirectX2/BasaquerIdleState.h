#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class BasaquerIdleState : public EnemyState {
public:
	BasaquerIdleState(EnemyData *data);
	~BasaquerIdleState();
	virtual void ResetState();
	virtual void Update(double dt);
private:
	float speed;
};