#include "StaticEntity.h"

StaticEntity::StaticEntity() : Entity() {
	type = Layer::StaticType;
	Tag = Tag::LADDER;
}
