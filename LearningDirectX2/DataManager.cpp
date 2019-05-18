#include "DataManager.h"

int DataManager::health = 16;
int DataManager::life = 2;
int DataManager::score = 0;
int DataManager::spiritPoint = 0;
Tag DataManager::item = NONE;

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
