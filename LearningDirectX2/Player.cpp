#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerIdleState.h"
#include "PlayerSlashState.h"
#include "PlayerCrouchState.h"
#include "PlayerCrouchSlashState.h"
#include "PlayerJumpingState.h"
#include "PlayerClimbState.h"
#include "PlayerUseItemState.h"
#include "PlayerInjuredState.h"
#include "Debug.h"

Player* Player::instance = NULL;

Player * Player::GetInstance() {
	return instance;
}

Player::Player() : Entity() {

	instance = this;

	Textures *textures = Textures::GetInstance();
	textures->Add(TEX_PLAYER, "Resources/Sprites/ryuspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

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
	injuredState = new PlayerInjuredState(playerData);

	SetState(PlayerState::Idle);
	SetTag(PLAYER);
	SetType(Layer::PlayerType);

	status = OnGround;

	D3DSURFACE_DESC desc;
	textures->Get(TEX_PLAYER)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height / 9;

	isActive = true;
}

Player::~Player() {
	delete idleState;
	idleState = NULL;
	delete runningState;
	runningState = NULL;
	delete slashState;
	slashState = NULL;
	delete crouchState;
	crouchState = NULL;
	delete crouchSlashState;
	crouchSlashState = NULL;
	delete jumpState;
	jumpState = NULL;
	delete climbState;
	climbState = NULL;
	delete useItemState;
	useItemState = NULL;
	delete playerData;
	playerData = NULL;
}

void Player::Update(double dt) {

	if (isImmortal && currentState != PlayerState::Injured) {
		immortalTime += dt;
		if (immortalTime > PLAYER_IMMORTAL_TIME) {
			immortalTime = 0;
			OffImmortal();
		}
	}

	if ((position.x + collider.left) + velocity.x * dt >= 16)
		Entity::Update(dt);

	if (playerData->state)
		playerData->state->Update(dt);

	//BoxCollider exPlayer = BoxCollider(GetPosition(), GetWidth(), GetBigHeight());

	////--DEBUG--
	//if (vely != velocity)
	//	vely = vely;
	////--DEBUG--
	//if (exPlayer.bottom < 39) {
	//	vely = vely;
	//}
	////-Debug
	//auto xside = NotKnow;
	//auto impactorRect = BoxCollider(40, 0, 0, 544);
	//float groundTime = CollisionDetector::SweptAABB(exPlayer, GetVelocity(), impactorRect, D3DXVECTOR2(0, 0), xside, dt);

	//if ((side == Left && velocity.x < 0) || (side == Right && velocity.x > 0))
	//	velocity.x = 0;
	//if ((side == Bottom && velocity.y < 0))
	//	velocity.y = 0;

	if (checkGroundInFrame == false && status == OnGround)
		OnFalling();

	checkGroundInFrame = false;
}

void Player::Render() {
	if (!isImmortal || (isImmortal && !renderPreviousFrame) || currentState == PlayerState::Injured) {
		playerData->state->Render();
		renderPreviousFrame = true;
	}
	else
		renderPreviousFrame = false;
}

void Player::SetState(PlayerState::State name, int dummy) {
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
		CheckForUseItem();
		break;
	case PlayerState::Jump:
		playerData->state = jumpState;
		break;
	case PlayerState::Falling:
		playerData->state = jumpState;
		dummy = 1;
		break;
	case PlayerState::Injured:
		playerData->state = injuredState;
		break;
	}

	currentState = playerData->state->GetState();
	playerData->state->ResetState(dummy);
}

void Player::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, float dt) {
	auto impactorRect = impactor->GetRect();
	auto impactorDir = impactor->GetMoveDirection();
	auto impactorTag = impactor->GetTag();
	float playerBottom = position.y - GetBigHeight() / 2.0 + collisionTime * dt * velocity.y;;

	D3DXVECTOR2 newVelocity = velocity;

	if (impactor->GetType() == StaticType)
		if (side == Bottom && status != Jumping && (status != Climbing || impactorTag != THINSURFACE)) {
			
			if (round(playerBottom) == impactorRect.top && velocity.y <= 0) {
				newVelocity.y *= collisionTime;
				checkGroundInFrame = true;
			}
		}
		else {

			bool specialWall = ((int)impactorRect.right - (int)impactorRect.left <= 16) && impactorTag == GROUND;

			bool canPassLeft = specialWall && velocity.x < 0 && impactorDir == RightToLeft;
			bool canPassRight = specialWall && velocity.x > 0 && impactorDir == RightToLeft;

			float slashCaseLeft = (impactorRect.left - GetBody().right) / (dt * velocity.x);
			float slashCaseRight = (impactorRect.right - GetBody().left) / (dt * velocity.x);

			if (currentState == PlayerState::Slash) {
				//BUG
				if (collisionTime == 0)
					collisionTime = min(slashCaseLeft, slashCaseRight);
				if (collisionTime > 1)
					collisionTime = 0;
			}

			float playerLeft = GetBody().left + velocity.x * collisionTime * dt;
			float playerRight = GetBody().right + velocity.x * collisionTime * dt;

			if ((side == Left && velocity.x < 0 && impactorRect.right == round(playerLeft)) || ((side == Right && velocity.x > 0) && impactorRect.left == round(playerRight))) {
				if (impactorRect.top > round(playerBottom) && impactorRect.bottom <= round(playerBottom)) {

					if (!canPassLeft || !canPassRight)
						newVelocity.x *= collisionTime;

					if ((int)impactorRect.top - (int)impactorRect.bottom > 32) {
						//if (GetRect().bottom < impactorRect.bottom)
						//	return;
						int sign = -1;
						if (impactorTag == LADDER)
							sign = 1;
						bool climbToWall = (impactorDir != RightToLeft && velocity.x < 0) || (impactorDir != LeftToRight && velocity.x > 0);
						bool climbToLadder = (sign == 1) && (playerBottom + LADDER_OFFSET < impactorRect.top) && climbToWall;
						climbToWall = climbToWall && (sign == -1) && velocity.y != 0;
						if (climbToWall || climbToLadder) {
							SetMoveDirection(impactor->GetPosition().x > position.x ? LeftToRight : RightToLeft);
							SetState(PlayerState::Climb, sign * impactorRect.top);
						}
					}
				}

			}
		}

	velocity = newVelocity;

	playerData->state->OnCollision(impactor, side);

}

