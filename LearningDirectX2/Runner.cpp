#include "Runner.h"

Runner::Runner() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_RUNNER, "Resources/Sprites/runnerspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	runnerFollowState = new RunnerFollowState(enemyData);
	//Set Tag
	Tag = RUNNER;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_RUNNER)->GetLevelDesc(0, &desc);
	width = desc.Width / 2;
	height = desc.Height;
	point = 300;
}

Runner::~Runner() {
	delete runnerFollowState;
	runnerFollowState = NULL;
}

void Runner::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	Enemy::OnCollision(impactor, side, collisionTime);
	if (impactor->GetType() == Layer::StaticType && side == Bottom)
		onGround = true;
}

void Runner::Update(double dt) {
	Enemy::Update(dt);
	if (!onGround)
		AddVy(-CAT_GRAVITY);
	onGround = false;
}

void Runner::SetColliderTop(int top) {
	collider.top = top;
}

void Runner::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Runner::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Runner::SetColliderRight(int right) {
	collider.right = right;
}

void Runner::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = runnerFollowState;
	enemyData->state->ResetState();
}

BoxCollider Runner::GetCollider() {
	return collider;
}

void Runner::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
