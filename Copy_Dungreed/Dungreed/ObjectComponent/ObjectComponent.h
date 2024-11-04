#pragma once

class Object;

class ObjectComponent
{
public:
	ObjectComponent(Object* inOwner);

	virtual void Update() abstract;

public:
	// 컴포넌트의 업데이트 우선순위
	virtual float GetComponentPriority() = 0;

protected:
	Object* _owner;

};

