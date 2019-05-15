#include "Soldier.h"

Soldier::Soldier() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
		textures->Add(TEX_SOLDIER, "Resources/Sprites/soldierspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	soldierFollowState = new SoldierFollowState(enemyData);
	soldierAttackState = new SoldierAttackState(enemyData);
	//Set tag
	tag = Entity::Soldier;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_SOLDIER)->GetLevelDesc(0, &desc);
	width = desc.Width / 2.0;
	height = desc.Height / 2.0;
}

Soldier::~Soldier() {
	delete soldierFollowState;
	delete soldierAttackState;
	soldierFollowState = NULL;
	soldierAttackState = NULL;
}

void Soldier::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	Enemy::OnCollision(impactor, side, collisionTime);
	if (impactor->GetType() == Entity::StaticType && side == Bottom)
		onGround = true;
}

void Soldier::Update(double dt) {
	SetMoveDirection(Camera::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
	if (!onGround)
		AddVy(-CAT_GRAVITY);
	onGround = false;
}

void Soldier::SetColliderTop(int top) {
	collider.top = top;
}

void Soldier::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Soldier::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Soldier::SetColliderRight(int right) {
	collider.right = right;
}

void Soldier::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = soldierFollowState;
	if (state == EnemyState::Attack)
		enemyData->state = soldierAttackState;
	enemyData->state->ResetState();
}

BoxCollider Soldier::GetCollider() {
	return collider;
}

void Soldier::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}

void Soldier::SpawnBullet() {
	D3DXVECTOR3 position = this->position;
	position.y += OFFSET_TO_BULLET;
	if (!ObjectPooling::GetInstance()->Instantiate(BULLET_POOL_INDEX, position))
		SetState(EnemyState::Follow);
}
