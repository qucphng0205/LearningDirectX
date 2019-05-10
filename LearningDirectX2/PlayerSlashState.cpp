#include "PlayerSlashState.h"

PlayerSlashState::PlayerSlashState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 2, 2, 3, 9, 4, 0.08f);
}

PlayerSlashState::~PlayerSlashState() {
}

void PlayerSlashState::Update(double dt) {
	if (m_Animation->IsLastFrame(dt)) {
		if (playerData->player->onAir)
			playerData->player->SetState(Falling);
		else
			if (KeyBoard::GetInstance()->GetKey(DIK_DOWNARROW))
				playerData->player->SetState(Crouch);
			else
				playerData->player->SetState(Idle);
		return;
	}
	m_Animation->Update(dt);
}

void PlayerSlashState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerSlashState::HandleInput() {
	auto keyboard = KeyBoard::GetInstance();
	auto player = playerData->player;
	if (keyboard->GetKeyDown(DIK_F) && !player->onAir)
		player->SetState(Jump);
	else
		if (player->onAir) {

			if (keyboard->GetKey(DIK_LEFTARROW) && !keyboard->GetKey(DIK_RIGHTARROW)) {
				if (player->GetMoveDirection() == Player::RightToLeft)
					player->SetVx(-PLAYER_RUN_VELOCITY);
				else {
					player->SetVx(-PLAYER_RUN_VELOCITY / 3.0f);
					player->SetMoveDirection(Player::LeftToRight);
				}
			}
			else
				if (keyboard->GetKey(DIK_RIGHTARROW) && !keyboard->GetKey(DIK_LEFTARROW)) {
					if (player->GetMoveDirection() == Player::LeftToRight)
						player->SetVx(PLAYER_RUN_VELOCITY);
					else {
						player->SetVx(PLAYER_RUN_VELOCITY / 3.0f);
						player->SetMoveDirection(Player::RightToLeft);
					}
				}
				else player->SetVx(0);

			float vy = player->GetVelocity().y;
			player->AddVy(-GRAVITY);
			if (player->GetVelocity().y <= PLAYER_MAX_FALLING_VELOCITY) {
				player->SetVy(PLAYER_MAX_FALLING_VELOCITY);
			}
		}
}

void PlayerSlashState::OnCollision(Entity * impactor, Entity::SideCollision side) {

	Player *player = playerData->player;

	auto impactorType = impactor->GetType();

	////--DEBUG
	//if (impactorType == Entity::EnemyType)
	//	impactor = impactor;
	
	if (impactorType == Entity::EnemyType || impactorType == Entity::ProjectileType || impactorType == Entity::ItemType) {
		if (m_Animation->GetCurrentFrameID() == 0)
			return;
		////--DEBUG
		//if (impactor->GetType() == Entity::ProjectileType)
		//	impactor = impactor;
		//auto slashDir = player->GetMoveDirection();
		//auto posX = player->GetPosition().x;
		//auto impactorX = impactor->GetPosition().x;

		if (CollideWithKatana(impactor->GetRect())) {
			impactor->OnDestroy();
		}
		return;
	}

	if (impactor->GetTag() == Entity::Ground && side == Entity::Bottom && player->onAir) {
		auto keyboard = KeyBoard::GetInstance();
		if (keyboard->GetKey(DIK_LEFTARROW) && !(keyboard->GetKey(DIK_RIGHTARROW)))
			player->SetState(Running);
		else
			if (keyboard->GetKey(DIK_RIGHTARROW) && !(keyboard->GetKey(DIK_LEFTARROW)))
				player->SetState(Running);
			else
				if (keyboard->GetKey(DIK_DOWNARROW))
					player->SetState(Crouch);
				else
					player->SetState(Idle);
		player->onAir = false;
	}
}

PlayerState::State PlayerSlashState::GetState() {
	return Slash;
}

void PlayerSlashState::ResetState(int dummy) {
	auto player = playerData->player;

	//right + left collider is slash range 
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);
	player->SetColliderLeft(-7);
	player->SetColliderRight(31);


	PlayerState::ResetState(dummy);
	if (dummy != -1)
		m_Animation->SetCurrentFrame(dummy);
}

#include "CollisionDetector.h"
bool PlayerSlashState::CollideWithKatana(BoxCollider r) {
	BoxCollider katana = playerData->player->GetRect();
	katana.top -= 3;
	katana.bottom += 18;
	if (playerData->player->GetMoveDirection() == Entity::LeftToRight)
		katana.left += 14;
	else
		katana.right -= 14;
	if (CollisionDetector::IsCollide(katana, r))
		return true;
	return false;
}
