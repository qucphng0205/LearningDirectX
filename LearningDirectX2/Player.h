#pragma once
#include "KeyBoard.h"
#include "Entity.h"
#include "PlayerData.h"
#include "PlayerState.h"

class Player : public Entity {
public:

	enum Status {
		Jumping,
		Falling,
		OnGround
	};

	static Player *GetInstance();
	Player();
	~Player();
	virtual void Update(double dt);
	virtual void Render();
	void SetState(PlayerState::State name, int dummy = 0);
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	BoxCollider GetRect();
	BoxCollider GetBigBound();
	PlayerState::State GetState();
	virtual float GetBigWidth();
	virtual float GetBigHeight();
	virtual float GetWidth();
	virtual float GetHeight();
	virtual void OnFalling();
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetMoveDirection(Entity::EntityDirection dir);
	virtual BoxCollider GetCollider();
	void HandleInput();
	Status status;

	bool isImmortal;
	bool checkGroundInFrame;
	float timeOnAir;

protected:
	static Player *instance;
	PlayerData *playerData;
	PlayerState
		*idleState,
		*runningState,
		*slashState,
		*crouchState,
		*jumpState,
		*crouchSlashState,
		*climbState,
		*useItemState;
	PlayerState::State currentState;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
};