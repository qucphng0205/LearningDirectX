#include "GameOver.h"

GameOver::GameOver() {
}

GameOver::~GameOver() {
}

void GameOver::Render() {
	Graphic *g = Graphic::GetInstance();
	//Graphic::GetInstance()->DrawString();
}

void GameOver::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
}

void GameOver::Update(double dt) {
}

int GameOver::GetSceneID() {
	return 4;
}