#include "DataManager.h"

int DataManager::health = 16;
int DataManager::life = 2;
int DataManager::score = 0;
int DataManager::spiritPoint = 0;
Entity::EntityTag DataManager::item = Entity::None;

int DataManager::GetHealth() {
	return health;
}

void DataManager::SetHealth(int hel) {
	DataManager::health = 0;// = MyHelper::Clamp(hel, 1, 16);
}

int DataManager::GetScore() {
	return score;
}

void DataManager::SetScore(int scr) {
	score = MyHelper::Clamp(scr, 0, 999999);
}

void DataManager::AddScore(int sco) {
	score += sco;
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

Entity::EntityTag DataManager::GetItem() {
	return item;
}

void DataManager::SetItem(Entity::EntityTag itm) {
	item = itm;
}
