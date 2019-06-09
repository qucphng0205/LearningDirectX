#include "GameOver.h"

GameOver::GameOver() {
	text1 = "GAME OVER";
	SetRect(&zone1, 0, 0, 256, 224);
}

GameOver::~GameOver() {
}

void GameOver::Render() {
	Graphic *g = Graphic::GetInstance();
	Graphic::GetInstance()->DrawCustomZone(zone1, text1);
}

void GameOver::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
	if (input->GetKey(DIK_RETURN)) {
		int stage = DataManager::GetPreviousStage();
		stage = MyHelper::Clamp(stage, INTRO_SCENE + 1, BOSS_STAGE - 1);
		DataManager::Reset();
		DataManager::SetCurrentStage(stage);
	}
}

void GameOver::Update(double dt) {
	ProcessInput();
}

int GameOver::GetSceneID() {
	return 5;
}