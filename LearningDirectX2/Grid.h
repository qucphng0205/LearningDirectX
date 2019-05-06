#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Entity.h"
#include "GameConfig.h"
#include "MyHelper.h"
#include "CollisionDetector.h"
#include "ObjectGroup.h"

//#include "Enemy.h"

//class GridCell {
//	//use topleft coordinates
//	D3DXVECTOR2 pos;
//	BoxCollider rect;
//	//nhung vat the nam trong gridcell
//	//std::vector<Enemy*> m_Enemies;
//	//nhung vat the co dinh trong map
//	std::vector<Entity*> m_StaticEntities;
//public:
//	GridCell();
//	GridCell(D3DXVECTOR2 position) { pos = position; };
//	GridCell(float x, float y) { pos = D3DXVECTOR2(x, y); };
//	void SetRect(float width, float height);
//	BoxCollider GetRect() { return rect; }
//	//xoa het vat the
//	void ClearAllEntities();
//	//void ClearEnemies();
//	//day entities trong gridcell vao entities
//	void GetAllEntityTo(std::vector<Entity*> &entities);
//
//	//void PushEnemy(Enemy *entity);
//
//	void PushStaticEntity(Entity *entity);
//	~GridCell();
//};
//
//class Grid {
//	int rows;
//	int columns;
//	float cellWidth;
//	float cellHeight;
//	GridCell **cells;
//	//kiem tra xem r1 va r2 co chong len nhau
//	bool IsOverlap(BoxCollider r1, BoxCollider r2);
//public:
//	//constructor cua grid dua vao khung cua the gioi, so luong hang, so luong cot
//	Grid(BoxCollider r, int rows = GRID_ROWS, int columns = GRID_COLUMNS);
//	//Se clear toan bo entities o trong toan bo gridcell
//	void Clear();
//	//void ClearEnemies();
//	//Dua entity vao gridcell nao do de gridcell do dua vao mang entities cua no
//	//void InsertEnemy(Enemy *entity);
//	//dua static entity vao gridcell nao do de gridcell do dua vao mang static entities cua no
//	void InsertStaticEntity(Entity *entity);
//	//Lay nhung entity co kha nang va cham voi BoxCollider r
//	void GetEntityWithRect(std::vector<Entity*> &entities, BoxCollider r);
//	~Grid();
//};

class Unit;
class Grid {
public:
	Grid(BoxCollider r);
	~Grid();
	void Add(Unit *unit);
	void AddStaticObject(Entity *ent);
	void HandleActiveUnit(BoxCollider camBox, Entity::EntityDirection camDirection, int cellX, int cellY);
	void HandleActive(BoxCollider camRect, Entity::EntityDirection camDirection);
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
private:
	ObjectGroup *staticObjects;
	float cellWidth;
	float cellHeight;
	int rows;
	int columns;
	Unit *cells[GRID_COLUMN][GRID_ROW];
	RECT activeRect;
};