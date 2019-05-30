#pragma once
//class Tag {
//public:
enum Tag {
	GROUND,
	SPARTA,
	CAT,
	THROWER,
	EAGLE,
	SOLDIER,
	SPIRITPOINTS5,
	SPIRITPOINTS10,
	SCORES500,
	SCORES1000,
	TIMEFREEZE,
	HEALTH,
	THROWINGSTAR,
	WINDMILLSTAR,
	FLAMES,
	GUNNER,
	RUNNER,
	LADDER,
	THINSURFACE,
	BASAQUER,
	EPROJECTILE,
	PPROJECTILE,
	PLAYER,
	NONE
};

enum Layer {
	StaticType,
	PlayerType,
	EnemyType,
	//Enemy projectile
	EProjectileType,
	//Player projectile
	PProjectileType,
	//katana + pprojectile tac dong duoc
	ItemHolderType,
	//katana + pprojectile ko tac dong dc
	ItemAvailableType,
	NoneType
};
//}