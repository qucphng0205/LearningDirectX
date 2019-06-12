#pragma once

#include "SceneManager.h"
#include "Graphic.h"
#include "KeyBoard.h"

class GameManager {

	HWND hWnd;
	HINSTANCE hInstance;
public:
	GameManager(HWND hWnd, HINSTANCE hInstance);
	~GameManager();
	void ProcessInput();
	void Update(double dt);
	void Render();
private:
	double hihi;
	bool isPause;
	SceneManager *sceneManager;
	KeyBoard *keyboard;
	Graphic *graphic;
};