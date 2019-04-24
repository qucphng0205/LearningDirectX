#pragma once

#include "SceneManager.h"
#include "PlayScene.h"
#include "Graphic.h"
#include "KeyBoard.h"
#define FPS 60;

class GameManager {

	HWND hWnd;
	HINSTANCE hInstance;
public:
	GameManager(HWND hWnd, HINSTANCE hInstance);
	~GameManager();
	void ProcessInput();
	void Update(double dt);
	void Render();
};