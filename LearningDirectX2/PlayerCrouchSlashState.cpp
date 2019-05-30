#include "PlayerCrouchSlashState.h"

PlayerCrouchSlashState::PlayerCrouchSlashState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 7, 7, 3, 9, 4, 0.1f);
}

PlayerCrouchSlashState::~PlayerCrouchSlashState() {
}

void PlayerCrouchSlashState::Update(double dt) {
	if (m_Animation->IsLastFrame(dt)) {
		if (KeyBoard::GetInstance()->GetKey(DIK_DOWNARROW))
			playerData->player->SetState(Crouch);
		else
			playerData->player->SetState(Idle);
		return;
	}

	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	m_Animation->Update(dt);
}

void PlayerCrouchSlashState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerCrouchSlashState::HandleInput() {
	auto keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKeyDown(DIK_F))
		playerData->player->SetState(Jump);
	else
		playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
}

void PlayerCrouchSlashState::OnCollision(Entity * impactor, Entity::SideCollision side) {
	Player *player = playerData->player;

	auto impactorType = impactor->GetType();

	////--DEBUG
	//if (impactorType == Layer::EnemyType)
	//	impactor = impactor;

	if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType || impactorType == Layer::ItemAvailableType || impactorType == Layer::ItemHolderType) {

		bool isSlash = (m_Animation->GetCurrentFrameID() != 0);

		if (CollideWithKatana(impactor->GetRect()) && isSlash) {
			if (impactorType != Layer::ItemAvailableType)
				DataManager::AddData(impactor->OnDestroy());
		}
		else
			if (CollideWithBody(impactor->GetRect())) {
				if (impactorType == Layer::ItemAvailableType) {
					DataManager::AddData(impactor->OnDestroy());
				}
				else {
					player->InjuredByOther(impactor);
				}
			}
		return;
	}
	//else if (impactor->GetTag() == GROUND && side == Entity::Bottom && player->status == Player::Falling) {
	//	player->status = Player::OnGround;
	//	player->timeOnAir = 0;
	//	auto keyboard = KeyBoard::GetInstance();
	//	if (keyboard->GetKey(DIK_LEFTARROW) && !(keyboard->GetKey(DIK_RIGHTARROW)))
	//		player->SetState(Running);
	//	else
	//		if (keyboard->GetKey(DIK_RIGHTARROW) && !(keyboard->GetKey(DIK_LEFTARROW)))
	//			player->SetState(Running);
	//		else
	//			if (keyboard->GetKey(DIK_DOWNARROW))
	//				player->SetState(Crouch);
	//			else
	//				player->SetState(Idle);
	//}
}

PlayerState::State PlayerCrouchSlashState::GetState() {
	return CrouchSlash;
}

void PlayerCrouchSlashState::ResetState(int dummy) {
	auto player = playerData->player;

	//collider slash + crouch 
	player->SetColliderTop(8);
	player->SetColliderBottom(-16);

	player->SetColliderLeft(-7);
	player->SetColliderRight(31);

	PlayerState::ResetState(dummy);
}

BoxCollider PlayerCrouchSlashState::GetBody() {
	BoxCollider body = playerData->player->GetRect();
	if (playerData->player->GetMoveDirection() == Entity::LeftToRight)
		body.right -= 24;
	else
		body.left += 24;
	return body;
}

#include "CollisionDetector.h"
bool PlayerCrouchSlashState::CollideWithKatana(BoxCollider r) {
	BoxCollider katana = playerData->player->GetRect();
	katana.top -= 3;
	katana.bottom += 12;
	//tinh tu tay
	if (playerData->player->GetMoveDirection() == Entity::LeftToRight)
		katana.left += 14;
	else
		katana.right -= 14;
	if (CollisionDetector::IsCollide(katana, r))
		return true;
	return false;
}

bool PlayerCrouchSlashState::CollideWithBody(BoxCollider r) {
	BoxCollider body = GetBody();
	if (CollisionDetector::IsCollide(body, r))
		return true;
	return false;
}