#include "Knife.h"

Knife::Knife() : Weapon() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_KNIFE, "Resources/Sprites/knifespritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	PDIRECT3DTEXTURE9 tex = textures->Get(TEX_KNIFE);
	anim = new Animation();
	anim->AddFrames(tex, 1, 4, KNIFE_FRAME * (1 / 60.0f));

	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);

	width = desc.Width / 4.0;
	height = desc.Height;

	SetColliderTop(width / 2);
	SetColliderBottom(-width / 2);
	SetColliderLeft(-height / 2);

	isActive = false;
}

Knife::~Knife() {
}

void Knife::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

void Knife::Update(double dt) {


	//if (abs(velocity.x) > 0)
	//	velocity.x = 0;
	//else 
	//	velocity.x -= KNIFE_DRAG_FORCE;

	if (velocity.y < -KNIFE_THROW_FORCE_Y)
		velocity.y = -KNIFE_THROW_FORCE_Y;
	else
		velocity.y -= CAT_GRAVITY;

	Weapon::Update(dt);
}

BoxCollider Knife::GetCollider() {
	return collider;
}

#include "Debug.h"
void Knife::Instantiate(D3DXVECTOR3 position) {
	this->position = position;

	srand(time(NULL));
	velocity.x = (float)(rand() % (KNIFE_THROW_FORCE_MAX_X - KNIFE_THROW_FORCE_MIN_X + 1)) + KNIFE_THROW_FORCE_MIN_X;

	//DebugOut(L"velocity.x = %f\n", velocity.x);

	if (Camera::GetInstance()->GetPosition().x < position.x)
		velocity.x = -velocity.x;

	velocity.y = KNIFE_THROW_FORCE_Y;
	SetVelocity(velocity);

	Weapon::Spawn();
}