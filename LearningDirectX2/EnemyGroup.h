#pragma once
#include "ObjectGroup.h"
#include "BoxCollider.h"
#include "Enemy.h"

class EnemyGroup : public ObjectGroup {
public:
	EnemyGroup();
	virtual void CheckActive(Camera *cam, D3DXVECTOR2 velocity);
	virtual void Update(double dt);
	virtual void Render();
};