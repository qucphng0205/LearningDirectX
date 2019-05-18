#include "CatFollowState.h"
#include "Enemy.h"

CatFollowState::CatFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_CAT);
	m_Animation = new Animation();
	m_Animation->AddFrames(texture, 1, 2, CAT_FRAME * (1 / 60.0f));
}

CatFollowState::~CatFollowState() {
}

void CatFollowState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(12);
	enemy->SetColliderBottom(-12);
	enemy->SetColliderLeft(-8);

	if (enemy->GetSpawnDirection() == Entity::LeftToRight)
		enemy->SetVx(110);
	else
		enemy->SetVx(-110);

	EnemyState::ResetState();
}

void CatFollowState::Update(double dt) {
	m_Animation->Update(dt);
}
