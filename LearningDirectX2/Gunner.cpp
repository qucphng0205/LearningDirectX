#include "Gunner.h"

Gunner::Gunner() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_GUNNER, "Resources/Sprites/gunnerspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	gunnerFollowState = new GunnerFollowState(enemyData);
	gunnerAttackState = new GunnerAttackState(enemyData);
	//Set Tag
	Tag = GUNNER;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_GUNNER)->GetLevelDesc(0, &desc);
	width = desc.Width / 2.0;
	height = desc.Height / 2.0;
	point = 200;
}

Gunner::~Gunner() {
	delete gunnerFollowState;
	delete gunnerAttackState;
	gunnerAttackState = NULL;
	gunnerFollowState = NULL;
}

void Gunner::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	Enemy::OnCollision(impactor, side, collisionTime);
}

void Gunner::Update(double dt) {
	SetMoveDirection(Camera::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
}

void Gunner::SetColliderTop(int top) {
	collider.top = top;
}

void Gunner::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Gunner::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Gunner::SetColliderRight(int right) {
	collider.right = right;
}

void Gunner::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = gunnerFollowState;
	if (state == EnemyState::Attack)
		enemyData->state = gunnerAttackState;
	enemyData->state->ResetState();
}

BoxCollider Gunner::GetCollider() {
	return collider;
}

void Gunner::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}

void Gunner::SpawnBigBullet() {
	D3DXVECTOR3 position = this->position;
	//to attach to the head of the gun
	position.y += OFFSET_TO_BULLET;
	if (!ObjectPooling::GetInstance()->Instantiate(BIGBULLET_POOL_INDEX, position))
		SetState(EnemyState::Follow);
}
