#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "GameConfig.h"
#include "MyHelper.h"
#include "CollisionDetector.h"
#include "Effect.h"
#include "DataManager.h"

//not only the grid of the world, but also the box containts all the update-able object: effect, enemies,... or static objects like ground
class Unit;
class Grid {
public:
	static Grid *GetInstance();
	Grid(BoxCollider r, int columns = GRID_COLUMN, int rows = GRID_ROW);
	~Grid();
	void Add(Unit *unit);
	void AddStaticObject(Entity *ent);
	void HandleActiveUnit(BoxCollider camBox, Entity::EntityDirection camDirection, int cellX, int cellY);
	void HandleActive(BoxCollider camRect, Entity::EntityDirection camDirection);
	void HandleInactiveUnit(Unit *unit);
	//rows * columns * 100 vs 100
	void HandleCollision(double dt);
	//100 vs 100
	void HandleCell(int x, int y, RECT r, double dt);
	//1 vs 100
	void HandleUnit(Unit *unit, Unit *other, double dt);
	void HandleCellWithStatic(Unit *unit, double dt);
	void HandleMelee(Entity *ent1, Entity *ent2, double dt);
	void HandleCollideStatic(Entity *ent1, Entity*ent2, double dt);
	void Move(Unit *unit, float x, float y);
	void MoveActiveUnit(Unit *unit);
	void Update(double dt);
	void UpdateUnit(Unit *unit, double dt);
	void Render();
	void RenderUnit(Unit *unit);
	void ahha();

	void AddEffect(EffectChain *chain);
	void RemoveEffect(EffectChain *chain);
	void UpdateEffect(double dt);
	void RenderEffect();
private:
	static Grid *instance;
	float cellWidth;
	float cellHeight;
	int rows;
	int columns;
	Unit *cells[GRID_COLUMN][GRID_ROW];
	bool activeCells[GRID_COLUMN][GRID_ROW];
	RECT activeRect;

	EffectChain *effects;
	std::vector<Entity*> staticObjects;
};