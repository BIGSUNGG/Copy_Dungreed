#pragma once

class Object;

class ObjectComponent
{
public:
	ObjectComponent(Object* object = nullptr);

	virtual void Update() abstract;

	virtual void SetObject(Object* object) { _object = object; }

protected:
	Object* _object;

};

