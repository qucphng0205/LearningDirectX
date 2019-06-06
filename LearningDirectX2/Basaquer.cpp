#include "Basaquer.h"

Basaquer::Basaquer() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_BASAQUER, "Resources/Sprites/basaquerspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	basaquerIdleState = new BasaquerIdleState(enemyData);
	basaquerJumpingState = new BasaquerJumpingState(enemyData);
	//Set Tag
	Tag = BASAQUER;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_BASAQUER)->GetLevelDesc(0, &desc);
	width = desc.Width;
	height = desc.Height / 2;
	point = 200;
	jumpTimes = 2;
}

Basaquer::~Basaquer() {
	delete basaquerIdleState;
	delete basaquerJumpingState;
	basaquerIdleState = NULL;
	basaquerJumpingState = NULL;
}

void Basaquer::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime, double dt) {
	if (isDead)
		return;

	if (impactor->GetType() == Layer::StaticType)
		if (side == Bottom) {
			onGround = true;
			if (velocity.y < 0) {
				SetVy(velocity.y * dt * collisionTime);
				if (state != EnemyState::Follow)
					SetState(EnemyState::Follow);
			}
		}
		else if ((side == Left && velocity.x < 0) || (side == Right && velocity.x > 0)) {
			SetVx(velocity.x * collisionTime);
		}
	GetRect();
}

void Basaquer::Update(double dt) {
	if (isDead) {
		explosionTime += dt;
		if (explosionTime >= BOSS_DEATH_DELAY + 0.0f) {
			SetActive(false);
			DataManager::SetBossReallyDead();
		}
	} else 
	Enemy::Update(dt);
}

void Basaquer::SetColliderTop(int top) {
	collider.top = top;
}

void Basaquer::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Basaquer::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Basaquer::SetColliderRight(int right) {
	collider.right = right;
}

void Basaquer::SetVelocity(D3DXVECTOR2 vel) {
	velocity = vel;
}

void Basaquer::SetVx(float vx) {
	velocity.x = vx;
}

void Basaquer::SetVy(float vy) {
	velocity.y = vy;
}

void Basaquer::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = basaquerIdleState;
	if (state == EnemyState::Attack) {
		enemyData->state = basaquerJumpingState;
		jumpTimes = (jumpTimes + 1) % 11;
		SpawnDarts();
	}
	this->state = state;
	enemyData->state->ResetState();
}

BoxCollider Basaquer::GetCollider() {
	return collider;
}

void Basaquer::SetActive(bool active) {

	if (active == isActive)
		return;

	if (active)
		Spawn();
	else
		MakeInactive();
}

void Basaquer::Spawn() {
	isDead = false;
	DataManager::InitBossHealth();
	SetState(EnemyState::Attack);
	Enemy::Spawn();
}

EarnedData Basaquer::OnDestroy() {

	DataManager::MinusBossHealth();
	if (DataManager::GetBossHealth() > 0 || isDead)
		return EarnedData(0);

	explosionTime = 0;
	isDead = true;
	gnhpSound::GetInstance()->PlayFX(SOUND_BASAQUEREXPLOSION);
	//for collide
	type = Layer::NoneType;

	//6 / (12/60) = 30 percent times
	//*2 becauz 2 frames
	effect = new EffectChain(new BigExplosion(position, (float)BOSS_DEATH_DELAY / (BIGEXPLOSION_FRAME * 2 /60.0)));
	Grid::GetInstance()->AddEffect(effect);
	return EarnedData(point);
}

void Basaquer::SpawnDarts() {
	ObjectPooling *pool = ObjectPooling::GetInstance();

	if (pool->CheckQuantity(DARTS_POOL_INDEX) < 3)
		return;

	//int jump2 = jumpTimes + 1;
	//if (jump2 != 3 && jump2 != 6 && jump2 == 10)
	//	return;

	if ((jumpTimes + 1) % 3 != 0) 
		return;

	//--DEBUG WITH ZERO
	for (int i = 0; i < 3; i++)
		ObjectPooling::GetInstance()->Instantiate(DARTS_POOL_INDEX, position);
}
