#include "EnemyGroup.h"

EnemyGroup::EnemyGroup() {
}

void EnemyGroup::CheckActive(Camera *cam, D3DXVECTOR2 camVelocity) {
	if (camVelocity.x == 0)
		return;
	BoxCollider camBox = cam->GetRect();
	D3DXVECTOR2 center = camBox.GetCenter();
	for (size_t i = 0; i < entities.size(); i++) {

		if (!entities[i]->IsActive() && !entities[i]->wasInCamera) {

			if (cam->IsContaint(entities[i]->GetRect()))
				entities[i]->wasInCamera = true;
			else
				continue;

			Entity::EntityDirection direction = entities[i]->GetMoveDirection();
			auto childPos = entities[i]->GetPosition();

			if (direction == Entity::EntityDirection::RightToLeft) {
				//Neu o ben trai va player di trai
				//Neu o ben phai va player di phai
				entities[i]->SetActive((childPos.x < center.x && camVelocity.x < 0) || (childPos.x > center.x && camVelocity.x > 0));
			}
			else {
				//Neu o ben trai va player di phai
				//Neu o ben phai va player di trai
				entities[i]->SetActive((childPos.x < center.x && camVelocity.x > 0) || (childPos.x > center.x && camVelocity.x < 0));
			}
		}
		else if (entities[i]->IsActive() && cam->IsHalfContaint(entities[i]->GetRect())) {
			entities[i]->wasInCamera = false;
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
