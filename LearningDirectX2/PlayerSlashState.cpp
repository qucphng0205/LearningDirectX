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
	auto player = playerData->player;

	if (m_Animation->IsLastFrame(dt)) {
		if (player->status != Player::OnGround) {
			//jump or falling is not important, on air time is exactly important thing
			player->SetState(Jump);
		}
		else
			if (KeyBoard::GetInstance()->GetKey(DIK_DOWNARROW))
				player->SetState(Crouch);
			else
				player->SetState(Idle);
		return;
	}

	if (player->status != Player::OnGround) {

		player->timeOnAir += dt;
		if (player->timeOnAir > 1)
			player->timeOnAir = 1;

		player->SetVy(MyHelper::Lerp(PLAYER_JUMP_FORCE, -PLAYER_JUMP_FORCE, JUMP_TO_GROUND_SPEED * player->timeOnAir));

		if (player->GetVelocity().y <= 0)
			player->status = Player::Falling;
	}

	PlayerState::Update(dt);
}

void PlayerSlashState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerSlashState::HandleInput() {
	auto keyboard = KeyBoard::GetInstance();
	auto player = playerData->player;
	if (keyboard->GetKeyDown(DIK_F) && player->status == Player::OnGround)
		player->SetState(Jump);
	else
		if (player->GetVelocity().y < 0) {

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
		}
}

void PlayerSlashState::OnCollision(Entity * impactor, Entity::SideCollision side) {

	Player *player = playerData->player;

	auto impactorType = impactor->GetType();

	////--DEBUG
	//if (impactorType == Layer::EnemyType)
	//	impactor = impactor;

	if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType || impactorType == Layer::ItemType) {
		if (m_Animation->GetCurrentFrameID() == 0)
			return;

		if (CollideWithKatana(impactor->GetRect())) {
			if ((impactorType != Layer::ItemType) || (impactorType == Layer::ItemType && !((Item*)impactor)->IsAvailable()))
				DataManager::AddData(impactor->OnDestroy());
		}
		else
			if (CollideWithBody(impactor->GetRect())) {
				if (impactorType == Layer::ItemType) {
					DataManager::AddData(impactor->OnDestroy());
				}
				else {
					//ENEMY OR PROJECTILE
				}
			}
		return;
	}

	if (impactor->GetTag() == GROUND && side == Entity::Bottom && player->status == Player::Falling) {
		player->status = Player::OnGround;
		player->timeOnAir = 0;
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
	if (dummy != 0)
		m_Animation->SetCurrentFrame(dummy);
}

#include "CollisionDetector.h"
bool PlayerSlashState::CollideWithKatana(BoxCollider r) {
	BoxCollider katana = playerData->player->GetRect();
	katana.top -= 3;
	katana.bottom += 18;
	//tinh tu tay
	if (playerData->player->GetMoveDirection() == Entity::LeftToRight)
		katana.left += 14;
	else
		katana.right -= 14;
	if (CollisionDetector::IsCollide(katana, r))
		return true;
	return false;
}

bool PlayerSlashState::CollideWithBody(BoxCollider r) {
	BoxCollider body = playerData->player->GetRect();
	if (playerData->player->GetMoveDirection() == Entity::LeftToRight)
		body.right -= 24;
	else
		body.left += 24;
	if (CollisionDetector::IsCollide(body, r))
		return true;
	return false;
}
