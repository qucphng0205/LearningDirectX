#pragma once
//-------------------------------TEXTURE INDEX-----------------------
#define TEX_STAGE31 0
#define TEX_stage32 1
#define TEX_stage33 2
#define TEX_PLAYER 4
#define TEX_SPARTA 5
#define TEX_CAT 6
#define TEX_THROWER 7
#define TEX_EAGLE 8
#define TEX_SOLDIER 9
#define TEX_HOLDER 10
#define TEX_ITEM 11
#define TEX_KNIFE 12
#define TEX_BULLET 13
#define TEX_EXPLOSION 14
#define TEX_FLAMES 15
#define TEX_THROWINGSTAR 16
#define TEX_WINDMILLSTAR 17
#define TEX_SHURIKEN 18
#define TEX_BIGSHURIKEN 19
#define TEX_FLAMESPROJECTILE 20
#define TEX_GUNNER 21
#define TEX_RUNNER 22
#define TEX_BIGBULLET 23

//---------------------------------ANIMATION FRAME----------------------
#define PLAYER_SLASH_FRAME 7
#define PLAYER_RUNNING_FRAME 4
#define PLAYER_JUMPING_FRAME 8
#define SPARTA_FRAME 15
#define CAT_FRAME 15
#define THROWER_FOLLOW_FRAME 12
#define THROWER_ATTACK_FRAME 12
#define EAGLE_FRAME 15
#define SOLDIER_FOLLOW_FRAME 14
#define SOLDIER_ATTACK_FRAME 2
#define EXPLOSION_FRAME 2
//frame loops cua animation attack
#define SOLDIER_ATTACK_LOOP_FRAMES 30
//frame spawn bullet
#define SOLDIER_ATTACK_SHOOT_FRAMES 10
#define SOLDIER_FOLLOW_PERCENTTIME 2.5f
#define GUNNER_FOLLOW_FRAME 60
#define GUNNER_ATTACK_FRAME 4
#define RUNNER_FRAME 12

#define HOLDER_FRAME 10
#define KNIFE_FRAME 8
#define SHURIKEN_FRAME 3
#define BIGSHURIKEN_FRAME 3
#define FLAMES_FRAME 1

//-------------------------------------- GRID -------------------------
#define GRID_ROW 4
#define GRID_COLUMN 40

//----------------------------PLAYER SPEED AND FORCE-------------------
#define PLAYER_RUN_VELOCITY 90
//1 mean 1s 
//2 mean 0.5s
//0.5 mean 2s
//1 / x = s
#define JUMP_TO_GROUND_SPEED 1.5
#define PLAYER_JUMP_FORCE 270

#define PLAYER_INJURED_FORCE_X 60
#define PLAYER_INJURED_FORCE_Y 110
#define PLAYER_INJURED_SPEED 2
#define PLAYER_IMMORTAL_TIME 0.4

#define PLAYER_CLIM_SPEED 70

//----------------------------BOT CONFIG-------------------------------
#define SPARTA_SPEED 30.0f
#define THROWER_SPEED 20.0f
//PERCENT TIME OF FOLLOW (/ 10)
#define THOWER_ATTACK_MAX 40
#define THROWER_ATTACK_MIN 3
#define THROWER_ATTACK_RAND THOWER_ATTACK_MAX - THROWER_ATTACK_MIN + 1
#define EAGLE_ACCELERATE 12
#define CAT_SPEED 110
#define CAT_JUMP_VELOCITY 100
#define CAT_GRAVITY 10
#define SOLDIER_SPEED 30
#define KNIFE_THROW_FORCE_Y 120
#define KNIFE_THROW_FORCE_MIN_X 30
#define KNIFE_THROW_FORCE_MAX_X 120
#define KNIFE_DRAG_FORCE 10.0f
#define BULLET_FORCE 110
#define BIGBULLET_FORCE 140
#define OFFSET_TO_BULLET 6
#define BIG_BULLET_FORCE 110
#define SHURIKEN_VELOCITY 190
#define BIGSHURIKEN_VELOCITY 190
#define FLAMES_VELOCITY_X 190
#define FLAMES_VELOCITY_Y_0 30
#define FLAMES_VELOCITY_Y_1 60
#define FLAMES_VELOCITY_Y_2 90
#define RUNNER_SPEED 110

#define PLAYER_OFFSET_GROUND PLAYER_JUMP_FORCE * 1.0 / 60
#define ENEMY_OFFSET_BORDER 2

//-----------------------OBJECTPOOLING-------------------

//first
#define KNIFE_QUANTITY 3
#define KNIFE_POOL_INDEX 0
#define KNIFE_SPEED 1
//second
#define BULLET_QUANTITY 9
#define BULLET_POOL_INDEX 1
//third
//spirit points
#define SHURIKEN_COST 3
#define SHURIKEN_QUANTITY 6
#define SHURIKEN_POOL_INDEX 2
//fourth
//spirit points
#define BIGSHURIKEN_COST 5
#define BIGSHURIKEN_QUANTITY 1
#define BIGSHURIKEN_POOL_INDEX 3
//five
//spirit points
#define FLAMES_COST 5
#define FLAMES_QUANTITY 3
#define FLAMES_POOL_INDEX 4
//six
#define BIGBULLET_POOL_INDEX 5
#define BIGBULLET_QUANTITY 4

#define LADDER_OFFSET 20

//-----------------------------------------------SCENE
#define SCENE_TIME_TRANSITION 3
