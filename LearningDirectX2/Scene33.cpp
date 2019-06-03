#include "Scene33.h"
#include "Debug.h"

Scene33::Scene33() {
	//LoadResources

	//map = new GameMap((char*)"Resources/map31xTileSet.png", (char*)"Resources/map31x.txt", 16, 16);
	map = new GameMap((char*)"Resources/map33TileSet.png", (char*)"Resources/map33.txt", 224, 256);
	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();
	camera = new Camera(width, height);
	map->SetCamera(camera);
	camera->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));

	player = new Player();
	player->SetPosition(32, 40 + player->GetBigHeight() / 2.0f);
	//player->SetPosition(1200, 184 + player->GetBigHeight() / 2.0f);
	camera->FollowPlayer(player->GetPosition().x, player->GetPosition().y);
	(new Unit(map->GetGrid(), player))->SetActive(true);
	CheckCamera();
	ObjectPooling *pool = ObjectPooling::GetInstance();
	pool->AddDarts();
	pool->AddShuriken();
	pool->AddBigShuriken();
	pool->AddFlames();

	timeLeft = 150;
	timeScale = 7;
	gnhpSound::GetInstance()->PlayMusic(2);
}

Scene33::~Scene33() {
	delete map;
	map = NULL;
	delete camera;
	camera = NULL;
}

void Scene33::Render() {
	Graphic *g = Graphic::GetInstance();
	g->SetScoreInfo(DataManager::GetScore());
	g->SetTimeInfo(timeLeft);
	g->SetLifeInfo(DataManager::GetLife());
	g->SetSpiritInfo(DataManager::GetSpiritPoint());
	g->SetstageInfo(1);
	g->SetPlayerHealthInfo(DataManager::GetHealth());
	g->SetEnemyHealthInfo(DataManager::GetBossHealth());
	g->SetItemInfo(DataManager::GetItem());

	map->Draw();

	Graphic::GetInstance()->DrawString();

	map->GetGrid()->Render();
}

void Scene33::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
	player->HandleInput();
}

void Scene33::Update(double dt) {
	if (DataManager::GetBossHealth() == 0)
		EarnReward(dt);
	else
		timeLeft -= dt;
	//DebugOut(L"New Frame\n");
	CheckActive();
	ProcessInput();
	CheckCollision(dt);
	map->GetGrid()->Update(dt);
	D3DXVECTOR3 playerPos = player->GetPosition();
	camera->FollowPlayer(playerPos.x, playerPos.y);
	CheckCamera();
	timeLeft -= dt;
	if (DataManager::IsFreezeTime())
		DataManager::MinusFreezeTimeLeft(dt);
}

int Scene33::GetSceneID() {
	return 2;
}

void Scene33::CheckCollision(double dt) {
	map->GetGrid()->HandleCollision(dt);
}

void Scene33::CheckActive() {
	Entity::EntityDirection camDirection = player->GetVelocity().x > 0 ? Entity::LeftToRight : Entity::RightToLeft;
	map->GetGrid()->HandleActive(camera->GetRect(), camDirection);
}

void Scene33::CheckCamera() {
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

void Scene33::CheckTransitionScene() {
	if (DataManager::IsBossReallyDead() && timeLeft == 0)
		DataManager::SetCurrentStage(3);
}

void Scene33::EarnReward(double dt) {
	earnRewardTime += dt;
	if (timeLeft > 0)
		if (earnRewardTime > 1.0 / timeScale) {
			timeLeft -= 2;
			DataManager::AddData(EarnedData(200));
			if (timeLeft <= 0) {
				timeLeft = 0;
			}
			earnRewardTime = 0;
		}
	CheckTransitionScene();
}

void Scene33::Reset() {
}
