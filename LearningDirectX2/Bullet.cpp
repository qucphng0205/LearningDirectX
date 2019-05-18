#include "Bullet.h"

Bullet::Bullet() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_BULLET, "Resources/Sprites/bulletspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	PDIRECT3DTEXTURE9 tex = textures->Get(TEX_BULLET);
	anim = new Animation();
	anim->AddFrames(tex, 1, 1, 1 * (1 / 60.0f));

	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);

	width = desc.Width;
	height = desc.Height;

	SetColliderTop(width / 2);
	SetColliderBottom(-width / 2);
	SetColliderLeft(-height / 2);

	isActive = false;
	point = 0;
}

void Bullet::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

void Bullet::Update(double dt) {
	Weapon::Update(dt);
}

void Bullet::Instantiate(D3DXVECTOR3 position) {
	this->position = position;

	velocity.x = BULLET_FORCE;

	//DebugOut(L"velocity.x = %f\n", velocity.x);

	if (Camera::GetInstance()->GetPosition().x < position.x)
		velocity.x = -velocity.x;

	velocity.y = 0;

	SetVelocity(velocity);
	Weapon::Spawn();
}
