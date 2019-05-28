#include "Thrower.h"

Thrower::Thrower() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_THROWER, "Resources/Sprites/throwerspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	throwerFollowState = new ThrowerFollowState(enemyData);
	throwerAttackState = new ThrowerAttackState(enemyData);
	//Set Tag
	Tag = THROWER;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_THROWER)->GetLevelDesc(0, &desc);

	width = desc.Width / 2.0;
	height = desc.Height / 2.0;

	point = 300;
}

Thrower::~Thrower() {
	delete throwerFollowState;
	throwerFollowState = NULL;
	delete throwerAttackState;
	throwerAttackState = NULL;
}

void Thrower::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, float dt) {
	Enemy::OnCollision(impactor, side, collisionTime);
	if (impactor->GetType() == Layer::StaticType && side == Bottom)
		onGround = true;
}

void Thrower::SetVelocity(D3DXVECTOR2 vel) {
	velocity = vel;
}

void Thrower::SetVx(float vx) {
	velocity.x = vx;
}

void Thrower::Update(double dt) {
	auto center = GetRect().GetCenter().x;
	SetMoveDirection(Camera::GetInstance()->GetPosition().x < center ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
	if (!onGround)
		AddVy(-CAT_GRAVITY);
	onGround = false;
}

void Thrower::SetColliderTop(int top) {
	collider.top = top;
}

void Thrower::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Thrower::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Thrower::SetColliderRight(int right) {
	collider.right = right;
}

void Thrower::SetState(EnemyState::State state) {
	if (state == EnemyState::Attack)
		if (!ObjectPooling::GetInstance()->CheckQuantity(KNIFE_POOL_INDEX))
			return;

	if (state == EnemyState::Follow)
		enemyData->state = throwerFollowState;
	else
		enemyData->state = throwerAttackState;
	enemyData->state->ResetState();
}

BoxCollider Thrower::GetCollider() {
	return collider;
}

void Thrower::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}

void Thrower::SpawnKnife() {
	D3DXVECTOR3 position = this->position;
	position.y += collider.top;
	if (!ObjectPooling::GetInstance()->Instantiate(KNIFE_POOL_INDEX, position))
		SetState(EnemyState::Follow);
}
