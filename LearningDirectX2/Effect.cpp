#include "Effect.h"

Effect::Effect(D3DXVECTOR3 position, float durationTime) {
	durationTime = durationTime;
	this->position = position;
}

bool Effect::Update(double dt) {
	//false will destroy this

	anim->Update(dt);

	if (anim->GetPercentTime() > 1)
		return false;

	return true;
}

void Effect::Render() {
	anim->Render(position);
}