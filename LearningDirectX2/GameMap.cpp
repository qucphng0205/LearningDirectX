#include "GameMap.h"

Tileset::Tileset(int rows, int columns, int tileWidth, int tileHeight) {
	this->rows = rows;
	this->columns = columns;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
}

void Tileset::Add(int id, LPSPRITE tile) {
	tiles[id] = tile;
}

int Tileset::GetRows() {
	return rows;
}

int Tileset::GetColumns() {
	return columns;
}

int Tileset::GetTileWidth() {
	return tileWidth;
}

int Tileset::GetTileHeight() {
	return tileHeight;
}

LPSPRITE Tileset::GetSprite(int id) {
	return tiles[id];
}
//GameMap::GameMap() {
//	auto bufferWidth = Graphic::GetInstance()->GetBackBufferWidth();
//	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();
//	grid = new Grid(MyHelper::ToRect(0, bufferWidth, 0, bufferHeight), 1, 1);
//}
//
//GameMap::GameMap(char * tilesetPath, int tileWidth, int tileHeight) {
//}

GameMap::GameMap(char * tilesetPath, char * mapPath, int tileHeight, int tileWidth, bool gridBuildIn) {
	LoadTileset(tilesetPath, tileWidth, tileHeight);
	if (gridBuildIn)
		SetMapPathGridBuildIn(mapPath);
	else
		SetMapPath(mapPath);
}

void GameMap::SetMapPath(char * mapPath) {
	this->mapPath = mapPath;
	std::fstream reader(mapPath);
	if (reader.fail()) {
		return;
	}
	reader >> rows;
	reader >> columns;
	mapIDs = new int*[rows];

	for (int i = 0; i < rows; i++) {
		mapIDs[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			reader >> mapIDs[i][j];
		}
	}

	BoxCollider gridRect = BoxCollider(GetHeight(), 0, 0, GetWidth());

	switch (DataManager::GetCurrentStage()) {
	case BOSS_STAGE:
		grid = new Grid(gridRect, GRID_COLUMN_STAGE33, GRID_ROW_STAGE33);
		break;
	case BOSS_STAGE-1:
		grid = new Grid(gridRect, GRID_COLUMN_STAGE32, GRID_ROW_STAGE32);
		break;
	default:
		grid = new Grid(gridRect);
		break;
	}

	reader >> mapObject;
	int id = 0;
	int i = 0;
	int posx = 0;
	int posy = 0;
	int wid = 0;
	int hei = 0;
	int direction = 1;

	Unit *unit;
	for (int i = 0; i < mapObject; i++) {
		reader >> id;
		reader >> posx;
		reader >> posy;
		reader >> wid;
		reader >> hei;
		reader >> direction;

		if (id == (int)Tag::GROUND || id == (int)Tag::LADDER || id == (int)Tag::THINSURFACE) {
			Entity *ground = new Entity();
			ground->SetTag((Tag)id);
			ground->SetType(Layer::StaticType);
			ground->SetStatic(true);
			ground->SetPosition(D3DXVECTOR3(posx + wid / 2, posy - hei / 2, 0));
			ground->SetWidth(wid);
			ground->SetHeight(hei);
			ground->SetMoveDirection((Entity::EntityDirection)direction);
			grid->AddStaticObject(ground);
			continue;
		}

		BoxCollider box;
		box.top = posy;
		box.left = posx;
		box.bottom = posy - hei;
		box.right = posx + wid;

		//--DEBUG
		//continue; 


		switch (id) {
		case SPARTA:
		{
			Sparta *sparta = new Sparta();
			sparta->SetSpawnBox(box, direction);
			unit = new Unit(grid, sparta);
		}
		break;
		case CAT:
		{
			Cat *cat = new Cat();
			cat->SetSpawnBox(box, direction);
			unit = new Unit(grid, cat);
		}
		break;
		case THROWER:
		{
			Thrower *thrower = new Thrower();
			thrower->SetSpawnBox(box, direction);
			unit = new Unit(grid, thrower);
		}
		break;
		case EAGLE:
		{
			Eagle *eagle = new Eagle();
			eagle->SetSpawnBox(box, direction);
			unit = new Unit(grid, eagle);
		}
		break;
		case SOLDIER:
		{
			Soldier *soldier = new Soldier();
			soldier->SetSpawnBox(box, direction);
			unit = new Unit(grid, soldier);
		}
		break;
		case GUNNER:
		{
			Gunner *gunner = new Gunner();
			gunner->SetSpawnBox(box, direction);
			unit = new Unit(grid, gunner);
		}
		break;
		case RUNNER:
		{
			Runner *runner = new Runner();
			runner->SetSpawnBox(box, direction);
			unit = new Unit(grid, runner);
		}
		break;
		case BASAQUER:
		{
			Basaquer *basaquer = new Basaquer();
			basaquer->SetSpawnBox(box, direction);
			unit = new Unit(grid, basaquer);
		}
		break;
		case BAT:
		{
			Bat *bat = new Bat();
			bat->SetSpawnBox(box, direction);
			unit = new Unit(grid, bat);
		}
		break;
		default:
		{
			Item *item = new Item(DataManager::GetCurrentStage(), (Tag)id);
			item->SetSpawnBox(box);
			unit = new Unit(grid, item);
		}
		}
	}
}

