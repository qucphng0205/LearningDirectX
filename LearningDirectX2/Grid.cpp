#include "Grid.h"

GridCell::GridCell() {
	pos = D3DXVECTOR2(0, 0);
}

void GridCell::SetRect(float width, float height) {
	rect = BoxCollider(pos.y, pos.x, pos.y - height, pos.x + width);
}

void GridCell::ClearAllEntities() {
	//m_Enemies.clear();
	m_StaticEntities.clear();
}

//void GridCell::ClearEnemies() {
//	m_Enemies.clear();
//}

void GridCell::GetAllEntityTo(std::vector<Entity*> &entities) {
	//add enemies
	//for (auto child : m_Enemies) {
	//	int childID = child->GetID();
	//	for (size_t i = 0; i < entities.size(); i++)
	//		if (childID == entities[i]->GetID()) {
	//			childID = -1;
	//			break;
	//		}
	//	if (childID != -1)
	//		entities.push_back(child);
	//}
	//add static
	for (auto child : m_StaticEntities) {
		int childID = child->GetID();
		for (size_t i = 0; i < entities.size(); i++) {
			if (childID == entities[i]->GetID()) {
				childID = -1;
				break;
			}
		}
		if (childID != -1)
			entities.push_back(child);
	}
}

//void GridCell::PushEnemy(Enemy * enemy) {
//	m_Enemies.push_back(enemy);
//}

void GridCell::PushStaticEntity(Entity * entity) {
	m_StaticEntities.push_back(entity);
}

GridCell::~GridCell() {
}

bool Grid::IsOverlap(BoxCollider r1, BoxCollider r2) {
	if (r1.bottom > r2.top || r1.top < r2.bottom || r1.left > r2.right || r1.right < r2.left)
		return false;
	return true;
}

Grid::Grid(BoxCollider r, int rows, int columns) {
	//--Debug
	rows = 1;
	columns = 1;

	cellWidth = (float)(r.right - r.left) / rows;
	cellHeight = (float)(r.top - r.bottom) / columns;

	this->rows = rows;
	this->columns = columns;

	cells = new GridCell*[rows];
	int **a;
	a = new int*[rows];
	for (int i = 0; i < rows; i++) {
		a[i] = new int[columns];
	}
	for (int i = 0; i < rows; i++) {
		cells[i] = new GridCell[columns];
		for (int j = 0; j < columns; j++) {
			cells[i][j] = GridCell(j * cellWidth, (i + 1) * cellHeight);
			cells[i][j].SetRect(cellWidth, cellHeight);
		}
	}
}

void Grid::Clear() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			cells[i][j].ClearAllEntities();
}

//void Grid::ClearEnemies() {
//	for (int i = 0; i < rows; i++)
//		for (int j = 0; j < columns; j++)
//			cells[i][j].ClearEnemies();
//	
//}

//void Grid::InsertEnemy(Enemy * enemy) {
//	BoxCollider entityBound = enemy->GetRect();
//	for (int i = 0; i < rows; i++)
//		for (int j = 0; j < columns; j++)
//			if (IsOverlap(cells[i][j].GetRect(), entityBound))
//				cells[i][j].PushEnemy(enemy);
//}

void Grid::InsertStaticEntity(Entity * entity) {
	BoxCollider entityBound = entity->GetRect();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (IsOverlap(cells[i][j].GetRect(), entityBound))
				cells[i][j].PushStaticEntity(entity);
}

void Grid::GetEntityWithRect(std::vector<Entity*> &entities, BoxCollider r) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			BoxCollider rr = cells[i][j].GetRect();
			if (IsOverlap(cells[i][j].GetRect(), r))
				cells[i][j].GetAllEntityTo(entities);
		}
}

Grid::~Grid() {
	if (cells) {
		for (int i = 0; i < rows; i++) {
			delete[] cells[i];
			cells[i] = nullptr;
		}
	}
	delete[] cells;
	cells = nullptr;
}



