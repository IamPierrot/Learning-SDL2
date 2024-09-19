#include "ECS.h"

void Entity::addGroup(Group mGroup)
{
     groupBitSet[mGroup] = true;
     manager.addToGroup(this, mGroup);
}
