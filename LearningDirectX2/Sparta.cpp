#include "Sparta.h"

Sparta::Sparta() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SPARTA, "Resources/Sprites/spartaspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_SPARTA);
	anim = new Animation();
	anim->AddFrames(texture, 1, 3, 0.3f);

	SetTag(Entity::Enemy);

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	width = desc.Width / 3;
	height = desc.Height;

	collider.top = 12;
	collider.bottom = -21;
	collider.right = 12;
	collider.left = -12;
}

Sparta::~Sparta() {
}

void Sparta::Update(double dt) {
	Entity::Update(dt);
}

void Sparta::Render() {
	anim->Render(position);
}

void Sparta::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

BoxCollider Sparta::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

void Sparta::SetVelocity(D3DXVECTOR2 velocity) {
	this->velocity = velocity;
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

BoxCollider Sparta::GetCollider() {
	return collider;
}
