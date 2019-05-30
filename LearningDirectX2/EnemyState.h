#pragma once
#include "GameConfig.h"
#include "Animation.h"
#include "EnemyData.h"
#include "Entity.h"

class EnemyState {
public:
	enum State {
		Follow,
		Attack,
		Rotate
	};
	EnemyState(EnemyData *data);
	EnemyState();
	virtual ~EnemyState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTIme, double dt = 1.0/60);
	virtual void ResetState();
protected:
	Animation *m_Animation;
	EnemyData *enemyData;
};
