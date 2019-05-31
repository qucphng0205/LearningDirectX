#include "BasaquerJumpingState.h"
#include "Enemy.h"

BasaquerJumpingState::BasaquerJumpingState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_BASAQUER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 2, 2, 1, 2, 1, RUNNER_FRAME * (1 / 60.0f));
}

BasaquerJumpingState::~BasaquerJumpingState() {
}

void BasaquerJumpingState::ResetState() {

	auto enemy = enemyData->enemy;
	auto enemyX = enemy->GetPosition().x;
	float playerX = 0;

	if (Player::GetInstance() != NULL)
		playerX = Player::GetInstance()->GetPosition().x;

	enemy->SetColliderTop(27);
	enemy->SetColliderBottom(-27);
	enemy->SetColliderLeft(-19);
	enemy->SetColliderRight(9);

	if (enemyX > 128)
		vx = (-170);
	else
		vx = (170);

	enemyData->enemy->SetMoveDirection(playerX < enemyX ? Entity::RightToLeft : Entity::LeftToRight);

	timeState = 0;

	EnemyState::ResetState();
}

void BasaquerJumpingState::Update(double dt) {

	if (timeState > 1)
		timeState = 1;

	int vy = MyHelper::Lerp(350, -350, timeState);

	enemyData->enemy->SetVelocity(D3DXVECTOR2(vx, vy));

	m_Animation->Update(dt);

	timeState += dt;
}

void BasaquerJumpingState::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTIme, double dt) {
}
