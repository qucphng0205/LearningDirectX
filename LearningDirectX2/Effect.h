#pragma once
#include <d3dx9.h>
#include "Animation.h"

class Effect;
struct EffectChain {
	Effect *data;
	EffectChain *prev, *next;
	EffectChain(Effect *data) : data(data), prev(NULL), next(NULL) {}
};

class Effect {
public:
	//percent time of animation to autoDestroy
	Effect(D3DXVECTOR3 position, float durationTime = 1);
	virtual bool Update(double dt);
	virtual void Render();
	D3DXVECTOR3 position;
	Animation *anim;
	//percentTime
	float durationTime;
};
