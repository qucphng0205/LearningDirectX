#pragma once
#include "Effect.h"
class EffectChains {
public:
	void Add(EffectChain *newChain);
	void Remove(EffectChain *effect);
private:
	EffectChain *chains;
};