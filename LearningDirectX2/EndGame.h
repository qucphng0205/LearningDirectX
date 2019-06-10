#pragma once
#include "Scene.h"
#include "GameMap.h"
#include "Player.h"
#include "ObjectPooling.h"
#include "DataManager.h"

class EndGame : public Scene {
private:
	BoxCollider zone1Box;
	std::string text1;
	float speed;
public:
	EndGame();
	~EndGame();
	void Render() override;
	void ProcessInput() override;
	void Update(double dt) override;
	int GetSceneID() override;
};