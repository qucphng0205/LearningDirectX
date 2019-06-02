#pragma once
#include "Effect.h"
#include "Textures.h"
#include "GameConfig.h"

class BigExplosion : public Effect {
public:
	BigExplosion(D3DXVECTOR3 position, float durationTime = 1);
};