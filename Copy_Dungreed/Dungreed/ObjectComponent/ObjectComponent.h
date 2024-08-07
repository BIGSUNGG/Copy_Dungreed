#pragma once

class Object;

class ObjectComponent
{
public:
	ObjectComponent(Object* object = nullptr);

	virtual void Update() abstract;

	virtual void SetOwner(Object* owner) { _owner = owner; }

protected:
	Object* _owner;

};

