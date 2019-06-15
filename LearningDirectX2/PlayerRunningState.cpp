#include "PlayerRunningState.h"

PlayerRunningState::PlayerRunningState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 5, 5, 3, 9, 4, PLAYER_RUNNING_FRAME * (1.0 / 60));
}

PlayerRunningState::~PlayerRunningState() {
}

void PlayerRunningState::Update(double dt) {
	KeyBoard *keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW))
		playerData->player->SetVelocity(D3DXVECTOR2(-PLAYER_RUN_VELOCITY, 0));
	else
		if (keyboard->GetKey(RIGHT_ARROW) && !keyboard->GetKey(LEFT_ARROW))
			playerData->player->SetVelocity(D3DXVECTOR2(PLAYER_RUN_VELOCITY, 0));
	PlayerState::Update(dt);
}

void PlayerRunningState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerRunningState::HandleInput() {
	//Slash, Left, Right, 
	KeyBoard *keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyDown(SLASH_BUTTON)) {
		playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
		if (keyboard->GetKey(UP_ARROW))
			playerData->player->SetState(UseItem);
		else
			playerData->player->SetState(Slash);
	}
	else
		if (keyboard->GetKeyDown(JUMP_BUTTON)) {
			playerData->player->SetState(Jump);
		}
		else if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW))
			playerData->player->SetVelocity(D3DXVECTOR2(-PLAYER_RUN_VELOCITY, 0));
		else if (keyboard->GetKey(RIGHT_ARROW) && !keyboard->GetKey(LEFT_ARROW))
			playerData->player->SetVelocity(D3DXVECTOR2(PLAYER_RUN_VELOCITY, 0));
		else if (keyboard->GetKey(DOWN_ARROW)) {
			playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
			playerData->player->SetState(Crouch);
		}
		else {
			playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
			playerData->player->SetState(Idle);
		}
}

void PlayerRunningState::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	auto player = playerData->player;
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::ItemAvailableType) {
		DataManager::AddData(impactor->OnDestroy());
		impactor->GetRect();
	}
	else if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType) {
		player->InjuredByOther(impactor);
	}
}

PlayerState::State PlayerRunningState::GetState() {
	return Running;
}

void PlayerRunningState::ResetState(int dummy) {
	auto player = playerData->player;

	//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-7);
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);

	PlayerState::ResetState(dummy);
}

