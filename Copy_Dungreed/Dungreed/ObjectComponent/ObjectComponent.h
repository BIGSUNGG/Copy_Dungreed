#pragma once

class Object;

class ObjectComponent
{
public:
	ObjectComponent(Object* inOwner);

	virtual void Update() abstract;

public:
	// ������Ʈ�� ������Ʈ �켱����
	virtual float GetComponentPriority() = 0;

protected:
	Object* _owner;

};

