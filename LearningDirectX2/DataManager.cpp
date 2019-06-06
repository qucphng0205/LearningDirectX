#include "DataManager.h"

int DataManager::health = 16;
int DataManager::life = 2;
int DataManager::score = 0;
int DataManager::spiritPoint = 0;
int DataManager::bossHealth = 16;
Tag DataManager::item = NONE;
float DataManager::freezeTimeLeft = 0;
bool DataManager::isBossDead = false;
int DataManager::unlockedStage = 0;

bool DataManager::isDeath = false;
int DataManager::currentStage = 0;
D3DXCOLOR DataManager::gameColor = D3DCOLOR_XRGB(255, 255, 255);

int DataManager::GetHealth() {
	return health;
}

void DataManager::InitPlayerHealth() {
	health = 16;
}

int DataManager::GetBossHealth() {
	return bossHealth;
}

void DataManager::SetBossReallyDead() {
	isBossDead = true;
}

bool DataManager::IsBossReallyDead() {
	return isBossDead;
}

void DataManager::SetPlayerDead() {
	if (life <= 0)
		currentStage = GAMEOVER_SCENE;
	else {
		life--;
		if (currentStage == 2)
			currentStage--;
	}
	isDeath = true;
}

void DataManager::SetPlayerAlive() {
	isDeath = false;
}

void DataManager::InitBossHealth() {
	bossHealth = 16;
}

void DataManager::MinusBossHealth() {
	if (bossHealth > 0)
		bossHealth--;
}

void DataManager::SetHealth(int hel) {
	DataManager::health = MyHelper::Clamp(hel, 1, 16);
}

int DataManager::GetScore() {
	return score;
}

void DataManager::SetScore(int scr) {
	score = MyHelper::Clamp(scr, 0, 999999);
}

int DataManager::GetSpiritPoint() {
	return spiritPoint;
}

bool DataManager::MinusHealth(int hea) {
	health -= hea;
	if (health < 0)
		health = 0;
	return (isDeath);
}

bool DataManager::MinusHealth(Tag impactor) {
	switch (impactor) {
	case BASAQUER:
	case DART:
	case BIGBULLET:
		return MinusHealth(2);
	case EAGLE:
		return MinusHealth(3);
		break;
	default:
		return MinusHealth(1);
	}
}

bool DataManager::IsFreezeTime() {
	return (freezeTimeLeft > 0);
}

void DataManager::MinusFreezeTimeLeft(float time) {
	if (freezeTimeLeft > 0)
		freezeTimeLeft = MyHelper::Clamp(freezeTimeLeft - time, 0, 5);

}

bool DataManager::ConsumeSpiritPoint(int point) {
	if (spiritPoint < point)
		return false;
	spiritPoint -= point;
	return true;
}

void DataManager::SetSpiritPoint(int point) {
	spiritPoint = MyHelper::Clamp(point, 0, 99);
}

int DataManager::GetLife() {
	return life;
}

void DataManager::SetLife(int lif) {
	life = MyHelper::Clamp(lif, 0, 99);
}

Tag DataManager::GetItem() {
	return item;
}

void DataManager::AddData(EarnedData data) {
	SetScore(score + data.score);
	if (data.item != NONE) {
		switch (data.item) {
		case (SCORES500):
			SetScore(score + 500);
			break;
		case (SCORES1000):
			SetScore(score + 1000);
			break;
		case (SPIRITPOINTS5):
			SetSpiritPoint(spiritPoint + 5);
			break;
		case (SPIRITPOINTS10):
			SetSpiritPoint(spiritPoint + 10);
			break;
		case (HEALTH):
			SetHealth(health + 6);
			break;
		case (TIMEFREEZE):
			freezeTimeLeft = 5.0f;
			break;
		case (THROWINGSTAR):
		case (WINDMILLSTAR):
		case (FLAMES):
			SetItem(data.item);
			break;
		default:
			break;
		}
	}
}

bool DataManager::IsDeath() {
	return isDeath;
}

int DataManager::GetCurrentStage() {
	return currentStage;
}

void DataManager::SetCurrentStage(int stage) {
	unlockedStage = max(stage, unlockedStage);
	currentStage = stage;
}

void DataManager::SetGameColor(D3DXCOLOR color) {
	gameColor = color;
}

D3DXCOLOR DataManager::GetGameColor() {
	return gameColor;
}

void DataManager::Reset() {
	DataManager::health = 16;
	DataManager::life = 2;
	DataManager::score = 0;
	DataManager::spiritPoint = 0;
	DataManager::bossHealth = 16;
	DataManager::item = NONE;
	DataManager::freezeTimeLeft = 0;
	DataManager::isBossDead = false;
	DataManager::isDeath = false;
	DataManager::currentStage = 0;
	DataManager::unlockedStage = 0;
	DataManager::gameColor = D3DCOLOR_XRGB(255, 255, 255);
}

//after transition scene
void DataManager::HandleGameOver() {
	DataManager::health = 16;
	DataManager::life = 2;
	DataManager::score = 0;
	DataManager::spiritPoint = 0;
	//DataManager::bossHealth = 16;
	DataManager::item = NONE;
	DataManager::freezeTimeLeft = 0;
	DataManager::isBossDead = false;
	DataManager::isDeath = false;
	DataManager::gameColor = D3DCOLOR_XRGB(255, 255, 255);
	//IF BOSS_SCENE
	if (currentStage == 3)
		currentStage--;
}

//after transition scene and check life
void DataManager::HandleReload() {
	DataManager::health = 16;
	//DataManager::life--; already minus bro
	//DataManager::score = 0;
	DataManager::spiritPoint /= 2;
	//DataManager::bossHealth = 16;
	DataManager::item = NONE;
	DataManager::freezeTimeLeft = 0;
	DataManager::isBossDead = false;
	DataManager::isDeath = false;
	DataManager::gameColor = D3DCOLOR_XRGB(255, 255, 255);
	//IF BOSS_SCENE
}

void DataManager::SetItem(Tag itm) {
	item = itm;
}
