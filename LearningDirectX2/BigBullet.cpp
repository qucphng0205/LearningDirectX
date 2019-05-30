#include "BigBullet.h"

BigBullet::BigBullet() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_BIGBULLET, "Resources/Sprites/bigbulletspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	PDIRECT3DTEXTURE9 tex = textures->Get(TEX_BIGBULLET);
	anim = new Animation();
	anim->AddFrames(tex, 1, 1, 1000 * (1 / 60.0f));

	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);

	width = desc.Width;
	height = desc.Height;

	SetColliderTop(width / 2);
	SetColliderBottom(-width / 2);
	SetColliderLeft(-height / 2);

	isActive = false;
	point = 200;
}

BigBullet::~BigBullet() {
}

void BigBullet::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
}

void BigBullet::Update(double dt) {
	Weapon::Update(dt);
}

void BigBullet::Instantiate(D3DXVECTOR3 position) {
	this->position = position;

	velocity.x = BIG_BULLET_FORCE;

	//DebugOut(L"velocity.x = %f\n", velocity.x);

	if (Camera::GetInstance()->GetPosition().x < position.x)
		velocity.x = -velocity.x;

	velocity.y = 0;

	SetVelocity(velocity);
	Weapon::Spawn();
}
