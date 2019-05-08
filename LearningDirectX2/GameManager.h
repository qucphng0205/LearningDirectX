#pragma once

#include "SceneManager.h"
#include "PlayScene.h"

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