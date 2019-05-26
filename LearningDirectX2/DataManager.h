#pragma once
#include "Tag.h"
#include "MyHelper.h"

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
#pragma region runtime data

	static int life;
	static int health;
	static int score;
	static int spiritPoint;
	static Tag item;
	static float freezeTimeLeft;

#pragma endregion
#pragma region loading data
	static bool isDeath;
	static int currentStage;
	//for scene-transition
	static D3DXCOLOR gameColor;
#pragma endregion

	static void SetScore(int scr);
	static void SetHealth(int hel);
	static void SetSpiritPoint(int point);
	static void SetLife(int lif);
	static void SetItem(Tag itm);
public:
	
#pragma region Run-time data function
	static int GetHealth();
	static int GetScore();
	static int GetSpiritPoint();
	static bool MinusHealth();
	static bool IsFreezeTime();
	static void MinusFreezeTimeLeft(float time);
	static bool ConsumeSpiritPoint(int point);
	static int GetLife();
	static Tag GetItem();
	static void AddData(EarnedData data);
#pragma endregion

#pragma region Loading data function
	static bool IsDeath();
	static int GetCurrentStage();
	static void SetGameColor(D3DXCOLOR color);
	static D3DXCOLOR GetGameColor();
#pragma endregion

	
};