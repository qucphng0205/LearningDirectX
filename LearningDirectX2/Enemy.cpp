#include "Enemy.h"

Enemy::Enemy() : Entity() {
	type = Entity::EnemyType;
	enemyData = new EnemyData();
	enemyData->enemy = this;
}

Enemy::~Enemy() {
}

void Enemy::Update(double dt) {
	if (isActive)
		enemyData->state->Update(dt);
}

void Enemy::Render() {
	if (isActive)
		enemyData->state->Render();
}

BoxCollider Enemy::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

BoxCollider Enemy::GetSpawnRect() {
	return spawnBox;
}

void Enemy::SetActive(bool active) {
	isActive = active;
	if (isActive) 
		Spawn();
}

void Enemy::SetRect(BoxCollider box) {
	collider = box;
}

void Enemy::SetSpawnBox(BoxCollider box, int direction) {
	spawnBox = box;
	spawnPosition.x = (box.left + box.right) / 2.0f;
	spawnPosition.y = (box.bottom + box.top) / 2.0f;
	spawnDirection = (EntityDirection)direction;
	MakeInactive();
}

void Enemy::SetColliderTop(int top) {
	collider.top = top;
}

void Enemy::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Enemy::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Enemy::SetColliderRight(int right) {
	collider.right = right;
}

float Enemy::GetWidth() {
	return collider.right - collider.left;
}

float Enemy::GetHeight() {
	return collider.top - collider.bottom;
}

BoxCollider Enemy::GetCollider() {
	return collider;
}

void Enemy::OnCollision(Entity * impactor, SideCollision side, float collisionTime) {
}

void Enemy::MakeInactive() {
	isActive = false;
	position = spawnPosition;
	direction = spawnDirection;
	SetColliderTop((spawnBox.top - spawnBox.bottom) / 2.0f);
	SetColliderBottom(-collider.top);
	SetColliderLeft((spawnBox.left - spawnBox.right) / 2.0f);
}

void Enemy::Spawn() {
	direction = spawnDirection;
	position.x = spawnBox.left - collider.left;
	position.y = spawnBox.bottom - collider.bottom;
}
