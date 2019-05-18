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
	point = 100;
}

void Knife::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

void Knife::Update(double dt) {

	Weapon::Update(dt);

	//Mathf.Lerp(a, b, t);
	if (tParam < 1)
		tParam += dt * KNIFE_SPEED;

	velocity.x = MyHelper::Lerp(startVelocity.x, startVelocity.x > 0 ? KNIFE_THROW_FORCE_MIN_X : -KNIFE_THROW_FORCE_MIN_X, tParam);
	velocity.y = MyHelper::Lerp(startVelocity.y, -KNIFE_THROW_FORCE_Y, tParam);
}

#include "Debug.h"
void Knife::Instantiate(D3DXVECTOR3 position) {

	tParam = 0;

	this->position = position;

	srand(time(NULL));
	velocity.x = (float)(rand() % (KNIFE_THROW_FORCE_MAX_X - KNIFE_THROW_FORCE_MIN_X + 1)) + KNIFE_THROW_FORCE_MIN_X;

	//DebugOut(L"velocity.x = %f\n", velocity.x);

	if (Camera::GetInstance()->GetPosition().x < position.x)
		velocity.x = -velocity.x;

	velocity.y = KNIFE_THROW_FORCE_Y;

	startVelocity = velocity;
	SetVelocity(velocity);
	Weapon::Spawn();
}