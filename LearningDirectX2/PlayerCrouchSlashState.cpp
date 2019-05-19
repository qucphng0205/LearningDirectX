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
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::ItemType)
		if (((Item*)impactor)->IsAvailable())
			DataManager::AddData(impactor->OnDestroy());
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
