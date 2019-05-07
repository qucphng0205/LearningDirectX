#include "CamBox.h"

CamBox::CamBox(BoxCollider rect, D3DXVECTOR2 velocity) {
	tag = CamRect;
	this->rect = rect;
	this->velocity = velocity;
	width = rect.right - rect.left;
	height = rect.top - rect.bottom;
}

BoxCollider CamBox::GetRect() {
	return rect;
}
