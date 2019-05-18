//#include "Shuriken.h"
//
//Shuriken::Shuriken() {
//	auto textures = Textures::GetInstance();
//	textures->Add(TEX_BIGSHURIKEN, "Resources/Sprites/bigshurikenspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
//
//	PDIRECT3DTEXTURE9 tex = textures->Get(TEX_BIGSHURIKEN);
//
//	anim = new Animation();
//	anim->AddFrames(tex, 1, 2, BIGSHURIKEN_FRAME * (1 / 60.0f));
//
//	D3DSURFACE_DESC desc;
//	tex->GetLevelDesc(0, &desc);
//
//	width = desc.Width / 2;
//	height = desc.Height;
//
//	SetColliderTop(width / 2);
//	SetColliderBottom(-width / 2);
//	SetColliderLeft(-height / 2);
//
//	isActive = false;
//	point = 0;
//}
//
//void Shuriken::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
//}
//
//void Shuriken::Instantiate(D3DXVECTOR3 position) {
//	velocity.x = BIGSHURIKEN_FRAME;
//	velocity.y = 0;
//
//	if (Camera::GetInstance()->GetPosition().x > position.x)
//		velocity.x = -velocity.x;
//
//	SetVelocity(velocity);
//
//	Weapon::Instantiate(position);
//}