BoxCollider Player::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	if (direction == LeftToRight) {
		r.left = position.x + collider.left;
		r.right = position.x + collider.right;
	}
	else {
		r.left = position.x - collider.right;
		r.right = position.x - collider.left;
	}
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

float Player::GetBigWidth() {
	return Entity::GetWidth();
}

float Player::GetBigHeight() {
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

void Player::SetMoveDirection(Entity::EntityDirection dir) {
	if (dir == direction)
		return;
	direction = dir;
	//DebugOut(L"left: %f, right: %f\n", collider.left, collider.right);
}

BoxCollider Player::GetBody() {
	return playerData->state->GetBody();
}

void Player::InjuredByOther(Entity *impactor) {
	if (isImmortal)
		return;
	float impactorX = impactor->GetPosition().x;
	if (impactorX > GetPosition().x)
		SetMoveDirection(Entity::LeftToRight);
	else
		SetMoveDirection(Entity::RightToLeft);
	if (currentState != PlayerState::Climb)
		SetState(PlayerState::Injured);
	else
		OnImmortal();
	DataManager::MinusHealth();
	DataManager::GetHealth();
}

void Player::OnImmortal() {
	isImmortal = true;
}

void Player::OffImmortal() {
	isImmortal = false;
}
#include "ObjectPooling.h"
void Player::CheckForUseItem() {
	enum Tag item = DataManager::GetItem();
	switch (item) {
	case (NONE):
		ThrowFlames();
		//ThrowBigShuriken();
		break;
	case (THROWINGSTAR):
		ThrowShuriken();
		break;
	case (WINDMILLSTAR):
		ThrowBigShuriken();
		break;
	case (FLAMES):
		ThrowFlames();
		break;
	}
}

void Player::ThrowShuriken() {

	if (DataManager::GetSpiritPoint() < SHURIKEN_COST)
		return;

	ObjectPooling *pool = ObjectPooling::GetInstance();

	D3DXVECTOR3 position = this->position;
	if (direction == LeftToRight)
		position.x += collider.right;
	else
		position.x += collider.left;

	if (ObjectPooling::GetInstance()->Instantiate(SHURIKEN_POOL_INDEX, position))
		DataManager::ConsumeSpiritPoint(SHURIKEN_COST);
}

void Player::ThrowBigShuriken() {
	//--DEBUG
	if (DataManager::GetSpiritPoint() < 0) //BIGSHURIKEN_COST)
		return;

	ObjectPooling *pool = ObjectPooling::GetInstance();

	D3DXVECTOR3 position = this->position;
	if (direction == LeftToRight)
		position.x += collider.right;
	else
		position.x += collider.left;

	//--DEBUG WITH ZERO
	if (ObjectPooling::GetInstance()->Instantiate(BIGSHURIKEN_POOL_INDEX, position))
		DataManager::ConsumeSpiritPoint(0);// BIGSHURIKEN_COST);
}

void Player::ThrowFlames() {
	//--DEBUG
	if (DataManager::GetSpiritPoint() < 0) //BIGSHURIKEN_COST)
		return;
	ObjectPooling *pool = ObjectPooling::GetInstance();

	if (pool->CheckQuantity(FLAMES_POOL_INDEX) < 3)
		return;

	D3DXVECTOR3 position = this->position;
	if (direction == LeftToRight)
		position.x += collider.right;
	else
		position.x += collider.left;

	//--DEBUG WITH ZERO
	for (int i = 0; i < 3; i++)
		ObjectPooling::GetInstance()->Instantiate(FLAMES_POOL_INDEX, position);

	DataManager::ConsumeSpiritPoint(0);// BIGSHURIKEN_COST);
}

BoxCollider Player::GetCollider() {
	return collider;
}

void Player::HandleInput() {
	if (this->playerData->state)
		playerData->state->HandleInput();
}