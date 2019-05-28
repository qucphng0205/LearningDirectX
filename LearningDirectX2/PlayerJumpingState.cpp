#include "PlayerJumpingState.h"

PlayerJumpingState::PlayerJumpingState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 8, 8, 4, 9, 4, PLAYER_JUMPING_FRAME * (1.0f / 60));
}

PlayerJumpingState::~PlayerJumpingState() {
}
#include "Debug.h"
void PlayerJumpingState::Update(double dt) {
	auto player = playerData->player;

	float t = JUMP_TO_GROUND_SPEED * player->timeOnAir;
	if (t > 1)
		t = 1;
	//linear interpolation
	player->SetVy(MyHelper::Lerp(PLAYER_JUMP_FORCE, -PLAYER_JUMP_FORCE, t));

	if (player->GetVelocity().y <= 0) {
		//DebugOut(L"timeOnAir = %f\n", player->timeOnAir);
		player->status = Player::Falling;
	}
	PlayerState::Update(dt);
	player->timeOnAir += dt;
}

void PlayerJumpingState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerJumpingState::HandleInput() {
	auto player = playerData->player;
	auto keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKeyDown(DIK_D)) {
		if (keyboard->GetKey(DIK_UPARROW))
			player->SetState(UseItem, 1);
		else
			player->SetState(Slash, 1);
		return;
	}
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

void PlayerJumpingState::OnCollision(Entity * impactor, Entity::SideCollision side) {

	auto player = playerData->player;
	auto impactorType = impactor->GetType();
	auto impactorRect = impactor->GetRect();

	if (impactorType == Layer::ItemAvailableType) {
		DataManager::AddData(impactor->OnDestroy());
	}
	else if (impactor->GetTag() == GROUND && side == Entity::Bottom && (abs(player->GetPosition().y - player->GetBigHeight() / 2.0 - impactorRect.top) <= PLAYER_OFFSET_GROUND)) {
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
	else if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType) {
		player->InjuredByOther(impactor);
	}
}

PlayerState::State PlayerJumpingState::GetState() {
	return (playerData->player->GetVelocity().y > 0) ? Jump : Falling;
}

void PlayerJumpingState::ResetState(int dummy) {
	//1. falling from ground
	//2. falling from slash

	auto player = playerData->player;

	//jump collider around center point
	player->SetColliderLeft(-7);
	player->SetColliderTop(16);
	player->SetColliderBottom(-3);

	if (player->timeOnAir == 0) {
		//dummy = 0  means jumping
		if (dummy == 0) {
			playerData->player->SetVy(PLAYER_JUMP_FORCE);
			player->status = Player::Jumping;
			player->timeOnAir = 0;
		}
		else {
			player->timeOnAir = 0.4f;
			player->status = Player::Falling;
		}
	}
	//else means from slash to jump with on air time = 0

	PlayerState::ResetState(dummy);
}
