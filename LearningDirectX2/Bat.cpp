#include "Bat.h"
#include "Debug.h"

Bat::Bat() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_BAT, "Resources/Sprites/batspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	batFollowState = new BatFollowState(enemyData);
	//Set Tag
	Tag = BAT;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_BAT)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
	point = 300;
}

Bat::~Bat() {
	delete batFollowState;
	batFollowState = NULL;
}

void Bat::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
}

#include "Player.h"
void Bat::Update(double dt) {

	Enemy::Update(dt);

	if (direction == LeftToRight)
		velocity.x = 50;
	else
		velocity.x = -50;

	if (position.y <= 40)
		velocity.y = 90;
	else if (position.y >= 90)
		velocity.y = -90;
}

void Bat::SetColliderTop(int top) {
	collider.top = top;
}

void Bat::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Bat::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Bat::SetColliderRight(int right) {
	collider.right = right;
}

void Bat::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = batFollowState;
	enemyData->state->ResetState();
}

BoxCollider Bat::GetCollider() {
	return collider;
}

void Bat::Spawn() {
	if (position.y > 40)
		velocity.y = -90;
	else
		velocity.y = 90;
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
