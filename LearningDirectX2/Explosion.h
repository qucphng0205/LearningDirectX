#pragma once
#include "Effect.h"
#include "Textures.h"
#include "GameConfig.h"

class Explosion : public Effect {
public:
	Explosion(D3DXVECTOR3 position, float durationTime = 1);
};