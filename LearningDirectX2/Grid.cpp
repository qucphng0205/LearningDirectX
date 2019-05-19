#include "Grid.h"
#include "Unit.h"

Grid *Grid::instance = NULL;

Grid * Grid::GetInstance() {
	return instance;
}
//
//GridCell::GridCell() {
//	pos = D3DXVECTOR2(0, 0);
//}
//
//void GridCell::SetRect(float width, float height) {
//	rect = BoxCollider(pos.y, pos.x, pos.y - height, pos.x + width);
//}
//
//void GridCell::ClearAllEntities() {
//	//m_Enemies.clear();
//	m_StaticEntities.clear();
//}
//
////void GridCell::ClearEnemies() {
////	m_Enemies.clear();
////}
//
//void GridCell::GetAllEntityTo(std::vector<Entity*> &entities) {
//	//add enemies
//	//for (auto child : m_Enemies) {
//	//	int childID = child->GetID();
//	//	for (size_t i = 0; i < entities.size(); i++)
//	//		if (childID == entities[i]->GetID()) {
//	//			childID = -1;
//	//			break;
//	//		}
//	//	if (childID != -1)
//	//		entities.push_back(child);
//	//}
//	//add static
//	for (auto child : m_StaticEntities) {
//		int childID = child->GetID();
//		for (size_t i = 0; i < entities.size(); i++) {
//			if (childID == entities[i]->GetID()) {
//				childID = -1;
//				break;
//			}
//		}
//		if (childID != -1)
//			entities.push_back(child);
//	}
//}
//
////void GridCell::PushEnemy(Enemy * enemy) {
////	m_Enemies.push_back(enemy);
////}
//
//void GridCell::PushStaticEntity(Entity * entity) {
//	m_StaticEntities.push_back(entity);
//}
//
//GridCell::~GridCell() {
//}
//
//bool Grid::IsOverlap(BoxCollider r1, BoxCollider r2) {
//	if (r1.bottom > r2.top || r1.top < r2.bottom || r1.left > r2.right || r1.right < r2.left)
//		return false;
//	return true;
//}
//
//Grid::Grid(BoxCollider r, int rows, int columns) {
//	//--Debug
//	rows = 1;
//	columns = 1;
//
//	cellWidth = (float)(r.right - r.left) / rows;
//	cellHeight = (float)(r.top - r.bottom) / columns;
//
//	this->rows = rows;
//	this->columns = columns;
//
//	cells = new GridCell*[rows];
//	int **a;
//	a = new int*[rows];
//	for (int i = 0; i < rows; i++) {
//		a[i] = new int[columns];
//	}
//	for (int i = 0; i < rows; i++) {
//		cells[i] = new GridCell[columns];
//		for (int j = 0; j < columns; j++) {
//			cells[i][j] = GridCell(j * cellWidth, (i + 1) * cellHeight);
//			cells[i][j].SetRect(cellWidth, cellHeight);
//		}
//	}
//}
//
//void Grid::Clear() {
//	for (int i = 0; i < rows; i++)
//		for (int j = 0; j < columns; j++)
//			cells[i][j].ClearAllEntities();
//}
//
////void Grid::ClearEnemies() {
////	for (int i = 0; i < rows; i++)
////		for (int j = 0; j < columns; j++)
////			cells[i][j].ClearEnemies();
////	
////}
//
////void Grid::InsertEnemy(Enemy * enemy) {
////	BoxCollider entityBound = enemy->GetRect();
////	for (int i = 0; i < rows; i++)
////		for (int j = 0; j < columns; j++)
////			if (IsOverlap(cells[i][j].GetRect(), entityBound))
////				cells[i][j].PushEnemy(enemy);
////}
//
//void Grid::InsertStaticEntity(Entity * entity) {
//	BoxCollider entityBound = entity->GetRect();
//	for (int i = 0; i < rows; i++)
//		for (int j = 0; j < columns; j++)
//			if (IsOverlap(cells[i][j].GetRect(), entityBound))
//				cells[i][j].PushStaticEntity(entity);
//}
//
//void Grid::GetEntityWithRect(std::vector<Entity*> &entities, BoxCollider r) {
//	for (int i = 0; i < rows; i++)
//		for (int j = 0; j < columns; j++) {
//			BoxCollider rr = cells[i][j].GetRect();
//			if (IsOverlap(cells[i][j].GetRect(), r))
//				cells[i][j].GetAllEntityTo(entities);
//		}
//}
//
//Grid::~Grid() {
//	if (cells) {
//		for (int i = 0; i < rows; i++) {
//			delete[] cells[i];
//			cells[i] = nullptr;
//		}
//	}
//	delete[] cells;
//	cells = nullptr;
//}
//
//
//
Grid::Grid(BoxCollider r) {
	columns = GRID_COLUMN;
	rows = GRID_ROW;
	cellWidth = (float)(r.right - r.left) / columns;
	cellHeight = (float)(r.top - r.bottom) / rows;

	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++) {
			activeCells[x][y] = false;
			cells[x][y] = NULL;
		}

	effects = NULL;

	instance = this;

	//Unit *x = new Unit(NULL, NULL);
	//x->haha();
}

