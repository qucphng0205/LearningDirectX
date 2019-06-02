#pragma once
#include "Camera.h"
#include "Grid.h"
#include "Sparta.h"
#include "Cat.h"
#include "Thrower.h"
#include "Eagle.h"
#include "Soldier.h"
#include "Unit.h"
#include "Item.h"
#include "Tag.h"
#include "Gunner.h"
#include "Runner.h"
#include "Basaquer.h"
#include <iostream>
#include <fstream>

class Tileset {
	int tileWidth;
	int tileHeight;
	int rows;
	int columns;
	unordered_map<int, LPSPRITE> tiles;
public:
	Tileset(int rows, int columns, int tileWidth, int tileHeight);
	void Add(int id, LPSPRITE tile);
	int GetRows();
	int GetColumns();
	int GetTileWidth();
	int GetTileHeight();
	LPSPRITE GetSprite(int id);
};

class GameMap {
public:
	GameMap(char* tilesetPath, char* mapPath, int tileHeight = 32, int tileWidth = 32);
	void SetMapPath(char *mapPath);
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	Grid *GetGrid();
	void SetCamera(Camera *cam);
	void Draw();
	//Active objects
	//void GetStaticObjects(std::vector<Entity*> &entities);
	~GameMap();
private:
	Grid *grid;
	void LoadTileset(char *filePath, int tileWidth, int tileHeight);
	Tileset *tileset;
	LPCSTR mapPath;
	int rows;
	int columns;
	int mapObject;
	int **mapIDs;
	std::unordered_map<int, LPSPRITE> listTileset;
	Camera *camera;
};