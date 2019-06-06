#include "BatFollowState.h"
#include "Enemy.h"

BatFollowState::BatFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_BAT);
	m_Animation = new Animation();
	m_Animation->AddFrames(texture, 1, 2, BAT_FRAME * (1 / 60.0f));
}

BatFollowState::~BatFollowState() {
}

void BatFollowState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(6);
	enemy->SetColliderBottom(-6);
	enemy->SetColliderLeft(-8);

	EnemyState::ResetState();
}

void BatFollowState::Update(double dt) {
	m_Animation->Update(dt);
}
