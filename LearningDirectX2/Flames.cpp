#include "Flames.h"

int Flames::quantity = 0;

Flames::Flames() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_FLAMESPROJECTILE, "Resources/Sprites/flamesspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	PDIRECT3DTEXTURE9 tex = textures->Get(TEX_FLAMESPROJECTILE);

	anim = new Animation();
	anim->AddFrames(tex, 1, 4, FLAMES_FRAME * (1 / 60.0f));

	Tag = Tag::PPROJECTILE;
	type = Layer::PProjectileType;

	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);

	width = desc.Width / 4;
	height = desc.Height;

	SetColliderTop(width / 2);
	SetColliderBottom(-width / 2);
	SetColliderLeft(-height / 2);

	isActive = false;
	point = 0;

	index = quantity++;
}

Flames::~Flames() {
	quantity--;
}

void Flames::Update(double dt) {
	SetMoveDirection(Camera::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);

	Weapon::Update(dt);
}

void Flames::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::EnemyType || impactorType == Layer::ItemHolderType || impactorType == Layer::EProjectileType) {
		impactor->OnDestroy();
		OnDestroy();
	}
}

//instantiate flames please attached set velocity
void Flames::Instantiate(D3DXVECTOR3 position) {
	
	velocity.x = FLAMES_VELOCITY_X;

	switch (index) {
	case 0:
		velocity.y = FLAMES_VELOCITY_Y_0;
		break;
	case 1:
		velocity.y = FLAMES_VELOCITY_Y_1; 
		break;
	case 2:
		velocity.y = FLAMES_VELOCITY_Y_2; 
		break;
	}

	if (Player::GetInstance()->GetPosition().x > position.x)
		velocity.x = -velocity.x;

	SetVelocity(velocity);

	Weapon::Instantiate(position);
}

EarnedData Flames::OnDestroy() {
	SetActive(false);
	return EarnedData(0);
}
