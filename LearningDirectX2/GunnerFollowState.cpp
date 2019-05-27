#include "GunnerFollowState.h"
#include "Enemy.h"

GunnerFollowState::GunnerFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_GUNNER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 1, 1, 1, 2, 2, GUNNER_FOLLOW_FRAME * (1 / 60.0f));
}

GunnerFollowState::~GunnerFollowState() {
}

void GunnerFollowState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(10);
	enemy->SetColliderBottom(-14);
	enemy->SetColliderLeft(-10);
	enemy->SetColliderRight(6);

	EnemyState::ResetState();
}

void GunnerFollowState::Update(double dt) {
	m_Animation->Update(dt);
	if (m_Animation->IsLastFrame(dt))
		enemyData->enemy->SetState(EnemyState::Attack);
}
