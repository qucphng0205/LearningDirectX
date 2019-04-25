#include "Sparta.h"

Sparta::Sparta() {
	Enemy::Enemy();
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SPARTA, "Resources/Sprites/spartaspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	SetTag(Entity::Sparta);

	D3DSURFACE_DESC desc;
	textures->Get(TEX_SPARTA)->GetLevelDesc(0, &desc);
	width = desc.Width / 3;
	height = desc.Height;
}

Sparta::~Sparta() {
}

void Sparta::Render() {
	enemyData->state->Render();
}

void Sparta::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

void Sparta::SetVelocity(D3DXVECTOR2 velocity) {
	if (velocity.x > 0)
		direction = LeftToRight;
	else
		if (velocity.x < 0)
			direction = RightToLeft;
	Enemy::SetVelocity(velocity);
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

void Sparta::SetStage(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = spartaFollowState;
	enemyData->state->ResetState();
}

BoxCollider Sparta::GetCollider() {
	return collider;
}
