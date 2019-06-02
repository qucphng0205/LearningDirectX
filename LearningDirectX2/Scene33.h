#pragma once
#include "Scene.h"
#include "GameMap.h"
#include "Player.h"
#include "ObjectPooling.h"
#include "DataManager.h"

class Scene33 : public Scene {

	DWORD showTime;
	DWORD showTimeRate;

	GameMap *map;
	Camera *camera;
	Player *player;

	float timeLeft;

	float timeScale;
	float earnRewardTime;

public:

	Scene33();
	~Scene33();
	void Render() override;
	void ProcessInput() override;
	void Update(double dt) override;
	int GetSceneID() override;
	void CheckCollision(double dt = 0.0167f);
	void CheckActive();
	void CheckCamera();
	void CheckTransitionScene();
	void EarnReward(double dt);
	void Reset();
};