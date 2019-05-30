#include "BigShuriken.h"

BigShuriken::BigShuriken() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_BIGSHURIKEN, "Resources/Sprites/bigshurikenspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	PDIRECT3DTEXTURE9 tex = textures->Get(TEX_BIGSHURIKEN);

	anim = new Animation();
	anim->AddFrames(tex, 1, 2, BIGSHURIKEN_FRAME * (1 / 60.0f));

	Tag = Tag::PPROJECTILE;
	type = Layer::PProjectileType;

	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);

	width = desc.Width / 2;
	height = desc.Height;

	SetColliderTop(width / 2);
	SetColliderBottom(-width / 2);
	SetColliderLeft(-height / 2);

	isActive = false;
	point = 0;
}

void BigShuriken::Update(double dt) {
	SetMoveDirection(Camera::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);

	Weapon::Update(dt);

	D3DXVECTOR3 target = Player::GetInstance()->GetPosition();
	D3DXVECTOR2 accelerate = D3DXVECTOR2(0, 0);
	//D3DXVECTOR2 dir = D3DXVECTOR2(target - position);
	//D3DXVec2Normalize(&dir, &dir);
	//dir.x *= 180.0f;
	//dir.y *= 180.0f;

	if (target.x < position.x)
		accelerate.x = -5;
	else if (target.x > position.x)
		accelerate.x = 5;

	position.y = MyHelper::Lerp(position.y, target.y, 0.06f);

	//--DEBUG
	//i++;
	//if (i == 110)
	//	i = i;
	//if (i == 60)
	//	i = 60;

	//SetVelocity(dir);
	AddVelocity(accelerate);
	velocity.x = MyHelper::Clamp(velocity.x, -190.0f, 190.0f);
	//velocity.y = MyHelper::Clamp(velocity.y, -80.0f, 80.0f);
}

void BigShuriken::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	auto impactorType = impactor->GetType();
	if (impactorType == Layer::EnemyType || impactorType == Layer::ItemHolderType || impactorType == Layer::EProjectileType) {
		impactor->OnDestroy();
	}
	else if (impactorType == Layer::PlayerType) {
		auto body = ((Player*)impactor)->GetBody();
		auto playerState = ((Player*)impactor)->GetState();
		if (playerState != PlayerState::UseItem)
			if (CollisionDetector::IsCollide(body, GetRect()))
				OnDestroy();
	}
}

void BigShuriken::Instantiate(D3DXVECTOR3 position) {
	velocity.x = BIGSHURIKEN_VELOCITY;
	velocity.y = 0;

	if (Player::GetInstance()->GetPosition().x > position.x)
		velocity.x = -velocity.x;

	SetVelocity(velocity);

	Weapon::Instantiate(position);
}

EarnedData BigShuriken::OnDestroy() {
	SetActive(false);
	return EarnedData(0);
}
