#include "Knife.h"

Knife::Knife(Entity::EntityDirection dir) : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_KNIFE, "Resources/Sprites/knifespritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	knifeRotateState = new KnifeRotateState(enemyData);
	//Set tag
	tag = Entity::Projectile;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_KNIFE)->GetLevelDesc(0, &desc);

	width = desc.Width / 4.0;
	height = desc.Height;

	SetColliderTop(width / 2);
	SetColliderBottom(-width / 2);
	SetColliderLeft(-height / 2);

	offsetScaleX = 0;

	Spawn(dir);
}

Knife::~Knife() {
}

void Knife::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

void Knife::Update(double dt) {

	Enemy::Update(dt);

	if (velocity.x < 0)
		velocity.x = 0;
	else
		velocity.x -= KNIFE_DRAG_FORCE;

	if (velocity.y < -KNIFE_THROW_FORCE_Y)
		velocity.y = -KNIFE_THROW_FORCE_Y;
	else
		velocity.y -= CAT_GRAVITY;
}

void Knife::SetColliderTop(int top) {
	collider.top = top;
}

void Knife::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Knife::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Knife::SetColliderRight(int right) {
	collider.right = right;
}

void Knife::SetState(EnemyState::State state) {
	if (state == EnemyState::Rotate)
		enemyData->state = knifeRotateState;
	enemyData->state->ResetState();
}

BoxCollider Knife::GetCollider() {
	return collider;
}

void Knife::Spawn() {
	SetState(EnemyState::Rotate);
	Enemy::Spawn();
}

void Knife::Spawn(Entity::EntityDirection dir) {
	//if (dir == RightToLeft) 
	srand(time(NULL));
	velocity.x = (float)(rand() % (KNIFE_THROW_FORCE_MAX_X - KNIFE_THROW_FORCE_MIN_X + 1)) + KNIFE_THROW_FORCE_MIN_X;
	if (dir == RightToLeft)
		velocity.x = -velocity.x;
	velocity.y = KNIFE_THROW_FORCE_Y;
	SetVelocity(velocity);
	Spawn();
}
