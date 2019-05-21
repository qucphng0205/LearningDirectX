#pragma once
#include "Tag.h"
#include "MyHelper.h"
#include "Textures.h"
#include "DataManager.h"

struct EarnedData {
	int score;
	Tag item;
	EarnedData() {
		score = 0;
		item = NONE;
	}
	EarnedData(int score) {
		this->score = score;
		item = NONE;
	}
	EarnedData(Tag item) {
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
	static Tag item;
	static float freezeTimeLeft;

	static void SetScore(int scr);
	static void SetHealth(int hel);
	static void SetSpiritPoint(int point);
	static void SetLife(int lif);
	static void SetItem(Tag itm);
public:
	static int GetHealth();
	static int GetScore();
	static int GetSpiritPoint();
	static bool IsFreezeTime();
	static void MinusFreezeTimeLeft(float time);
	static bool ConsumeSpiritPoint(int point);
	static int GetLife();
	static Tag GetItem();
	static void AddData(EarnedData data);
};