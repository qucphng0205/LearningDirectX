#include "DataManager.h"

int DataManager::health = 16;
int DataManager::life = 2;
int DataManager::score = 0;
int DataManager::spiritPoint = 0;
Tag DataManager::item = NONE;
float DataManager::freezeTimeLeft = 0;

bool DataManager::isDeath = false;
int DataManager::currentStage = 0;

int DataManager::GetHealth() {
	return health;
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

bool DataManager::MinusHealth() {
	health--;
	isDeath = (health <= 0);
	return (isDeath);
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
	lif = MyHelper::Clamp(life, 0, 99);
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

void DataManager::SetItem(Tag itm) {
	item = itm;
}
