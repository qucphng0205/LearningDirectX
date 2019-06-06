#include "Scene.h"

Scene::Scene() {
	//backColor = 0x4866ff;
	backColor = D3DCOLOR_XRGB(0, 0, 0);
}
D3DCOLOR Scene::GetBackColor() {
	return backColor;
}

void Scene::ProcessInput() {
}
