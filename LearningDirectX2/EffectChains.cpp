//--OBSOLETE

//#include "EffectChains.h"
//
//void EffectChains::Add(EffectChain *newChain) {
//	newChain->prev = NULL;
//	newChain->next = chains;
//	chains = newChain;
//	if (newChain->next != NULL)
//		newChain->next->prev = newChain;
//}
//
//void EffectChains::Remove(EffectChain *chain) {
//	if (chain->prev != NULL)
//		chain->prev->next = chain->next;
//	if (chain->next != NULL)
//		chain->next->prev = chain->prev;
//	if (chains == chain)
//		chains = chain->next;
//}
