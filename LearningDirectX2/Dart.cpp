#include "Dart.h"

int Dart::quantity = 0;

Dart::Dart() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_DART, "Resources/Sprites/dartspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	PDIRECT3DTEXTURE9 tex = textures->Get(TEX_DART);

	anim = new Animation();
	anim->AddFrames(tex, 1, 1, 1000 * (1 / 60.0f));

	Tag = Tag::DART;
	type = Layer::EProjectileType;

	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);

	width = desc.Width;
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
	if (delay + dt > 0.1875f * (index + 1))
		Weapon::Update(dt);
	else
		delay += dt;
}

//instantiate flames please attached set velocity
void Dart::Instantiate(D3DXVECTOR3 position) {

	bool isReverse = false;

	velocity.x = 120;
	if (Player::GetInstance()->GetPosition().x < position.x) {
		velocity.x = -velocity.x;
	}

	SetVelocity(velocity);

	position.y -= 7;

	switch (index) {
	case 0:
		//position.x += isReverse ? -15 : 15;
		position.y += 15;
		break;
	case 1:
		break;
	case 2:
		//position.x -= isReverse ? -15 : 15;
		position.y -= 15;
		break;
	}

	delay = 0;
	Weapon::Instantiate(position);
}