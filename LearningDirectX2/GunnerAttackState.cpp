#include "GunnerAttackState.h"
#include "Enemy.h"

GunnerAttackState::GunnerAttackState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_GUNNER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 2, 2, 2, 2, 2, GUNNER_ATTACK_FRAME * (1 / 60.0f));
}

GunnerAttackState::~GunnerAttackState() {
}

void GunnerAttackState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(10);
	enemy->SetColliderBottom(-14);
	enemy->SetColliderLeft(-10);
	enemy->SetColliderRight(6);

	enemy->SetVx(0);

	((Gunner*)enemy)->SpawnBigBullet();
	gnhpSound::GetInstance()->PlayFX(SOUND_BIGBULLET);

	EnemyState::ResetState();
}

void GunnerAttackState::Update(double dt) {
	m_Animation->Update(dt);
	if (m_Animation->IsLastFrame(dt))
		enemyData->enemy->SetState(EnemyState::Follow);
}
