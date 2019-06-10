#include "EndGame.h"

EndGame::EndGame() {
	zone1Box = BoxCollider(0, 0, 224, 256);
	text1 = "Ninja Gaiden Remake\n\nC++, DirectX, Win32\n\nMentor Nguyen Vinh Kha\n\n\n Remade by Le Quoc Phuong\n\nProject\nStage 3-1\nStage 3-2\nBoss Basaquer (Stage 3-3)";
	speed = 20.0f;
}

EndGame::~EndGame() {
}

void EndGame::Render() {
	Graphic *g = Graphic::GetInstance();
	Graphic::GetInstance()->DrawCustomZone(MyHelper::BoxColliderToRect(zone1Box), text1);
}

void EndGame::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
	if (input->GetKeyDown(DIK_RETURN)) {
		DataManager::SetCurrentStage(INTRO_SCENE);
	}
}

void EndGame::Update(double dt) {
	ProcessInput();
	//ruom ra time :v
	zone1Box.top -= dt * speed;
	zone1Box.bottom = zone1Box.top + 224;

	if (zone1Box.bottom < 0) {
		zone1Box.top = 224;
		zone1Box.bottom = zone1Box.top + 224;
	}
}

int EndGame::GetSceneID() {
	return ENDGAME_SCENE;
}