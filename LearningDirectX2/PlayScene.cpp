#include "PlayScene.h"
#include "Debug.h"

PlayScene::PlayScene() {
	//LoadResources
	map = new GameMap((char*)"Resources/map31TileSet.png", (char*)"Resources/map31.txt", 32, 32);
	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();
	camera = new Camera(width, height);
	map->SetCamera(camera);
	camera->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));

	player = new Player();
	player->SetPosition(32, 40 + player->GetBigHeight() / 2.0f);
}

PlayScene::~PlayScene() {

}

void PlayScene::Render() {
	map->Draw();
	map->RenderActive();
	player->Render();
}

void PlayScene::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
	player->HandleInput();
}

void PlayScene::Update(double dt) {
	CheckCollision(dt);
	map->UpdateActive(dt);
	player->Update(dt);
	CheckActive();
	D3DXVECTOR3 playerPos = player->GetPosition();
	camera->FollowPlayer(playerPos.x, playerPos.y);
	CheckCamera();
	ProcessInput();
}

void PlayScene::CheckCollision(double dt) {

	CamBox *camBox = new CamBox(camera->GetRect(), player->GetVelocity());
	vector<Entity*> collideObjects;

	map->GetGrid()->GetEntityWithRect(collideObjects, camera->GetRect());
	map->GetActiveObject(collideObjects);

	auto side = Entity::NotKnow;

	for (size_t i = 0; i < collideObjects.size() - 1; i++) {
		for (size_t j = i + 1; j < collideObjects.size(); j++) {

			//--DEBUG--
			if (collideObjects[i]->GetTag() == Entity::CamRect && collideObjects[j]->GetTag() == Entity::Sparta)
				i = i;

			float collisionTime = CollisionDetector::SweptAABB(collideObjects[j], collideObjects[i], side, dt);

			if (collisionTime == 2)
				continue;

			collideObjects[j]->OnCollision(collideObjects[i], side, collisionTime);
			collisionTime = CollisionDetector::SweptAABB(collideObjects[i], collideObjects[j], side, dt);

			collideObjects[i]->OnCollision(collideObjects[j], side, collisionTime);

		}
	};

	BoxCollider exPlayer = BoxCollider(player->GetPosition(), 16, player->GetBigHeight());
	bool isOnGround = false;

	for (size_t i = 0; i < collideObjects.size(); i++) {

		if (collideObjects[i]->GetTag() == Entity::Sparta)
			i = i;

		if (collideObjects[i]->isStatic) {
			float groundTime = CollisionDetector::SweptAABB(exPlayer, player->GetVelocity(), collideObjects[i]->GetRect(), D3DXVECTOR2(0, 0), side, dt);
			if (Entity::Bottom) {
				if (groundTime == 0) {
					isOnGround = true;
					continue;
				}
				else
					if (groundTime != 2) {
						player->OnCollision(collideObjects[i], side, groundTime);
						isOnGround = true;
						continue;
					}
			}
		}

		float collisionTime = CollisionDetector::SweptAABB(player, collideObjects[i], side, dt);
		if (collisionTime == 2)
			continue;
		player->OnCollision(collideObjects[i], side, collisionTime);
		collisionTime = CollisionDetector::SweptAABB(collideObjects[i], player, side, dt);
		collideObjects[i]->OnCollision(player, side, collisionTime);
	}

	PlayerState::State state = player->GetState();
	if (!isOnGround && !player->onAir) {
		player->OnFalling();
	}
}

void PlayScene::CheckActive() {
	map->CheckActive(player->GetVelocity());
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
