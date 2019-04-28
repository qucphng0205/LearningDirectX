#include "Soldier.h"

Soldier::Soldier() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
		textures->Add(TEX_SOLDIER, "Resources/Sprites/soldierspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	soldierFollowState = new SoldierFollowState(enemyData);
	soldierAttackState = new SoldierAttackState(enemyData);
	//Set tag
	tag = Entity::Soldier;
	SetState(EnemyState::Follow);
	D3DSURFACE_DESC desc;
	textures->Get(TEX_SOLDIER)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
}

Soldier::~Soldier() {
}

void Soldier::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

void Soldier::SetColliderTop(int top) {
	collider.top = top;
}

void Soldier::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Soldier::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Soldier::SetColliderRight(int right) {
	collider.right = right;
}

void Soldier::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = soldierFollowState;
	if (state == EnemyState::Attack)
		enemyData->state = soldierAttackState;
	enemyData->state->ResetState();
}

BoxCollider Soldier::GetCollider() {
	return collider;
}

void Soldier::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