Grid::~Grid() {
	//delete grid double link list
	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			if (cells[x][y] != NULL) {
				Unit *unit = cells[x][y];
				Unit *other;
				while (unit != NULL) {
					other = unit->next;
					delete unit;
					unit = other;
				}
				cells[x][y] = NULL;
			}
	//delete effects double link list
	EffectChain *chain = effects;
	while (effects != NULL) {
		chain = effects->next;
		delete effects;
		effects = chain;
	}
	effects = NULL;
	//delete static object;
	for (size_t i = 0; i < staticObjects.size(); i++) {
		delete staticObjects[i];
		staticObjects[i] = NULL;
	}
}

void Grid::Add(Unit * unit) {
	int cellX = (int)(unit->pos.x / cellWidth);
	int cellY = (int)(unit->pos.y / cellHeight);
	if (cellX >= GRID_COLUMN)
		return;
	//link-list, add front
	unit->prev = NULL;
	unit->next = cells[cellX][cellY];
	cells[cellX][cellY] = unit;

	if (unit->next != NULL)
		unit->next->prev = unit;
}

void Grid::AddStaticObject(Entity * ent) {
	staticObjects.push_back(ent);
}

void Grid::HandleActiveUnit(BoxCollider camBox, Entity::EntityDirection camDirection, int cellX, int cellY) {

	Unit *unit = cells[cellX][cellY];
	float camCenterX = camBox.GetCenter().x;

	while (unit != NULL) {
		unit->active = true;
		if (!unit->entity->IsActive() && unit->entity->GetType() != Layer::EProjectileType) {
			auto entity = unit->entity;
			auto entityRect = entity->GetRect();
			Entity::EntityDirection direction = entity->GetMoveDirection();
			auto childPos = entity->GetPosition();

			if (unit->entity->GetType() == Layer::ItemType)
				entity->SetActive(true);

			else if (direction == Entity::EntityDirection::RightToLeft) {

				//neu entity xuat hien o border 
				//Neu o ben trai va player di trai
				//Neu o ben phai va player di phai
				entity->SetActive(
					(childPos.x < camCenterX && camDirection == Entity::RightToLeft && abs(entityRect.left - camBox.left) <= ENEMY_OFFSET_BORDER) ||
					(childPos.x > camCenterX && camDirection == Entity::LeftToRight && abs(camBox.right - entityRect.right) <= ENEMY_OFFSET_BORDER));
			}
			else {
				//Neu o ben trai va player di phai
				//Neu o ben phai va player di trai: MAYBE WRONG
				entity->SetActive((childPos.x < camCenterX && camDirection == Entity::LeftToRight && abs(entityRect.left - camBox.left) <= ENEMY_OFFSET_BORDER)/* || (childPos.x > camCenterX && camDirection == Entity::RightToLeft && camBox.right - entityRect.right <= ENEMY_OFFSET_BORDER)*/);
			}
		}
		unit = unit->next;
	}
}

