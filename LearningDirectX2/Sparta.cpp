#include "Sparta.h"

Sparta::Sparta() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SPARTA, "Resources/Sprites/spartaspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	spartaFollowState = new SpartaFollowState(enemyData);
	//Set tag
	tag = Entity::Sparta;
	SetState(EnemyState::Follow);
	D3DSURFACE_DESC desc;
	textures->Get(TEX_SPARTA)->GetLevelDesc(0, &desc);
	width = desc.Width / 3;
	height = desc.Height;
}

Sparta::~Sparta() {
}

void Sparta::Render() {
	if (isActive)
		enemyData->state->Render();
}

void Sparta::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	if (!isActive)
		Enemy::OnCollision(impactor, side, collisionTime);
}

void Sparta::SetColliderTop(int top) {
	collider.top = top;
}

void Sparta::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Sparta::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Sparta::SetColliderRight(int right) {
	collider.right = right;
}

void Sparta::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = spartaFollowState;
	enemyData->state->ResetState();
}

BoxCollider Sparta::GetCollider() {
	return collider;
}

void Sparta::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}