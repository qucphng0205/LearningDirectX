#include "PlayerInjuredState.h"

PlayerInjuredState::PlayerInjuredState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 8, 8, 1, 9, 4, 0.1f);
}

PlayerInjuredState::~PlayerInjuredState() {
}

void PlayerInjuredState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerInjuredState::Update(double dt) {
	auto player = playerData->player;

	float t = PLAYER_INJURED_SPEED * player->timeOnAir;
	if (t > 1)
		t = 1;
	float sign = player->GetMoveDirection() == Entity::LeftToRight ? -1 : 1;

	//linear interpolation
	player->SetVy(MyHelper::Lerp(PLAYER_INJURED_FORCE_Y, -PLAYER_INJURED_FORCE_Y * 2.5f, t));
	//player->SetVx(MyHelper::Lerp(sign * PLAYER_INJURED_FORCE_X, 0, t));

	player->SetMoveDirection(sign == -1 ? Entity::LeftToRight : Entity::RightToLeft);

	if (player->GetVelocity().y <= 0) {
		//DebugOut(L"timeOnAir = %f\n", player->timeOnAir);
		player->status = Player::Falling;
	}
	PlayerState::Update(dt);
	player->timeOnAir += dt;
}


void PlayerInjuredState::HandleInput() {

}

void PlayerInjuredState::OnCollision(Entity * impactor, Entity::SideCollision side) {
	auto impactorType = impactor->GetType();
	auto player = playerData->player;

	if (impactorType == Layer::ItemAvailableType) 
		DataManager::AddData(impactor->OnDestroy());
	else if (impactor->GetTag() == GROUND && side == Entity::Bottom) {
		if (player->status == Player::Jumping)
			return;
		auto keyboard = KeyBoard::GetInstance();

		player->status = Player::OnGround;
		player->timeOnAir = 0;

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

PlayerState::State PlayerInjuredState::GetState() {
	return Injured;
}

void PlayerInjuredState::ResetState(int dummy) {

	//before reset state to injured please set the direction for the player
	auto player = playerData->player;

	//jump collider around center point
	player->SetColliderTop(16);
	player->SetColliderBottom(-3);
	player->SetColliderLeft(-7);
	player->OnImmortal();

	float sign = player->GetMoveDirection() == Entity::LeftToRight ? -1 : 1;

	//if (player->timeOnAir == 0) {
		//dummy = 0  means damage from enemy
		if (dummy == 0) {
			playerData->player->SetVelocity(D3DXVECTOR2(sign * PLAYER_INJURED_FORCE_X, PLAYER_JUMP_FORCE));
			player->SetMoveDirection(sign == -1 ? Entity::LeftToRight : Entity::RightToLeft);
			player->status = Player::Jumping;
			player->timeOnAir = 0;
		}
		else {
			player->timeOnAir = 0.4f;
			player->status = Player::Jumping;
		}
	//}

	PlayerState::ResetState(dummy);
}
