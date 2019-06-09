#pragma once
#include "Scene.h"
#include "GameMap.h"
#include "Player.h"
#include "ObjectPooling.h"
#include "DataManager.h"

class IntroScene : public Scene {
private:
	Animation *animation;
	std::string text1;
	std::string text2;
	std::string text3;
	std::string animtext2;
	//for text2
	float timeToText;
	//for text3
	float timeToShow;
	bool showText3;

	RECT zone1;
	RECT zone2;
	RECT zone3;

public:
	IntroScene();
	~IntroScene();
	void Render() override;
	void ProcessInput() override;
	void Update(double dt) override;
	int GetSceneID() override;
};