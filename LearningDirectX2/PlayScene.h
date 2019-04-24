#pragma once
#include "Scene.h"
#include "Textures.h"
#include "GameMap.h"
#include "Entity.h"
#include "CollisionDetector.h"
#include "Player.h"

class PlayScene : public Scene {

	LPDIRECT3DTEXTURE9 player1_win_texture;
	LPDIRECT3DTEXTURE9 player2_win_texture;

	DWORD showTime;
	DWORD showTimeRate;
	int win;

	GameMap *map;
	Camera *camera;
	Player *player;

public:
	PlayScene();
	virtual ~PlayScene();
	virtual void Render();
	virtual void ProcessInput();
	virtual void Update(double dt);
	void CheckCollision(double dt = 0.0167f);
	void CheckCamera();
	void Reset();
};