#include "GameManager.h"

GameManager::GameManager(HWND hWnd, HINSTANCE hInstance) {
	Graphic::GetInstance()->Init(hWnd);
	KeyBoard::GetInstance()->InitKeyboard(hWnd, hInstance);
	SceneManager::GetInstance()->LoadScene(DataManager::GetCurrentStage());
	this->hWnd = hWnd;
	this->hInstance = hInstance;
}

GameManager::~GameManager() {
	delete Graphic::GetInstance();
	delete KeyBoard::GetInstance();
	delete SceneManager::GetInstance();
}

void GameManager::Update(double dt) {
	hihi += dt;
	if ((int)hihi > 10) {
		SceneManager::GetInstance()->LoadScene(DataManager::GetCurrentStage());
		hihi = 0;
	}
	//neu khong chuyen canh thi update
	/*if (!SceneManager::GetInstance()->isSceneTransitioning())
		SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
	else {
		SceneTransition::GetInstance()->Update();
		SceneManager::GetInstance()->UpdateWithEffect();
	}*/
	SceneManager *sceneManager = SceneManager::GetInstance();

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

