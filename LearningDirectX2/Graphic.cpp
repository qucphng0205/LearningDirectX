#include "Graphic.h"
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
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	D3DXCreateSprite(d3ddv, &spriteHandler);
	InitFont();
}
int y;
#include <time.h>

void Graphic::InitFont() {
	int x = 0;
	AddFontResourceEx("Resources/NinjaGaiden.ttf", FR_PRIVATE, 0);
	AddFontResourceEx("Resources/NinjaGaidenII.ttf", FR_PRIVATE, 0);
	AddFontResourceEx("Resources/NinjaGaidenIII.ttf", FR_PRIVATE, 0);
	D3DXCreateFont(d3ddv, 8, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		"Ninja Gaiden II (NES)", &smallFont);
	//y = D3DXCreateFontA(d3ddv, 20, 0, FW_NORMAL, 1, false,
	//	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	//	ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
	//	"Ninja Gaiden (NES)", &largeFont);
	srand(time(NULL));
	SetRect(&scoreZone, 24, 17, 900, 900);
	SetRect(&timerPZone, 24, 25, 900, 900);
	SetRect(&rightZone, 128, 17, 900, 900);
}

void Graphic::DrawString() {
	scoreInfor = "SCORE-000000\nTIMER-146\nP-02  -00";
	smallFont->DrawTextA(NULL, scoreInfor.c_str(), -1, &scoreZone, DT_LEFT,
		0xFFFFFFFF);
	rightInfor = "STAGE-3-1\nNINJA-\nENEMY-";
	smallFont->DrawTextA(NULL, rightInfor.c_str(), -1, &rightZone, DT_LEFT,
		0xFFFFFFFF);
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
}
