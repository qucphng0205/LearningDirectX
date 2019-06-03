#include "SoldierAttackState.h"
#include "Enemy.h"

SoldierAttackState::SoldierAttackState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_SOLDIER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 2, 2, 2, 2, 2, SOLDIER_ATTACK_FRAME * (1 / 60.0f));
}

SoldierAttackState::~SoldierAttackState() {
}

void SoldierAttackState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(16);
	enemy->SetColliderBottom(-16);
	enemy->SetColliderLeft(-8);

	enemy->SetVx(0);

	frame = 0;

	gnhpSound::GetInstance()->PlayFX(SOUND_BULLET);

	EnemyState::ResetState();
}

void SoldierAttackState::Update(double dt) {
	m_Animation->Update(dt);
	frame++;
	if (frame >= SOLDIER_ATTACK_LOOP_FRAMES)
		enemyData->enemy->SetState(EnemyState::Follow);
	if (frame % SOLDIER_ATTACK_SHOOT_FRAMES == 0)
		((Soldier*)enemyData->enemy)->SpawnBullet();
}
