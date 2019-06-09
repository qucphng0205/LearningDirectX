#include "GameManager.h"

GameManager::GameManager(HWND hWnd, HINSTANCE hInstance) {
	graphic = Graphic::GetInstance();
	sceneManager = SceneManager::GetInstance();
	keyboard = KeyBoard::GetInstance();

	graphic->Init(hWnd);
	keyboard->InitKeyboard(hWnd, hInstance);
	gnhpSound::GetInstance()->LoadSound(hWnd);

	sceneManager->LoadScene(DataManager::GetCurrentStage(), SceneManager::TransitionType::Next);

	this->hWnd = hWnd;
	this->hInstance = hInstance;
}

GameManager::~GameManager() {
	delete graphic;
	graphic = NULL;
	delete keyboard;
	keyboard = NULL;
	delete sceneManager;
	sceneManager = NULL;
}

void GameManager::Update(double dt) {
	//--DEBUG
	////hihi += dt;
	//if (DataManager::GetCurrentStage() == 0)
	//	DataManager::SetCurrentStage(1);

	bool otherScene = sceneManager->GetSceneID() != DataManager::GetCurrentStage();
	bool playerDead = DataManager::IsDeath();

	if (otherScene && DataManager::GetCurrentStage() == GAMEOVER_SCENE)
		sceneManager->LoadScene(DataManager::GetCurrentStage(), SceneManager::TransitionType::ToGameOverTo);
	else if (playerDead)
		sceneManager->LoadScene(DataManager::GetCurrentStage(), SceneManager::TransitionType::Reload);
	else if (otherScene)
		sceneManager->LoadScene(DataManager::GetCurrentStage(), SceneManager::TransitionType::Next);

	if (!sceneManager->IsTransitioning())
		sceneManager->GetCurrentScene()->Update(dt);
	else
		sceneManager->UpdateTransition(dt);
}

void GameManager::Render() {
	auto device = Graphic::GetInstance()->Getdirect3DDevice();
	auto spriteHandler = Graphic::GetInstance()->GetSpriteHandler();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackColor(), 0.0f, 0);
	/*if (!SceneManager::GetInstance()->isSceneTransitioning())
	SceneManager::GetInstance()->GetCurrentScene()->Render();*/
	//RENDER
	{
		device->BeginScene();

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		scene->Render();

		spriteHandler->End();

		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);

}

void GameManager::ProcessInput() {
	KeyBoard::GetInstance()->ProcessKeyboard();
}

