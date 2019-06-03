#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include "gnhpSound.h"

class BasaquerIdleState : public EnemyState {
public:
	BasaquerIdleState(EnemyData *data);
	~BasaquerIdleState();
	void ResetState() override;
	void Update(double dt) override;
private:
	float speed;
};