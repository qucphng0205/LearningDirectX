#include "Unit.h"
#include "Grid.h"

Unit::Unit(Grid *gr, Entity *ent) {
	grid = gr;
	entity = ent;
	pos = D3DXVECTOR2(ent->GetPosition());
	prev = NULL;
	next = NULL;
	grid->Add(this);
	active = false;
}

Unit::Unit(Grid * gr, Entity * ent, int cellX, int cellY) {
	grid = gr;
	entity = ent;
	pos = D3DXVECTOR2(ent->GetPosition());
	prev = NULL;
	next = NULL;
	grid->Add(this, cellX, cellY);
	active = false;
}

Unit::~Unit() {
	if (entity->GetType() == Layer::PProjectileType)
		entity = entity;
	delete entity;
	entity = NULL;
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
