#pragma once
#include "Scene.h"
#include "Textures.h"
#include "GameMap.h"
#include "Entity.h"
#include "CollisionDetector.h"
#include "Player.h"
#include "CamBox.h"
#include "EnemyGroup.h"

class PlayScene : public Scene {

	DWORD showTime;
	DWORD showTimeRate;
	int win;

	GameMap *map;
	Camera *camera;
	Player *player;

public:
	PlayScene();
	virtual ~PlayScene();
	virtual void Render();
	virtual void ProcessInput();
	virtual void Update(double dt);
	void CheckCollision(double dt = 0.0167f);
	void CheckActive();
	void CheckCamera();
	void Reset();
};