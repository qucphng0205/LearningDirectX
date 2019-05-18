//OBSOLETE

//#include "KnifeRotateState.h"
//#include "Enemy.h"
//
//KnifeRotateState::KnifeRotateState(EnemyData *data) : EnemyState(data) {
//	auto textures = Textures::GetInstance();
//	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_KNIFE);
//	m_Animation = new Animation();
//	m_Animation->AddFramesA(texture, 1, 1, 4, 1, 4, KNIFE_FRAME * (1 / 60.0f));
//}
//
//KnifeRotateState::~KnifeRotateState() {
//	delete m_Animation;
//}
//
//void KnifeRotateState::ResetState() {
//
//	auto enemy = enemyData->enemy;
//
//	auto playerX = Camera::GetInstance()->GetPosition().x;
//	auto enemyX = enemy->GetPosition().x;
//
//	EnemyState::ResetState();
//}
//
//void KnifeRotateState::Update(double dt) {
//	m_Animation->Update(dt);
//}
