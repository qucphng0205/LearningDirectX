#include "Enemy.h"

Enemy::Enemy() {
	type = Entity::EnemyType;
}

Enemy::~Enemy() {
}

BoxCollider Enemy::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

void Enemy::SetSpawnBox(BoxCollider box, int direction) {
	spawnBox = box;
	spawnPosition.x = box.left + width / 2.0f;
	spawnPosition.y = box.bottom + height / 2.0f;
	spawnDirection = (EntityDirection)direction;
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

BoxCollider Enemy::GetCollider() {
	return collider;
}

void Enemy::Spawn() {
	direction = spawnDirection;
	position = spawnPosition;
}
