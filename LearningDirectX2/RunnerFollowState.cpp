#include "RunnerFollowState.h"
#include "Enemy.h"

RunnerFollowState::RunnerFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_RUNNER);
	m_Animation = new Animation();
	m_Animation->AddFrames(texture, 1, 2, RUNNER_FRAME * (1 / 60.0f));
}

RunnerFollowState::~RunnerFollowState() {
}

void RunnerFollowState::ResetState() {

	auto enemy = enemyData->enemy;
	auto enemyX = enemy->GetPosition().x;
	auto playerX = Camera::GetInstance()->GetPosition().x;

	if (playerX > enemyX)
		speed = (RUNNER_SPEED);
	else
		speed = (-RUNNER_SPEED);

	enemy->SetColliderTop(16);
	enemy->SetColliderBottom(-16);
	enemy->SetColliderLeft(-8);

	EnemyState::ResetState();
}

void RunnerFollowState::Update(double dt) {
	enemyData->enemy->SetVx(speed);
	m_Animation->Update(dt);
}
