#include "..\stdafx.h"
#include "ActorObject.h"
bool ActorObject::HasCollision(const ActorObject* actorOne, const ActorObject* actorTwo)
{
	if (collisionMatrix[actorOne->_type][actorTwo->_type])
	{
		Vec2 diff = actorOne->_position;
		diff -= actorTwo->_position;
		float dist = diff.Length();
		return dist <= actorOne->_radius + actorTwo->_radius;
	}
	return false;
}
