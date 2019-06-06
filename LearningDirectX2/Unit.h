#pragma once
#include "Grid.h"

class Unit {
	friend class Grid;
public:
	Unit(Grid *gr, Entity *ent);
	Unit(Grid *gr, Entity *ent, int cellX, int cellY);
	void SetEntity(Entity *ent) { entity = ent;  }
	Entity* GetEntity() { return entity; }
	void Move(float x, float y);
	void Move(D3DXVECTOR3 newPosition);
	void SetActive(bool active) { this->active = active; }
	void haha();

	virtual ~Unit();

private:
	Grid *grid;
	Entity *entity;
	D3DXVECTOR2 pos;
	Unit *prev, *next;
	bool active;
};