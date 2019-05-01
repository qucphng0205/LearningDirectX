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
	ProcessInput();
	CheckCollision(dt);
	map->UpdateActive(dt);
	player->Update(dt);
	CheckActive();
	D3DXVECTOR3 playerPos = player->GetPosition();
	camera->FollowPlayer(playerPos.x, playerPos.y);
	CheckCamera();
}

void PlayScene::CheckCollision(double dt) {

	CamBox *camBox = new CamBox(camera->GetRect(), player->GetVelocity());
	vector<Entity*> staticObjects;
	vector<Entity*> actives;

	map->GetGrid()->GetEntityWithRect(staticObjects, camera->GetRect());
	map->GetActiveObject(actives);

	auto side = Entity::NotKnow;

	//actives with ground
	for (size_t i = 0; i < actives.size(); i++) {
		bool onGround = false;
		for (size_t j = 0; j < staticObjects.size(); j++) {

			float collisionTime = CollisionDetector::SweptAABB(actives[i], staticObjects[j], side, dt);

			if (collisionTime == 2)
				continue;

			actives[i]->OnCollision(staticObjects[j], side, collisionTime);
			if (side == Entity::Bottom)
				onGround = true;
		}
		//if (!onGround && actives[i]->GetVy() >= 0)
		if (!onGround)
			actives[i]->AddVy(-CAT_GRAVITY);
	}

	BoxCollider exPlayer = BoxCollider(player->GetPosition(), player->GetWidth(), player->GetBigHeight());
	bool isOnGround = false;

	//player with ground
	for (size_t i = 0; i < staticObjects.size(); i++) {

		auto impactorRect = staticObjects[i]->GetRect();

		float groundTime = CollisionDetector::SweptAABB(exPlayer, player->GetVelocity(), impactorRect, D3DXVECTOR2(0, 0), side, dt);

		if (groundTime != 2)
			if (side == Entity::Bottom && abs(exPlayer.bottom - impactorRect.top) <= PLAYER_OFFSET_GROUND) {

				if (player->GetVelocity().y > 0)
					continue;

				if (player->GetVelocity().y < 0)
					player->OnCollision(staticObjects[i], side, groundTime);

				isOnGround = true;
			}
	}

	//player with actives but later 
	//for (int i = 0; i < actives.size(); i++) {

	//	float collisionTime = CollisionDetector::SweptAABB(player, actives[i], side, dt);

	//	if (collisionTime == 2)
	//		continue;

	//	player->OnCollision(actives[i], side, collisionTime);
	//	collisionTime = CollisionDetector::SweptAABB(actives[i], player, side, dt);
	//	actives[i]->OnCollision(player, side, collisionTime);
	//}

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
