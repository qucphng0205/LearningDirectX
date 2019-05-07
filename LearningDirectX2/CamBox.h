#pragma once
#include "Entity.h"
class CamBox : public Entity {
public:
	CamBox(BoxCollider rect, D3DXVECTOR2 velocity);
	virtual BoxCollider GetRect();
private:
	BoxCollider rect;
};