#pragma once
#include "Entity.h"
#include "MyHelper.h"

struct EarnedData {
	int score;
	Entity::EntityTag item;
	EarnedData() {
		score = 0;
		item = Entity::None;
	}
	EarnedData(int score) {
		this->score = score;
		item = Entity::None;
	}
	EarnedData(Entity::EntityTag item) {
		score = 0;
		this->item = item;
	}
};


class DataManager {
private:
	static int life;
	static int health;
	static int score;
	static int spiritPoint;
	static Entity::EntityTag item;
public:
	static int GetHealth();
	static void SetHealth(int hel);
	static int GetScore();
	static void SetScore(int scr);
	static void AddScore(int score);
	static int GetSpiritPoint();
	static void SetSpiritPoint(int point);
	static int GetLife();
	static void SetLife(int lif);
	static Entity::EntityTag GetItem();
	static void SetItem(Entity::EntityTag itm);
};