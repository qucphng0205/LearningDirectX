#include "IntroScene.h"

IntroScene::IntroScene() {
	auto textures = Textures::GetInstance();
	textures->Add(TEX_INTRO, "Resources/Sprites/introspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	animation = new Animation();
	animation->AddFramesA(textures->Get(TEX_INTRO), 1, 1, 2, 1, 2, 10 * 1.0 / 60);
	zone1 = RECT();
	SetRect(&zone1, 0, 0, 256, 50);
	SetRect(&zone2, 0, 190, 256, 224);
	SetRect(&zone3, 0, 160, 256, 190);
	text1 = "Ninja Gaiden - REMAKE";
	text2 = "Mentor Nguyen Vinh Kha\nRemade by Le Quoc Phuong";
	text3 = "Press enter to play";
	showText3 = false;

	DataManager::Reset();
}

IntroScene::~IntroScene() {
	delete animation;
	animation = NULL;
}

void IntroScene::Render() {
	animation->NormalRender(D3DXVECTOR3(0, 0, 0));
	Graphic *g = Graphic::GetInstance();
	g->DrawCustomZone(zone1, text1);
	g->DrawCustomZone(zone2, animtext2);
	if (showText3 && animtext2 == text2) {
		g->DrawCustomZone(zone3, text3);
	}
}

void IntroScene::ProcessInput() {
	if (KeyBoard::GetInstance()->GetKeyDown(DIK_RETURN))
		if (animtext2 == text2)
			DataManager::SetCurrentStage(DataManager::GetCurrentStage() + 1);
		else {
			animtext2 = text2;
		}
		
}

void IntroScene::Update(double dt) {
	ProcessInput();
	animation->Update(dt);
	timeToText += dt;
	timeToShow += dt;
	if (timeToText > 0.1f) {
		if (text2.length() > animtext2.length())
			animtext2 = text2.substr(0, animtext2.length() + 1);
		timeToText = 0;
	}
	if (timeToShow > 0.4f) {
		timeToShow = 0;
		showText3 = !showText3;
	}

}

int IntroScene::GetSceneID() {
	return 0;
}