void GameMap::SetMapPathGridBuildIn(char * mapPath) {
	this->mapPath = mapPath;
	std::fstream reader(mapPath);
	if (reader.fail()) {
		return;
	}
	reader >> rows;
	reader >> columns;
	mapIDs = new int*[rows];

	for (int i = 0; i < rows; i++) {
		mapIDs[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			reader >> mapIDs[i][j];
		}
	}

	int gridColumns = 1;
	int gridRows = 1;

	reader >> gridColumns;
	reader >> gridRows;


	BoxCollider gridRect = BoxCollider(GetHeight(), 0, 0, GetWidth());
	if (DataManager::GetCurrentStage() != 0) {
		grid = new Grid(gridRect, 1, 1);
	}
	else
		grid = new Grid(gridRect, gridColumns, gridRows);

	reader >> mapObject;
	int id = 0;
	int i = 0;
	int posx = 0;
	int posy = 0;
	int wid = 0;
	int hei = 0;
	int direction = 1;
	int cellX = 0;
	int cellY = 0;

	Unit *unit;
	for (int i = 0; i < mapObject; i++) {
		reader >> id;
		reader >> posx;
		reader >> posy;
		reader >> wid;
		reader >> hei;
		reader >> direction;
		reader >> cellX;
		reader >> cellY;

		if (id == (int)Tag::GROUND || id == (int)Tag::LADDER || id == (int)Tag::THINSURFACE) {
			Entity *ground = new Entity();
			ground->SetTag((Tag)id);
			ground->SetType(Layer::StaticType);
			ground->SetStatic(true);
			ground->SetPosition(D3DXVECTOR3(posx + wid / 2, posy - hei / 2, 0));
			ground->SetWidth(wid);
			ground->SetHeight(hei);
			ground->SetMoveDirection((Entity::EntityDirection)direction);
			grid->AddStaticObject(ground);
			continue;
		}

		BoxCollider box;
		box.top = posy;
		box.left = posx;
		box.bottom = posy - hei;
		box.right = posx + wid;

		////--DEBUG
		//continue; 


		switch (id) {
		case SPARTA:
		{
			Sparta *sparta = new Sparta();
			sparta->SetSpawnBox(box, direction);
			unit = new Unit(grid, sparta, cellX, cellY);
		}
		break;
		case CAT:
		{
			Cat *cat = new Cat();
			cat->SetSpawnBox(box, direction);
			unit = new Unit(grid, cat, cellX, cellY);
		}
		break;
		case THROWER:
		{
			Thrower *thrower = new Thrower();
			thrower->SetSpawnBox(box, direction);
			unit = new Unit(grid, thrower, cellX, cellY);
		}
		break;
		case EAGLE:
		{
			Eagle *eagle = new Eagle();
			eagle->SetSpawnBox(box, direction);
			unit = new Unit(grid, eagle, cellX, cellY);
		}
		break;
		case SOLDIER:
		{
			Soldier *soldier = new Soldier();
			soldier->SetSpawnBox(box, direction);
			unit = new Unit(grid, soldier, cellX, cellY);
		}
		break;
		case GUNNER:
		{
			Gunner *gunner = new Gunner();
			gunner->SetSpawnBox(box, direction);
			unit = new Unit(grid, gunner, cellX, cellY);
		}
		break;
		case RUNNER:
		{
			Runner *runner = new Runner();
			runner->SetSpawnBox(box, direction);
			unit = new Unit(grid, runner, cellX, cellY);
		}
		break;
		case BASAQUER:
		{
			Basaquer *basaquer = new Basaquer();
			basaquer->SetSpawnBox(box, direction);
			unit = new Unit(grid, basaquer, cellX, cellY);
		}
		break;
		case BAT:
		{
			Bat *bat = new Bat();
			bat->SetSpawnBox(box, direction);
			unit = new Unit(grid, bat, cellX, cellY);
		}
		break;
		default:
		{
			Item *item = new Item(0, (Tag)id);
			item->SetSpawnBox(box);
			unit = new Unit(grid, item, cellX, cellY);
		}
		}
	}
}

