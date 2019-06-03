#pragma once
#include "Scene.h"
#include "GameMap.h"
#include "Player.h"
#include "ObjectPooling.h"
#include "DataManager.h"
#include "gnhpSound.h"

class Scene32 : public Scene {

	DWORD showTime;
	DWORD showTimeRate;

	GameMap *map;
	Camera *camera;
	Player *player;

	float timeLeft;

public:

	Scene32();
	~Scene32();
	void Render() override;
	void ProcessInput() override;
	void Update(double dt) override;
	int GetSceneID() override;
	void CheckCollision(double dt = 0.0167f);
	void CheckActive();
	void CheckCamera();
	void CheckTransitionScene();
	void Reset();
};