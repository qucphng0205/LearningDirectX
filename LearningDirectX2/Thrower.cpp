#include "Thrower.h"

Thrower::Thrower() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
		textures->Add(TEX_THROWER, "Resources/Sprites/throwerspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	throwerFollowState = new ThrowerFollowState(enemyData);
	//Set tag
	tag = Entity::Thrower;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_THROWER)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
}

Thrower::~Thrower() {
}

void Thrower::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
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
	if (state == EnemyState::Follow)
		enemyData->state = throwerFollowState;
	enemyData->state->ResetState();
}

BoxCollider Thrower::GetCollider() {
	return collider;
}

void Thrower::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
