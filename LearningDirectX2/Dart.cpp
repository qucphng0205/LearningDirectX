#include "Dart.h"

int Dart::quantity = 0;

Dart::Dart() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_DART, "Resources/Sprites/dartspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	PDIRECT3DTEXTURE9 tex = textures->Get(TEX_DART);

	anim = new Animation();
	anim->AddFrames(tex, 1, 4, 1000 * (1 / 60.0f));

	Tag = Tag::EPROJECTILE;
	type = Layer::EProjectileType;

	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);

	width = desc.Width / 4;
	height = desc.Height;

	SetColliderTop(width / 2);
	SetColliderBottom(-width / 2);
	SetColliderLeft(-height / 2);

	isActive = false;
	point = 100;

	index = quantity++;
}

Dart::~Dart() {
	quantity--;
}

void Dart::Update(double dt) {
	Weapon::Update(dt);
}

void Dart::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
}

//instantiate flames please attached set velocity
void Dart::Instantiate(D3DXVECTOR3 position) {

	velocity.x = 120;

	switch (index) {
	case 0:
		position.x += 10;
		position.y += 10;
		break;
	case 1:
		break;
	case 2:
		position.x -= 10;
		position.y -= 10;
		break;
	}

	if (Player::GetInstance()->GetPosition().x > position.x)
		velocity.x = -velocity.x;

	SetVelocity(velocity);

	Weapon::Instantiate(position);
}

EarnedData Dart::OnDestroy() {
	SetActive(false);
	return EarnedData(point);
}
