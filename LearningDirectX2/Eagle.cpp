#include "Eagle.h"
#include "Debug.h"

Eagle::Eagle() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_EAGLE, "Resources/Sprites/eaglespritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	eagleFollowState = new EagleFollowState(enemyData);
	//Set Tag
	Tag = EAGLE;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_EAGLE)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
	point = 300;
}

Eagle::~Eagle() {
	delete eagleFollowState;
	eagleFollowState = NULL;
}

void Eagle::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
}

#include "Player.h"
int i = 0;
void Eagle::Update(double dt) {
	SetMoveDirection(Camera::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);

	Enemy::Update(dt);

	D3DXVECTOR3 target = Player::GetInstance()->GetPosition();
	target.y -= 15;
	D3DXVECTOR2 dir = D3DXVECTOR2(target - position);
	D3DXVec2Normalize(&dir, &dir);
	i++;
	dir.x *= 5.5f;
	dir.y *= 5.5f;

	//--DEBUG
	if (i == 110)
		i = i;
	if (i == 60)
		i = 60;

	AddVelocity(dir);

	//velocity.x = MyHelper::Clamp(velocity.x, -200.0f, 200.0f);
	velocity.y = MyHelper::Clamp(velocity.y, -80.0f, 80.0f);
}

void Eagle::SetColliderTop(int top) {
	collider.top = top;
}

void Eagle::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Eagle::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Eagle::SetColliderRight(int right) {
	collider.right = right;
}

void Eagle::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = eagleFollowState;
	enemyData->state->ResetState();
}

BoxCollider Eagle::GetCollider() {
	return collider;
}

void Eagle::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
	i = 0;
}
