#include "Weapon.h"

Weapon::Weapon() {
	tag = Entity::Projectile;
	type = Entity::ProjectileType;
}

Weapon::~Weapon() {
	delete anim;
	anim = NULL;
}

void Weapon::Update(double dt) {
	anim->Update(dt);
	Entity::Update(dt);
}

void Weapon::Render() {
	anim->Render(position);
}

BoxCollider Weapon::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;

	if (direction == Entity::LeftToRight) {
		r.left = position.x + collider.left;
		r.right = position.x + collider.right;
	}
	else {
		r.left = position.x - collider.right;
		r.right = position.x - collider.left;
	}
	return r;
}

void Weapon::SetActive(bool active) {
	if (active) 
		//IS A BUG, INSTANTIATE WITH POSITION INSTEAD, BRO
		Spawn();
	else
		MakeInactive();
}

void Weapon::SetColliderTop(int top) {
	collider.top = top;
}

void Weapon::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -left;
}

void Weapon::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Weapon::SetColliderRight(int right) {
	collider.right = right;
}

void Weapon::SetMoveDirection(Entity::EntityDirection dir) {
	direction = dir;
}

float Weapon::GetWidth() {
	return collider.right - collider.left;
}

float Weapon::GetBigWidth() {
	return width;
}

float Weapon::GetHeight() {
	return collider.top - collider.bottom;
}

float Weapon::GetBigHeight() {
	return height;
}

void Weapon::OnCollision(Entity * impactor, SideCollision side, float collisionTime) {
}

void Weapon::Instantiate(D3DXVECTOR3 position) {
	this->position = position;
	Spawn();
}

void Weapon::OnDestroy() {
	EffectChain *effect = new EffectChain(new Explosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
}

void Weapon::MakeInactive() {
	isActive = false;
}

void Weapon::Spawn() {
	anim->ResetAnimation();
	isActive = true;
}
