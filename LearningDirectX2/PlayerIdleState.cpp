#include "PlayerIdleState.h"

PlayerIdleState::PlayerIdleState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 1, 1, 1, 9, 4);
}

PlayerIdleState::~PlayerIdleState() {
}

void PlayerIdleState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerIdleState::Update(double dt) {
	playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
	PlayerState::Update(dt);
}

void PlayerIdleState::HandleInput() {
	//xu ly theo priority 
	KeyBoard *keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKeyDown(SLASH_BUTTON)) {
		if (keyboard->GetKey(UP_ARROW))
			playerData->player->SetState(UseItem);
		else
			playerData->player->SetState(Slash);
	}
	else
		if (keyboard->GetKeyDown(JUMP_BUTTON))
			playerData->player->SetState(Jump);
		else
			if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW)) {
				playerData->player->SetState(Running, 0);
			}
			else
				if (keyboard->GetKey(RIGHT_ARROW) && !keyboard->GetKey(LEFT_ARROW)) {
					playerData->player->SetState(Running, 0);
				}
				else
					if (keyboard->GetKey(DOWN_ARROW))
						playerData->player->SetState(Crouch);
					else
						playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
}

void PlayerIdleState::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::ItemAvailableType)
		DataManager::AddData(impactor->OnDestroy());
	else if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType) {
		playerData->player->InjuredByOther(impactor);
	}
}

PlayerState::State PlayerIdleState::GetState() {
	return Idle;
}

void PlayerIdleState::ResetState(int dummy) {
	auto player = playerData->player;

	//around center point
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);
	player->SetColliderLeft(-7);

	PlayerState::ResetState(dummy);
}
