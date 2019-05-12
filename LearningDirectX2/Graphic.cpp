﻿#include "Graphic.h"
#include <d3dx9core.h>

Graphic *Graphic::instance = NULL;

void Graphic::Init(HWND hWnd) {
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->hWnd = hWnd;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferHeight = 224;
	d3dpp.BackBufferWidth = 256;
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv
	);
	if (d3ddv == NULL)
		OutputDebugString("[ERROR] CreateDevice failed\n");
	//d3ddv->
	
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	D3DXCreateSprite(d3ddv, &spriteHandler);
	InitFont();
}

void Graphic::InitFont() {
	AddFontResourceEx("Resources/NinjaGaiden.ttf", FR_PRIVATE, 0);
	AddFontResourceEx("Resources/MyFont.ttf", FR_PRIVATE, 0);
	AddFontResourceEx("Resources/NinjaGaidenIII.ttf", FR_PRIVATE, 0);
	D3DXCreateFont(d3ddv, 8, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY, DEFAULT_PITCH,
		"Ninja Gaiden II (NES)", &normalFont);
	D3DXCreateFont(d3ddv, 8, 3, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY, DEFAULT_PITCH,
		"Ninja Gaiden II (NES)", &narrowFont);
	SetRect(&leftZone, 24, 17, 300, 300);
	SetRect(&rightZone, 128, 17, 300, 300);
	SetRect(&playerHealthZone, 176, 25, 300, 300);
	SetRect(&enemyHealthZone, 176, 33, 300, 300);
	SetRect(&iconSpiritZone, 64, 33, 300, 300);
	scoreInfor = "000000";
	timeInfor = "146";
	lifeInfor = "02";
	spiritInfor = "00";
	stageInfor = "3-1";
	playerHealthInfor = ";;;;;";
	enemyHealthInfor = "::::::::::::::::";
	healthIcon = "::::::::::::::::\n::::::::::::::::";
	iconSpirit = "+";
}
void Graphic::DrawString() {
	std::string left = "SCORE-" + scoreInfor + "\nTIMER-" + timeInfor + "{  |\nP-" + lifeInfor + "  -" + spiritInfor + "}  ~";
	std::string right = "STAGE-" + stageInfor + "\nNINJA-\nENEMY-";

	normalFont->DrawText(spriteHandler, left.c_str(), -1, &leftZone, DT_LEFT | DT_NOCLIP,
		0xFFFFFFFF);

	normalFont->DrawText(spriteHandler, right.c_str(), -1, &rightZone, DT_LEFT | DT_NOCLIP,
		0xFFFFFFFF);

	narrowFont->DrawText(spriteHandler, healthIcon.c_str(), -1, &playerHealthZone, DT_LEFT | DT_NOCLIP,
		0xFFFFFFFF);

	narrowFont->DrawText(spriteHandler, playerHealthInfor.c_str(), -1, &playerHealthZone, DT_LEFT | DT_NOCLIP,
		D3DCOLOR_XRGB(252,116,180));

	narrowFont->DrawText(spriteHandler, enemyHealthInfor.c_str(), -1, &enemyHealthZone, DT_LEFT | DT_NOCLIP,
		D3DCOLOR_XRGB(252, 116, 180));

	normalFont->DrawText(spriteHandler, iconSpirit.c_str(), -1, &iconSpiritZone, DT_LEFT | DT_NOCLIP,
		D3DCOLOR_XRGB(252, 116, 180));
}

//void Graphic::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha) {
//	D3DXVECTOR3 position(x, y, 0);
//	BoxCollider r;
//	r.top = top;
//	r.left = left;
//	r.right = right;
//	r.bottom = bottom;
//	spriteHandler->Draw(texture, &r, NULL, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
//}
//
//void Graphic::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, BoxCollider r, int alpha) {
//	D3DXVECTOR3 position(x, y, 0);
//	spriteHandler->Draw(texture, &r, NULL, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
//}
//
//void Graphic::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture) {
//	D3DXVECTOR3 position(x, y, 0);
//	spriteHandler->Draw(texture, NULL, NULL, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
//}

Graphic * Graphic::GetInstance() {
	if (instance == NULL)
		instance = new Graphic();
	return instance;
}

Graphic::~Graphic() {
	if (backBuffer != NULL)
		backBuffer->Release();
	if (d3ddv != NULL)
		d3ddv->Release();
	if (d3d != NULL)
		d3d->Release();
	if (normalFont != NULL) {
		normalFont->Release();
		normalFont = NULL;
	}
}
