#include "ThrowerFollowState.h"
#include "Enemy.h"

ThrowerFollowState::ThrowerFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_THROWER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 1, 1, 2, 2, 2, THROWER_FOLLOW_FRAME * (1 / 60.0f));
}

ThrowerFollowState::~ThrowerFollowState() {
}

void ThrowerFollowState::ResetState() {

	auto enemy = enemyData->enemy;

	auto playerX = Camera::GetInstance()->GetPosition().x;
	auto enemyX = enemy->GetPosition().x; 

	if (playerX > enemyX)
		enemy->SetVx(THROWER_SPEED);
	else
		enemy->SetVx(-THROWER_SPEED);

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(10);
	enemy->SetColliderBottom(-21);
	enemy->SetColliderLeft(-8);

	srand(time(0));

	//rand from 0.3f to 4.0f
	my_PrecentTime = (float)(rand() % THROWER_ATTACK_RAND + 3) / 10;

	EnemyState::ResetState();
}

void ThrowerFollowState::Update(double dt) {
	m_Animation->Update(dt);
	if (m_Animation->GetPercentTime() >= my_PrecentTime)
		enemyData->enemy->SetState(Attack);
}
