#include "PlayerRunningState.h"

PlayerRunningState::PlayerRunningState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 5, 5, 3, 9, 4, 0.01f);
}

PlayerRunningState::~PlayerRunningState() {
}

void PlayerRunningState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerRunningState::HandleInput() {
	//Slash, Left, Right, 
	KeyBoard *keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKeyDown(DIK_D)) {
		playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
		playerData->player->SetState(Slash);
	}
	else
		if (keyboard->GetKeyDown(DIK_F)) {
			playerData->player->SetState(Jump);
		}
		else
			if (keyboard->GetKey(DIK_LEFTARROW) && !keyboard->GetKey(DIK_RIGHTARROW))
				playerData->player->SetVelocity(D3DXVECTOR2(-PLAYER_RUN_VELOCITY, 0));
			else
				if (keyboard->GetKey(DIK_RIGHTARROW) && !keyboard->GetKey(DIK_LEFTARROW))
					playerData->player->SetVelocity(D3DXVECTOR2(PLAYER_RUN_VELOCITY, 0));
				else
					if (keyboard->GetKey(DIK_DOWNARROW)) {
						playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
						playerData->player->SetState(Crouch);
					}
					else {
						playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
						playerData->player->SetState(Idle);
					}
}

void PlayerRunningState::OnCollision(Entity * impactor, Entity::SideCollision side) {
}

PlayerState::State PlayerRunningState::GetState() {
	return Running;
}

void PlayerRunningState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetColliderLeft(-11);
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);
	auto keyboard = KeyBoard::GetInstance();
	//if (keyboard->GetKey(DIK_LEFTARROW) && !keyboard->GetKey(DIK_RIGHTARROW))
	//	playerData->player->SetVelocity(D3DXVECTOR2(-PLAYER_RUN_VELOCITY, 0));
	//else
	//	if (keyboard->GetKey(DIK_RIGHTARROW) && !keyboard->GetKey(DIK_LEFTARROW))
	//		playerData->player->SetVelocity(D3DXVECTOR2(PLAYER_RUN_VELOCITY, 0));

	PlayerState::ResetState(dummy);
}