void Grid::HandleActive(BoxCollider camRect, Entity::EntityDirection camDirection) {
	RECT r;
	r.left = (int)MyHelper::Clamp(camRect.left / cellWidth, 0, columns);
	r.right = (int)MyHelper::Clamp(camRect.right / cellWidth, 0, columns);
	r.top = (int)MyHelper::Clamp(camRect.top / cellHeight, 0, rows);
	r.bottom = (int)MyHelper::Clamp(camRect.bottom / cellHeight, 0, rows);
	activeRect = r;
	//CHECK ACTIVE FIRST
	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			if (x < r.left || x > r.right || y < r.bottom || y > r.top) {
				activeCells[x][y] = false;
				if (cells[x][y] != NULL) 
					if (cells[x][y]->entity->IsActive()) {
						HandleInactiveUnit(cells[x][y]);
						if (cells[x][y] == NULL)
							continue;
						cells[x][y]->Move(cells[x][y]->entity->GetPosition());
					}
			}
			else {
				activeCells[x][y] = true;
				if (cells[x][y] != NULL)
					HandleActiveUnit(camRect, camDirection, x, y);
			}
}

void Grid::HandleInactiveUnit(Unit * unit) {
	////--DEBUG
	//if (unit->entity->GetTag() == Entity::Projectile)
	//	unit = unit;
	Unit *other = unit;
	while (other != NULL) {
		unit = other;
		other = unit->next;
		unit->active = false;
		//maybe unit value of this unit pointer delete
		unit->entity->SetActive(false);
	}
}

void Grid::HandleCollision(double dt) {
	//COLLISION WITH STATIC: GROUND, WALL,...

	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			if (cells[x][y] != NULL && activeCells[x][y] == true) {
				//--DEBUG
				//if (cells[x][y]->entity->GetTag() == PLAYER)
				//	x = x;
				HandleCellWithStatic(cells[x][y], dt);
			}

	//CHECK COLLISION
	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			if (cells[x][y] != NULL && activeCells[x][y] == true)
				HandleCell(x, y, activeRect, dt);
}

void Grid::HandleCell(int x, int y, RECT r, double dt) {

	if (!cells[x][y]->active)
		return;

	Unit *unit = cells[x][y];

	while (unit != NULL) {
		if (unit->entity->IsActive()) {
			HandleUnit(unit, unit->next, dt);

			if (x > 0 && y > 0) HandleUnit(unit, cells[x - 1][y - 1], dt);
			if (x > 0) HandleUnit(unit, cells[x - 1][y], dt);
			if (y < GRID_ROW - 1) HandleUnit(unit, cells[x][y + 1], dt);
			if (x > 0 && y < GRID_ROW - 1)
				HandleUnit(unit, cells[x - 1][y + 1], dt);
		}
		unit = unit->next;
	}
}

void Grid::HandleUnit(Unit * unit, Unit * other, double dt) {
	while (other != NULL) {
		if (other->entity->IsActive())
			HandleMelee(unit->entity, other->entity, dt);
		other = other->next;
	}
}

void Grid::HandleCellWithStatic(Unit * unit, double dt) {
	while (unit != NULL) {
		if (unit->entity->IsActive()) {
			//--DEBUG
			//if (unit->entity->GetTag() == PLAYER)
			//	OutputDebugString(L"Player's checked collision\n");
			for (size_t i = 0; i < staticObjects.size(); i++)
				HandleCollideStatic(unit->entity, staticObjects[i], dt);
		}
		unit = unit->next;
	}
}

void Grid::HandleMelee(Entity * ent1, Entity * ent2, double dt) {

	Entity::SideCollision side;

	float collisionTime = 2;

	if (ent1->GetTag() == PLAYER || ent2->GetTag() == PLAYER)
		ent1 = ent1;

	if (!ent1->isStatic) {
		collisionTime = CollisionDetector::SweptAABB(ent1, ent2, side, dt);
		if (collisionTime == 2)
			return;
		ent1->OnCollision(ent2, side, collisionTime);
	}
	if (!ent2->isStatic) {
		collisionTime = CollisionDetector::SweptAABB(ent2, ent1, side, dt);
		ent2->OnCollision(ent1, side, collisionTime);
	}
}