int GameMap::GetWidth() {
	return tileset->GetTileWidth() * columns;
}

int GameMap::GetHeight() {
	return tileset->GetTileHeight() * rows;
}

int GameMap::GetTileWidth() {
	return tileset->GetTileWidth();
}

int GameMap::GetTileHeight() {
	return tileset->GetTileHeight();
}

Grid * GameMap::GetGrid() {
	return grid;
}

void GameMap::SetCamera(Camera * cam) {
	camera = cam;
}

void GameMap::Draw() {

	for (size_t i = 0; i < 1; i++) {

		//chieu dai va chieu rong cua tile
		int tileWidth = tileset->GetTileWidth();
		int tileHeight = tileset->GetTileHeight();

		for (int m = 0; m < this->rows; m++) {
			for (int n = 0; n < this->columns; n++) {
				int id = mapIDs[m][n];

				LPSPRITE sprite = tileset->GetSprite(id);

				BoxCollider spriteBound;
				spriteBound.top = (rows - m - 1) * tileHeight;
				spriteBound.bottom = spriteBound.top - tileHeight;
				spriteBound.left = n * tileWidth;
				spriteBound.right = spriteBound.left + tileWidth;

				if (camera->IsCollide(spriteBound)) {
					D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, (rows - m - 1) * tileHeight + tileHeight / 2, 0);
					sprite->SetHeight(tileHeight);
					sprite->SetWidth(tileWidth);
					sprite->Draw(position, BoxCollider(), DataManager::GetGameColor());
				}
			}

		}
	}

}

GameMap::~GameMap() {
	delete grid;
	grid = NULL;
	delete tileset;
	tileset = NULL;
	for (int m = 0; m < this->rows; m++) {
		delete mapIDs[m];
		mapIDs[m] = NULL;
	}
	delete mapIDs;
	mapIDs = NULL;
}

void GameMap::LoadTileset(char * filePath, int tileWidth, int tileHeight) {
	//Parse map tu file 
	Textures::GetInstance()->Add(DataManager::GetCurrentStage(), filePath, D3DCOLOR_XRGB(255, 0, 255));
	auto texture = Textures::GetInstance()->Get(DataManager::GetCurrentStage());
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	auto width = desc.Width;
	auto height = desc.Height;
	tileset = new Tileset(height / tileHeight, width / tileWidth, tileWidth, tileHeight);

	for (int i = 0; i < tileset->GetRows(); i++) {
		for (int j = 0; j < tileset->GetColumns(); j++) {
			BoxCollider r;
			r.top = i * tileHeight;
			r.left = j * tileWidth;
			r.bottom = r.top + tileHeight;
			r.right = r.left + tileWidth;
			LPSPRITE sprite = new Sprite(r, texture);
			tileset->Add(i * tileset->GetColumns() + j, sprite);
		}
	}
}

