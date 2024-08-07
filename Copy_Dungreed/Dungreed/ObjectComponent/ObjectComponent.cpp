#include "framework.h"
#include "ObjectComponent.h"

ObjectComponent::ObjectComponent(Object* object)
{
	SetOwner(object);
}
