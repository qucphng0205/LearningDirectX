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
	switch (type) {
	case ToGameOverTo:
		DataManager::HandleGameOver();
		break;
	case Reload:
		DataManager::HandleReload();
		break;
	case Next:
		break;
	}
	switch (sceneID) {
	case 0: 
		CurrentScene = new IntroScene();
		break;
	case 1:
		CurrentScene = new PlayScene();
		break;
	case 2:
		CurrentScene = new Scene32();
		break;
	case 3:
		CurrentScene = new Scene33();
		break;
	case 4:
		CurrentScene = new EndGame();
		break;
	case 5:
		CurrentScene = new GameOver();
		break;
	}
	
}

Scene * SceneManager::GetCurrentScene() {
	return CurrentScene;
}

void SceneManager::LoadScene(int sceneID, TransitionType type) {
	destSceneID = sceneID;
	this->type = type;
	if (firstTime) {
		CreateScene(sceneID);
		firstTime = false;
	}
	else
		isTransitioning = true;
	if (type == TransitionType::Reload || (type == TransitionType::ToGameOverTo && sceneID == GAMEOVER_SCENE)) {
		gnhpSound::GetInstance()->StopMusic();
		gnhpSound::GetInstance()->PlayFX(SOUND_GAMEOVER);
	}
}


void SceneManager::UpdateTransition(double dt) {

	auto previousStage = DataManager::GetPreviousStage();

	if ((previousStage == INTRO_SCENE || previousStage == GAMEOVER_SCENE || previousStage == ENDGAME_SCENE) && type == TransitionType::Next)
		timeTransition = SCENE_TIME_TRANSITION + 1;

	if (timeTransition > SCENE_TIME_TRANSITION) {
		CreateScene(destSceneID);
		timeTransition = 0;
		isTransitioning = false;
		DataManager::SetGameColor(D3DCOLOR_XRGB(255, 255, 255));
		return;
	}

	timeTransition += dt;
	DataManager::SetGameColor(D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255));
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
