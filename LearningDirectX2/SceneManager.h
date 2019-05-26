#pragma once
#include "Scene.h"
#include "DataManager.h"
#include "GameConfig.h"
#include "PlayScene.h"
#include <ctime>

class SceneManager {
public:
	static SceneManager *GetInstance();

	SceneManager();

	Scene* GetCurrentScene();
	void LoadScene(int sceneID);

	void UpdateTransition(double dt);
	
	bool IsTransitioning();

	~SceneManager();
private:
	void CreateScene(int sceneID);

	static SceneManager *instance;
	Scene *CurrentScene;
	float destSceneID;

	bool isTransitioning;
	bool firstTime;
	float timeTransition;

	int hihi;

};