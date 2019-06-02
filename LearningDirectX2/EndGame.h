#pragma once
#include "Scene.h"
#include "GameMap.h"
#include "Player.h"
#include "ObjectPooling.h"
#include "DataManager.h"

class EndGame : public Scene {

public:
	EndGame();
	~EndGame();
	void Render() override;
	void ProcessInput() override;
	void Update(double dt) override;
	int GetSceneID() override;
};