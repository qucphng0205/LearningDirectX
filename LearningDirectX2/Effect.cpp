#include "Effect.h"

Effect::Effect(D3DXVECTOR3 position, float durationTime) {
	this->durationTime = durationTime;
	this->position = position;
}

bool Effect::Update(double dt) {
	//false will destroy this

	anim->Update(dt);

	if (anim->GetPercentTime() > durationTime)
		return false;

	return true;
}

void Effect::Render() {
	anim->Render(position);
}

Effect::~Effect() {
	delete anim;
	anim = NULL;
}
