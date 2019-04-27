#include "Cat.h"

Cat::Cat() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_CAT, "Resources/Sprites/catspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	catFollowState = new CatFollowState(enemyData);
	//Set tag
	tag = Entity::Cat;
	SetState(EnemyState::Follow);
	D3DSURFACE_DESC desc;
	textures->Get(TEX_CAT)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
}

Cat::~Cat() {
}

void Cat::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

void Cat::SetColliderTop(int top) {
	collider.top = top;
}

void Cat::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Cat::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Cat::SetColliderRight(int right) {
	collider.right = right;
}

void Cat::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = catFollowState;
	enemyData->state->ResetState();
}

BoxCollider Cat::GetCollider() {
	return collider;
}

void Cat::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
