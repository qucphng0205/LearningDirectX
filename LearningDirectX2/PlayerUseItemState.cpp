#include "PlayerUseItemState.h"

PlayerUseItemState::PlayerUseItemState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 3, 3, 3, 9, 4, 0.1f);
}

PlayerUseItemState::~PlayerUseItemState() {
}

void PlayerUseItemState::Update(double dt) {
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

void PlayerUseItemState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerUseItemState::HandleInput() {
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

void PlayerUseItemState::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::ItemAvailableType)
		DataManager::AddData(impactor->OnDestroy());

	Player *player = playerData->player;

	////--DEBUG
	//if (impactorType == Layer::EnemyType)
	//	impactor = impactor;

	if (impactor->GetType() == StaticType && side == Entity::Bottom && player->status == Player::Falling) {
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
	else if (impactorType == Layer::EnemyType || impactorType == Layer::EProjectileType) {
		player->InjuredByOther(impactor);
	}
}

PlayerState::State PlayerUseItemState::GetState() {
	return UseItem;
}

void PlayerUseItemState::ResetState(int dummy) {
	auto player = playerData->player;

	//collider usually smaller than sprite
	player->SetColliderLeft(-7);
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);

	PlayerState::ResetState(dummy);
	if (dummy != 0)
		m_Animation->SetCurrentFrame(dummy);
}
