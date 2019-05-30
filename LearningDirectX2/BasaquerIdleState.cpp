#include "BasaquerIdleState.h"
#include "Enemy.h"

BasaquerIdleState::BasaquerIdleState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_BASAQUER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 1, 1, 1, 2, 1, 45 * (1 / 60.0f));
}

BasaquerIdleState::~BasaquerIdleState() {
}

void BasaquerIdleState::ResetState() {

	auto enemy = enemyData->enemy;
	auto enemyX = enemy->GetPosition().x;
	auto playerX = Camera::GetInstance()->GetPosition().x;

	enemy->SetColliderTop(27);
	enemy->SetColliderBottom(-27);
	enemy->SetColliderLeft(-19);

	EnemyState::ResetState();
}

void BasaquerIdleState::Update(double dt) {
	if (m_Animation->IsLastFrame(dt)) {
		enemyData->enemy->SetState(Attack);
		return;
	}
	enemyData->enemy->SetVelocity(D3DXVECTOR2(0, 0));
	m_Animation->Update(dt);
}
