#include "EndGame.h"

EndGame::EndGame() {
}

EndGame::~EndGame() {
}

void EndGame::Render() {
	Graphic *g = Graphic::GetInstance();
	//Graphic::GetInstance()->DrawString();
}

void EndGame::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
}

void EndGame::Update(double dt) {
}

int EndGame::GetSceneID() {
	return 4;
}