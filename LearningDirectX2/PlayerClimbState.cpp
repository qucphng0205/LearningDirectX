#include "PlayerClimbState.h"

PlayerClimbState::PlayerClimbState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 4, 4, 2, 9, 4, 0.1f);

}

PlayerClimbState::~PlayerClimbState() {
}

void PlayerClimbState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerClimbState::Update(double dt) {
	if (isClimbing)
		PlayerState::Update(dt);
}

void PlayerClimbState::HandleInput() {
	auto player = playerData->player;
	auto input = KeyBoard::GetInstance();
	auto bottom = player->GetRect().bottom;
	Entity::EntityDirection dir = player->GetMoveDirection();

	bool left = (dir == Entity::LeftToRight && input->GetKey(DIK_LEFTARROW));
	bool right = (dir == Entity::RightToLeft && input->GetKey(DIK_RIGHTARROW));

	if (input->GetKey(DIK_UP) && isLadder) {
		if (bottom < topPoint) {
			player->SetVy(PLAYER_CLIM_SPEED);
		}
		else
			player->SetVy(0);
		isClimbing = true;
	}
	else if (input->GetKey(DIK_DOWN) && isLadder) {
		player->SetVy(-PLAYER_CLIM_SPEED);
		isClimbing = true;
	}
	else if (input->GetKeyDown(DIK_F)) {
		if (left) {
			player->SetMoveDirection(Entity::RightToLeft);
			player->SetState(Jump);
		}
		else if (right) {
			player->SetMoveDirection(Entity::LeftToRight);
			player->SetState(Jump);
		}
		else {
			playerData->player->SetVy(0);
			isClimbing = false;
		}

	}
	else {
		playerData->player->SetVy(0);
		isClimbing = false;
	}
}

void PlayerClimbState::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::ItemAvailableType)
		DataManager::AddData(impactor->OnDestroy());
	if (playerData->player->GetVy() < 0 && impactor->GetTag() == GROUND && side == Entity::Bottom) {
		playerData->player->timeOnAir = 0;
		playerData->player->SetState(Crouch); 
	}
}

PlayerState::State PlayerClimbState::GetState() {
	return Climb;
}

void PlayerClimbState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetVy(0);
	//Climb collider: DEMO JUST DEMO BRO?
	player->SetColliderTop(13);
	player->SetColliderBottom(-16);
	player->SetColliderLeft(-7);

	if (dummy < 0) {
		topPoint = -dummy;
		isLadder = false;
	}
	else {
		isLadder = true;
		topPoint = dummy - LADDER_OFFSET;
	}
	isClimbing = false;
	player->status = Player::Status::Climbing;
	player->timeOnAir = 0.15f;
	PlayerState::ResetState(dummy);
}
