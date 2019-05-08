#include "Explosion.h"

Explosion::Explosion(D3DXVECTOR3 position, float durationTime) : Effect(position, durationTime) {
	Textures *texs = Textures::GetInstance();
	texs->Add(TEX_EXPLOSION, "Resources/Sprites/explosionspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	anim = new Animation();
	anim->AddFrames(texs->Get(TEX_EXPLOSION), 1, 5, EXPLOSION_FRAME * (1.0 / 60));
}