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
	auto impactorRect = impactor->GetRect();
	auto myRect = GetRect();
	auto enemyVel = enemyData->enemy->GetVelocity();

	if (impactor->GetType() == Layer::StaticType && impactor->GetTag() != Tag::THINSURFACE) {
		if (side == Entity::Bottom) {

			if ((MyHelper::Distance(myRect.left, impactorRect.left) < ENEMY_OFFSET_BORDER && velocity.x < 0) || (MyHelper::Distance(myRect.right, impactorRect.right) < ENEMY_OFFSET_BORDER && velocity.x > 0) || (impactorRect.left > myRect.left && impactorRect.left < myRect.right && velocity.x < 0) || (impactorRect.right > myRect.left && impactorRect.right < myRect.right && velocity.x > 0))
				if (impactor->GetTag() != LADDER)
					SetVy(210);//RUNNER_JUMP_FORCE);
			if (velocity.y < 0)
				velocity.y *= collisionTime * dt;
		}
		else if ((side == Entity::Left && enemyVel.x < 0) || (side == Entity::Right && enemyVel.x > 0)){
			velocity.x *= collisionTime * dt;
		}
	}
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