void Grid::HandleCollideStatic(Entity * ent1, Entity * ent2, double dt) {
	//ent2's always static
	Entity::SideCollision side;

	auto rectEnt1 = BoxCollider(ent1->GetPosition(), ent1->GetWidth(), ent1->GetBigHeight());
	auto impactorRect = ent2->GetRect();

	float groundTime = CollisionDetector::SweptAABB(rectEnt1, ent1->GetVelocity(), impactorRect, D3DXVECTOR2(0, 0), side, dt);

	//--DEBUG
	if (ent1->GetTag() == PLAYER && impactorRect.left == 16 && impactorRect.top == 40)
		groundTime = groundTime;

	if (groundTime == 2)
		return;

	ent1->OnCollision(ent2, side, groundTime);
}

void Grid::Move(Unit * unit, float x, float y) {
	int oldCellX = (int)(unit->pos.x / cellWidth);
	int oldCellY = (int)(unit->pos.y / cellHeight);

	int cellX = (int)(x / cellWidth);
	int cellY = (int)(y / cellHeight);

	//Out of screen
	if (cellX >= GRID_COLUMN || cellX < 0 || cellY >= GRID_ROW || cellY < 0) {
		unit->entity->SetActive(false);
		return;
	}

	unit->pos.x = x;
	unit->pos.y = y;

	if (oldCellX == cellX && oldCellY == cellY)
		return;

	//--DEBUG
	//if (unit->entity->GetTag() == PLAYER)
	//	x = x;

	if (unit->prev != NULL)
		unit->prev->next = unit->next;

	if (unit->next != NULL)
		unit->next->prev = unit->prev;

	if (cells[oldCellX][oldCellY] == unit)
		cells[oldCellX][oldCellY] = unit->next;

	Add(unit);
}

void Grid::MoveActiveUnit(Unit *unit) {
	Unit *other = unit;

	while (other != NULL) {
		unit = other;
		other = unit->next;
		unit->Move(unit->entity->GetPosition());
	}
}

void Grid::Update(double dt) {
	//update entity
	//used to bug: update 2 times if not update unit
	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			if (cells[x][y] != NULL && activeCells[x][y] == true)
				UpdateUnit(cells[x][y], dt);
	//update effect
	UpdateEffect(dt);
	//update unit
	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			if (cells[x][y] != NULL && activeCells[x][y] == true)
				MoveActiveUnit(cells[x][y]);
}

void Grid::UpdateUnit(Unit *unit, double dt) {
	while (unit != NULL) {
		if (unit->entity->IsActive()) {
			unit->entity->Update(dt);
		}
		unit = unit->next;
	}
}

void Grid::Render() {
	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
			if (cells[x][y] != NULL && activeCells[x][y] == true)
				RenderUnit(cells[x][y]);
	RenderEffect();
}

void Grid::RenderUnit(Unit *unit) {
	while (unit != NULL) {
		if (unit->entity->IsActive())
			unit->entity->Render();
		unit = unit->next;
	}
}

void Grid::ahha() {
}

void Grid::AddEffect(EffectChain * chain) {
	chain->prev = NULL;
	chain->next = effects;
	effects = chain;
	if (chain->next != NULL)
		chain->next->prev = chain;
}

void Grid::RemoveEffect(EffectChain *chain) {
	if (chain->prev != NULL)
		chain->prev->next = chain->next;
	if (chain->next != NULL)
		chain->next->prev = chain->prev;
	if (effects == chain)
		effects = chain->next;
	chain = effects;
}

void Grid::UpdateEffect(double dt) {
	auto chain = effects;
	while (chain != NULL) {
		if (!chain->data->Update(dt))
			RemoveEffect(chain);
		chain = chain->next;
	}
}

void Grid::RenderEffect() {
	auto chain = effects;
	while (chain != NULL) {
		chain->data->Render();
		chain = chain->next;
	}
}

