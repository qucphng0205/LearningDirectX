#pragma once
#include "Scene.h"
#include "DataManager.h"

class SceneManager {
public:
	static SceneManager *GetInstance();
	void CreateScene(Scene *scene);
	Scene* GetCurrentScene();
	void LoadScene(Scene *scene);
	~SceneManager();
private:
	static SceneManager *instance;
	Scene *CurrentScene;
	Scene *DestScene;
	bool isTransitioning;
};