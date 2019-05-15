#include "PlayScene.h"
#include "Debug.h"

PlayScene::PlayScene() {
	//LoadResources

	//map = new GameMap((char*)"Resources/map31xTileSet.png", (char*)"Resources/map31x.txt", 16, 16);
	map = new GameMap((char*)"Resources/map31TileSet.png", (char*)"Resources/map31.txt", 32, 32);
	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();
	camera = new Camera(width, height);
	map->SetCamera(camera);
	camera->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));

	player = new Player();
	player->SetPosition(32, 40 + player->GetBigHeight() / 2.0f);
	(new Unit(map->GetGrid(), player))->SetActive(true);

	ObjectPooling *pool = ObjectPooling::GetInstance();
	pool->AddKnife();
	pool->AddBullet();

	timeLeft = 150;
}

PlayScene::~PlayScene() {
	delete map;
	map = NULL;
	delete camera;
	camera = NULL;
}

void PlayScene::Render() {
	Graphic *g = Graphic::GetInstance();
	g->SetScoreInfo(DataManager::GetScore());
	g->SetTimeInfo(timeLeft);
	g->SetLifeInfo(DataManager::GetLife());
	g->SetSpiritInfo(DataManager::GetSpiritPoint());
	g->SetstageInfo(0);
	g->SetPlayerHealthInfo(DataManager::GetHealth());
	g->SetEnemyHealthInfo(16);
	g->SetItemInfo(DataManager::GetItem());

	map->Draw();

	Graphic::GetInstance()->DrawString();

	map->GetGrid()->Render();
}

void PlayScene::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
	player->HandleInput();
}

void PlayScene::Update(double dt) {
	//DebugOut(L"New Frame\n");
	CheckActive();
	ProcessInput();
	CheckCollision(dt);
	map->GetGrid()->Update(dt);
	D3DXVECTOR3 playerPos = player->GetPosition();
	camera->FollowPlayer(playerPos.x, playerPos.y);
	CheckCamera();
	timeLeft -= dt;
}

void PlayScene::CheckCollision(double dt) {
	map->GetGrid()->HandleCollision(dt);
}

void PlayScene::CheckActive() {
	Entity::EntityDirection camDirection = player->GetVelocity().x > 0 ? Entity::LeftToRight : Entity::RightToLeft;
	map->GetGrid()->HandleActive(camera->GetRect(), camDirection);
}

void PlayScene::CheckCamera() {
	D3DXVECTOR3 camPos = camera->GetPosition();
	float halfWidth = (float)camera->GetWidth() / 2;
	float halfHeight = (float)camera->GetHeight() / 2;
	auto worldWidth = map->GetWidth();
	auto worldHeight = map->GetHeight();
	if (camPos.x - halfWidth < 0)
		camPos.x = halfWidth;
	if (camPos.x + halfWidth > worldWidth)
		camPos.x = worldWidth - halfWidth;
	camera->SetPosition(camPos);
}

void PlayScene::Reset() {
}
