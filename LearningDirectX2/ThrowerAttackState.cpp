#include "ThrowerAttackState.h"
#include "Enemy.h"
#include "Thrower.h"

ThrowerAttackState::ThrowerAttackState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_THROWER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 2, 2, 1, 2, 2, THROWER_ATTACK_FRAME * (1 / 60.0f));
}

ThrowerAttackState::~ThrowerAttackState() {
}

void ThrowerAttackState::ResetState() {

	auto enemy = enemyData->enemy;

	auto playerX = Camera::GetInstance()->GetPosition().x;
	auto enemyX = enemy->GetPosition().x;

	enemy->SetVx(0);

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(13);
	enemy->SetColliderBottom(-22);
	enemy->SetColliderLeft(-12);
	enemy->SetColliderRight(4);

	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();

	((Thrower*)enemy)->SpawnKnife();

	EnemyState::ResetState();
}

void ThrowerAttackState::Update(double dt) {
	if (m_Animation->IsLastFrame(dt)) {
		//--DEBUG
		m_Animation->IsLastFrame(dt);
		enemyData->enemy->SetState(Follow);
	}
	m_Animation->Update(dt);
}
