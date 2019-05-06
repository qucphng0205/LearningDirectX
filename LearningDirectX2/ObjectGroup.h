#pragma once
#include "Entity.h"
#include <vector>
class ObjectGroup {
public:
	ObjectGroup();
	~ObjectGroup();
	void AddObject(Entity *e);
	void GetStatics(std::vector<Entity*> &entities);
	//void GetActiveObject(std::vector<Entity*> &entities);
	//virtual void Update(double dt) = 0;
	//virtual void Render() = 0;
	std::vector<Entity*> entities;
};