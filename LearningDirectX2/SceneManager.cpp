#include "SceneManager.h"

SceneManager *SceneManager::instance = NULL;

SceneManager * SceneManager::GetInstance() {
	if (instance == NULL)
		instance = new SceneManager();
	return instance;
}

SceneManager::SceneManager() {
	CurrentScene = NULL;
	timeTransition = 0;
	firstTime = true;
	destSceneID = DataManager::GetCurrentStage();
	hihi = 0;
	srand(time(NULL));

}

void SceneManager::CreateScene(int sceneID) {
	if (CurrentScene != NULL)
		delete CurrentScene;
	CurrentScene = NULL;
	switch (sceneID) {
	case 0:
		CurrentScene = new PlayScene();
		break;
	}
}

Scene * SceneManager::GetCurrentScene() {
	return CurrentScene;
}

void SceneManager::LoadScene(int sceneID) {
	destSceneID = sceneID;
	if (firstTime) {
		CreateScene(sceneID);
		firstTime = false;
	}
	else
		isTransitioning = true;
}


#include "Debug.h"

void SceneManager::UpdateTransition(double dt) {

	if (timeTransition > SCENE_TIME_TRANSITION) {
		CreateScene(destSceneID);
		timeTransition = 0;
		isTransitioning = false;
		DataManager::SetGameColor(D3DCOLOR_XRGB(255, 255, 255));
		return;
	}

	timeTransition += dt;
	DataManager::SetGameColor(D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255));
	DebugOut(L"random: %d", rand() % 255);
}

bool SceneManager::IsTransitioning() {
	return isTransitioning;
}

int SceneManager::GetSceneID() {
	return CurrentScene->GetSceneID();
}

SceneManager::~SceneManager() {
	delete CurrentScene;
	CurrentScene = NULL;
}
