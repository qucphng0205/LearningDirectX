#pragma once

#pragma region TEXTURE INDEX

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
#define TEX_BASAQUER 24
#define TEX_DART 25
#define TEX_BIGEXPLOSION 26
#define TEX_BAT 27
#define TEX_INTRO 28

#pragma endregion

#pragma region PLAYER

#pragma region ANIMATION FRAME

#define PLAYER_SLASH_FRAME 7
#define PLAYER_RUNNING_FRAME 4
#define PLAYER_JUMPING_FRAME 4

#pragma endregion

#pragma region SPEED AND FORCE
#define PLAYER_RUN_VELOCITY 90
#define PLAYER_JUMP_FORCE 270

//1 mean 1s 
//2 mean 0.5s
//0.5 mean 2s
//1 / x = s
#define JUMP_TO_GROUND_SPEED 1.5

#define PLAYER_INJURED_FORCE_X 60
#define PLAYER_INJURED_FORCE_Y 110
#define PLAYER_INJURED_SPEED 2
#define PLAYER_IMMORTAL_TIME 0.4

#define PLAYER_CLIM_SPEED 70
#pragma endregion


#pragma endregion

#pragma region ELSE FRAME

#pragma region ENEMY ANIMATION FRAME

#define SPARTA_FRAME 15
#define CAT_FRAME 15
#define THROWER_FOLLOW_FRAME 12
#define THROWER_ATTACK_FRAME 12
#define EAGLE_FRAME 15
#define SOLDIER_FOLLOW_FRAME 14
#define SOLDIER_ATTACK_FRAME 2
#define EXPLOSION_FRAME 2
#define BIGEXPLOSION_FRAME 5
//frame loops cua animation attack
#define SOLDIER_ATTACK_LOOP_FRAMES 30
//frame spawn bullet
#define SOLDIER_ATTACK_SHOOT_FRAMES 10
#define SOLDIER_FOLLOW_PERCENTTIME 2.5f
#define GUNNER_FOLLOW_FRAME 60
#define GUNNER_ATTACK_FRAME 4
#define RUNNER_FRAME 12
#define BAT_FRAME 10
#define BASAQUER_IDLE_FRAME 30

#pragma endregion

#pragma region WEAPON AND ITEM FRAME

#define HOLDER_FRAME 10
#define KNIFE_FRAME 8
#define SHURIKEN_FRAME 3
#define BIGSHURIKEN_FRAME 3
#define FLAMES_FRAME 1

#pragma endregion 

#pragma endregion

#pragma region GRID
#define GRID_ROW_STAGE31 4
#define GRID_COLUMN_STAGE31 40
#define GRID_ROW_STAGE32 4
#define GRID_COLUMN_STAGE32 60
#define GRID_ROW_STAGE33 1
#define GRID_COLUMN_STAGE33 1
#pragma endregion

#pragma region CONFIG

#pragma region SPARTA
#define SPARTA_SPEED 30.0f
#pragma endregion

#pragma region THROWER
#define THROWER_SPEED 20.0f
//PERCENT TIME OF FOLLOW (/ 10)
#define THOWER_ATTACK_MAX 40
#define THROWER_ATTACK_MIN 3
#define THROWER_ATTACK_RAND THOWER_ATTACK_MAX - THROWER_ATTACK_MIN + 1
#pragma endregion

#pragma region EAGLE AND CAT
#define EAGLE_ACCELERATE_X 5
#define CAT_SPEED 110
#define CAT_JUMP_VELOCITY 100

#define CAT_GRAVITY 10
#pragma endregion

#pragma region SOLDIER, RUNNER
#define SOLDIER_SPEED 30
#define RUNNER_SPEED 110
#pragma endregion

#pragma region KNIFE
#define KNIFE_THROW_FORCE_Y 120
#define KNIFE_THROW_FORCE_MIN_X 30
#define KNIFE_THROW_FORCE_MAX_X 120

#define KNIFE_DRAG_FORCE 10.0f
#pragma endregion

#pragma region BULLET, BIGBULLET
#define BULLET_FORCE 110
#define BIGBULLET_FORCE 140
#define OFFSET_TO_BULLET 6
#define BIG_BULLET_FORCE 110
#pragma endregion

#pragma region FLAMES
#define FLAMES_VELOCITY_X 190
#define FLAMES_VELOCITY_Y_0 120
#define FLAMES_VELOCITY_Y_1 240
#define FLAMES_VELOCITY_Y_2 360
#pragma endregion

#pragma region SHURIKEN, BIGSHURIKEN
#define SHURIKEN_VELOCITY 190
#define BIGSHURIKEN_VELOCITY 190
#pragma endregion


#pragma endregion

#pragma region Object Pooling

#pragma region KNIFE
#define KNIFE_QUANTITY 3
#define KNIFE_POOL_INDEX 0
#define KNIFE_SPEED 1
#pragma endregion

#pragma region BULLET
#define BULLET_QUANTITY 9
#define BULLET_POOL_INDEX 1
#pragma endregion

#pragma region SHURIKEN
#define SHURIKEN_COST 3
#define SHURIKEN_QUANTITY 6
#define SHURIKEN_POOL_INDEX 2
#pragma endregion

#pragma region BIGSHURIKEN
#define BIGSHURIKEN_COST 5
#define BIGSHURIKEN_QUANTITY 1
#define BIGSHURIKEN_POOL_INDEX 3
#pragma endregion

#pragma region FLAMES
#define FLAMES_COST 5
#define FLAMES_QUANTITY 3
#define FLAMES_POOL_INDEX 4
#pragma endregion

#pragma region BIGBULLET
#define BIGBULLET_POOL_INDEX 5
#define BIGBULLET_QUANTITY 4

#pragma endregion

#pragma region DARTS
#define DARTS_QUANTITY 3
#define DARTS_POOL_INDEX 6
#pragma endregion

#pragma endregion

#pragma region OFFSET
#define LADDER_OFFSET 20
#define PLAYER_OFFSET_GROUND PLAYER_JUMP_FORCE * 1.0 / 60
#define ENEMY_OFFSET_BORDER 2
#pragma endregion

#pragma region SCENE
#define SCENE_TIME_TRANSITION 4
#define BOSS_DEATH_DELAY 4
#define PLAYER_DEATH_DELAY 4
#define GAMEOVER_SCENE 5
#define BOSS_STAGE 3
#define ENDGAME_SCENE 4
#define INTRO_SCENE 0
#pragma endregion

#pragma region SOUND INDEX

#define SOUND_MUSIC31 0
#define SOUND_MUSIC32 1
#define SOUND_MUSIC33 2
#define SOUND_GAMEOVER 3
#define SOUND_SLASH 4
#define SOUND_JUMP 5
#define SOUND_INJURED 6
#define SOUND_EATITEM 7
#define SOUND_DAMAGE 8
#define SOUND_BIGBULLET 9
#define SOUND_BASAQUER 10
#define SOUND_BULLET 11
#define SOUND_EARN 12
#define SOUND_BASAQUEREXPLOSION 13
#define SOUND_THROWFLAMES 14
#define SOUND_THROWSHURIKEN 15
#define SOUND_THROWBIGSHURIKEN 16
#define SOUND_THEME 17

#pragma endregion

#define DOWN_ARROW DIK_S
#define UP_ARROW DIK_W
#define LEFT_ARROW DIK_A
#define RIGHT_ARROW DIK_D
#define SLASH_BUTTON DIK_G
#define JUMP_BUTTON DIK_H
