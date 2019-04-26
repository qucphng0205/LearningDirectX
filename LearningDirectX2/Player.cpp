#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerIdleState.h"
#include "PlayerSlashState.h"
#include "PlayerCrouchState.h"
#include "PlayerCrouchSlashState.h"
#include "PlayerJumpingState.h"
#include "PlayerClimbState.h"
#include "PlayerUseItemState.h"
#include "Debug.h"

Player::Player() {
	Textures::GetInstance()->Add(TEX_PLAYER, "Resources/Sprites/ryuspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	playerData = new PlayerData();
	playerData->player = this;

	idleState = new PlayerIdleState(playerData);
	runningState = new PlayerRunningState(playerData);
	slashState = new PlayerSlashState(playerData);
	crouchState = new PlayerCrouchState(playerData);
	crouchSlashState = new PlayerCrouchSlashState(playerData);
	jumpState = new PlayerJumpingState(playerData);
	climbState = new PlayerClimbState(playerData);
	useItemState = new PlayerUseItemState(playerData);

	SetState(PlayerState::Idle);
	SetTag(Entity::EntityTag::Player);
	SetType(Entity::EntityType::PlayerType);

	D3DSURFACE_DESC desc;
	Textures::GetInstance()->Get(TEX_PLAYER)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height / 9;

	isActive = true;
}

Player::~Player() {
}

void Player::Update(double dt) {
	if (playerData->state)
		playerData->state->Update(dt);
	//if (playerData->state->GetState() == PlayerState::Idle)
	//	DebugOut(L"State idle-ing\n");
	//DebugOut(L"Velocity: %f, Position.y: %f and %f\n", velocity.y, GetBigBound().bottom, GetBigBound().bottom + velocity.y * dt);
	Entity::Update(dt);
	if ((side == Left && velocity.x < 0) || (side == Right && velocity.x > 0))
		velocity.x = 0;
	if ((side == Bottom && velocity.y < 0))
		velocity.y = 0;
	side = NotKnow;
}

void Player::Render() {
	playerData->state->Render();
}

void Player::SetState(PlayerState::State name, int dummy) {
	bool falling = false;

	switch (name) {
	case PlayerState::Running:
		playerData->state = runningState;
		break;
	case PlayerState::Idle:
		playerData->state = idleState;
		break;
	case PlayerState::Slash:
		playerData->state = slashState;
		break;
	case PlayerState::Crouch:
		playerData->state = crouchState;
		break;
	case PlayerState::CrouchSlash:
		playerData->state = crouchSlashState;
		break;
	case PlayerState::Climb:
		playerData->state = climbState;
		break;
	case PlayerState::UseItem:
		playerData->state = useItemState;
		break;
	case PlayerState::Jump:
		playerData->state = jumpState;
		break;
	case PlayerState::Falling:
		playerData->state = jumpState;
		falling = true;
		break;
	}
	playerData->state->ResetState(dummy);
	if (falling)
		SetVy(0);
}

void Player::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	if (impactor->GetTag() == CamRect)
		return;
	playerData->state->OnCollision(impactor, side);
	if (side == Bottom && velocity.y < 0) {
		velocity.y *= collisionTime;
		DebugOut(L"Set lai velocity.y: %f", collisionTime);
	}
	else if ((side == Right && velocity.x > 0) || (side == Left && velocity.x < 0))
		velocity.x *= collisionTime;
	this->collisionTime = collisionTime;
	this->side = side;
}

BoxCollider Player::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	r.bottom = position.y + collider.bottom;
	return r;
}

BoxCollider Player::GetBigBound() {
	BoxCollider r;
	r.top = position.y + height / 2;
	r.left = position.x - width / 2;
	r.bottom = position.y - height / 2;
	r.right = position.x + width / 2;
	return r;
}

PlayerState::State Player::GetState() {
	return playerData->state->GetState();
}

int Player::GetBigWidth() {
	return Entity::GetWidth();
}

int Player::GetBigHeight() {
	return Entity::GetHeight();
}

float Player::GetWidth() {
	return collider.right - collider.left;
}

float Player::GetHeight() {
	return collider.top - collider.bottom;
}

void Player::OnFalling() {
	SetState(PlayerState::Falling);
}

void Player::SetColliderTop(int top) {
	collider.top = top;
}

void Player::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -left;
}

void Player::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Player::SetColliderRight(int right) {
	collider.right = right;
}

BoxCollider Player::GetCollider() {
	return collider;
}

void Player::HandleInput() {
	if (this->playerData->state)
		playerData->state->HandleInput();
}

