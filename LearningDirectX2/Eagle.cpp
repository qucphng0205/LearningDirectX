#include "Eagle.h"

Eagle::Eagle() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_EAGLE, "Resources/Sprites/eaglespritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	eagleFollowState = new EagleFollowState(enemyData);
	//Set tag
	tag = Entity::Eagle;
	SetState(EnemyState::Follow);
	D3DSURFACE_DESC desc;
	textures->Get(TEX_EAGLE)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
}

Eagle::~Eagle() {
}

void Eagle::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

void Eagle::SetColliderTop(int top) {
	collider.top = top;
}

void Eagle::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Eagle::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Eagle::SetColliderRight(int right) {
	collider.right = right;
}

void Eagle::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = eagleFollowState;
	enemyData->state->ResetState();
}

BoxCollider Eagle::GetCollider() {
	return collider;
}

void Eagle::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
