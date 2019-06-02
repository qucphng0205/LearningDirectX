#include "BigExplosion.h"

BigExplosion::BigExplosion(D3DXVECTOR3 position, float durationTime) : Effect(position, durationTime) {
	Textures *texs = Textures::GetInstance();
	texs->Add(TEX_BIGEXPLOSION, "Resources/Sprites/bigexplosionspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	anim = new Animation();
	anim->AddFrames(texs->Get(TEX_BIGEXPLOSION), 1, 2, BIGEXPLOSION_FRAME * (1.0 / 60));
}