#include "Unit.h"
#include "Grid.h"

Unit::Unit(Grid *gr, Entity *ent) {
	grid = gr;
	entity = ent;
	pos = D3DXVECTOR2(ent->GetPosition());
	prev = NULL;
	next = NULL;
	OutputDebugString(L"ASD");
	grid->Add(this);
	active = false;
}

void Unit::Move(float x, float y) {
	grid->Move(this, x, y);
}

void Unit::Move(D3DXVECTOR3 newPosition) {
	grid->Move(this, newPosition.x, newPosition.y);
}

void Unit::haha() {
	grid->ahha();
}
