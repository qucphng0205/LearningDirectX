#pragma once
#include "Scene.h"
#include "DataManager.h"
#include "GameConfig.h"
#include "PlayScene.h"
#include "Scene32.h"
#include "Scene33.h"
#include "EndGame.h"
#include "GameOver.h"
#include "gnhpSound.h"
#include <ctime>

class SceneManager {
public:
	enum TransitionType {
		ToGameOverTo,
		Reload,
		Next,
	};

	static SceneManager *GetInstance();

	SceneManager();

	Scene* GetCurrentScene();
	void LoadScene(int sceneID, TransitionType type = Reload);

	void UpdateTransition(double dt);
	
	bool IsTransitioning();

	int GetSceneID();

	~SceneManager();
private:
	void CreateScene(int sceneID);

	static SceneManager *instance;
	Scene *CurrentScene;
	float destSceneID;

	bool isTransitioning;
	TransitionType type;
	bool firstTime;
	float timeTransition;

	int hihi;

};