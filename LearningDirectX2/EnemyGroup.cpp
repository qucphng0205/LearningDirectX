#include "EnemyGroup.h"

EnemyGroup::EnemyGroup() {
}

void EnemyGroup::CheckActive(Camera *cam, D3DXVECTOR2 camVelocity) {
	if (camVelocity.x == 0)
		return;
	BoxCollider camBox = cam->GetRect();
	D3DXVECTOR2 center = camBox.GetCenter();
	for (size_t i = 0; i < entities.size(); i++) {
		//--DEBUG--
		if (i == 9)
			i = 9;
		auto entityRect = entities[i]->GetRect();
		if (!entities[i]->IsActive()) {

			if (!cam->IsContaint(entityRect))
				continue;

			Entity::EntityDirection direction = entities[i]->GetMoveDirection();
			auto childPos = entities[i]->GetPosition();

			if (direction == Entity::EntityDirection::RightToLeft) {

				//neu entity xuat hien o border 
				//Neu o ben trai va player di trai
				//Neu o ben phai va player di phai
				entities[i]->SetActive((childPos.x < center.x && camVelocity.x < 0 && entityRect.left - camBox.left <= ENEMY_OFFSET_BORDER) || (childPos.x > center.x && camVelocity.x > 0 && camBox.right - entityRect.right <= ENEMY_OFFSET_BORDER));
			}
			else {
				//Neu o ben trai va player di phai
				//Neu o ben phai va player di trai
				entities[i]->SetActive((childPos.x < center.x && camVelocity.x > 0 && entityRect.left - camBox.left <= ENEMY_OFFSET_BORDER) || (childPos.x > center.x && camVelocity.x < 0 && camBox.right - entityRect.right <= ENEMY_OFFSET_BORDER));
			}

		}
		else if (entities[i]->IsActive() && cam->IsHalfContaint(entities[i]->GetRect())) {
			entities[i]->SetActive(false);
		}

	}
}

void EnemyGroup::Update(double dt) {
	for (size_t i = 0; i < entities.size(); i++)
		if (entities[i]->IsActive())
			entities[i]->Update(dt);
}

void EnemyGroup::Render() {
	for (size_t i = 0; i < entities.size(); i++)
		if (entities[i]->IsActive())
			entities[i]->Render();
}
