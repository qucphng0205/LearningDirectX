#include "ThrowerFollowState.h"
#include "Enemy.h"

ThrowerFollowState::ThrowerFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_THROWER);
	m_Animation = new Animation();
	m_Animation->AddFrames(texture, 1, 3, THROWER_FRAME * (1 / 60.0f));
}

ThrowerFollowState::~ThrowerFollowState() {
}

void ThrowerFollowState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(13);
	enemy->SetColliderBottom(-22);
	enemy->SetColliderLeft(-12);
}

void ThrowerFollowState::Update(double dt) {
	m_Animation->Update(dt);
}
