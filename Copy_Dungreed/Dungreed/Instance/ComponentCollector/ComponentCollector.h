#pragma once

class Object;
class ObjectComponent;

class ComponentCollector
{
public:
	ComponentCollector(Object* inOwner);

public:
	void Update();

	void Add(shared_ptr<ObjectComponent> inComponent);
	void Remove(shared_ptr<ObjectComponent> inComponent);

private:
	Object* _owner = nullptr;
	vector<shared_ptr<ObjectComponent>> _components;
};