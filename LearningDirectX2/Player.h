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
		OnGround,
		Climbing
	};

	static Player *GetInstance();
	Player();
	~Player();
	void Update(double dt) override;
	void Render() override;
	void SetState(PlayerState::State name, int dummy = 0);
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0/60) override;
	BoxCollider GetRect();
	BoxCollider GetBigBound();
	BoxCollider GetBody();
	PlayerState::State GetState();
	float GetBigWidth() override;
	float GetBigHeight() override;
	float GetWidth() override;
	float GetHeight() override;
	void OnFalling();
	void SetColliderTop(int top);
	void SetColliderLeft(int left);
	void SetColliderBottom(int bottom);
	void SetColliderRight(int right);
	void SetMoveDirection(Entity::EntityDirection dir) override;
	void InjuredByOther(Entity *impactor);
	void OnImmortal();
	void OffImmortal();
	void CheckForUseItem();
	void ThrowShuriken();
	void ThrowBigShuriken();
	void ThrowFlames();
	virtual BoxCollider GetCollider();
	void HandleInput();
	Status status;

	bool isImmortal;
	bool checkGroundInFrame;
	float timeOnAir;
	float immortalTime;

	//check for immortal
	bool renderPreviousFrame;

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
		*useItemState,
		*injuredState;

	PlayerState::State currentState;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
private:
};