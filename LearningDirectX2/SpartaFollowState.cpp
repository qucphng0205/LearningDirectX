#include "SpartaFollowState.h"
#include "Enemy.h"

SpartaFollowState::SpartaFollowState(EnemyData *data) {
	EnemyState::EnemyState(data);
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_SPARTA);
	m_Animation = new Animation();
	m_Animation->AddFrames(texture, 1, 3, 0.3f);
}

SpartaFollowState::~SpartaFollowState() {
}

void SpartaFollowState::ResetState() {

	auto enemy = enemyData->enemy;
	
	enemy->SetColliderTop(12);
	enemy->SetColliderBottom(-21);
	enemy->SetColliderLeft(-12);
}

void SpartaFollowState::Update(double dt) {
	m_Animation->Update(dt);
}
