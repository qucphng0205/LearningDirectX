#include "Grid.h"

void GridCell::SetRect(float width, float height) {
	rect = BoxCollider(pos.y, pos.x, pos.y - height, pos.x + width);
}

void GridCell::ClearAllEntities() {
	m_Entities.clear();
	m_StaticEntities.clear();
}

void GridCell::GetAllEntityTo(std::vector<Entity*> &entities) {
	//add non-static
	for (auto child : m_Entities) {
		int childID = child->GetID();
		for (size_t i = 0; i < entities.size(); i++)
			if (childID == entities[i]->GetID()) {
				childID = -1;
				break;
			}
		if (childID != -1)
			entities.push_back(child);
	}
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

void GridCell::PushEntity(Entity * entity) {
	m_Entities.push_back(entity);
}

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

void Grid::InsertEntity(Entity * entity) {
	BoxCollider entityBound = entity->GetRect();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (IsOverlap(cells[i][j].GetRect(), entityBound))
				cells[i][j].PushEntity(entity);
}

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



