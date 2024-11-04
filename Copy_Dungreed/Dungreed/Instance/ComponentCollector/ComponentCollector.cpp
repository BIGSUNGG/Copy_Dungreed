#include "framework.h"
#include "ComponentCollector.h"

ComponentCollector::ComponentCollector(Object* inOwner)
{
	_owner = inOwner;
}

void ComponentCollector::Update()
{
	// ������Ʈ�� �켱������ ���� ������Ʈ
	for (auto& component : _components)
	{
		component->Update();
	}
}

void ComponentCollector::Add(shared_ptr<ObjectComponent> inComponent)
{
	_components.push_back(inComponent);
	sort(_components.begin(), _components.end(), [](const shared_ptr<ObjectComponent>& a1, const shared_ptr<ObjectComponent>& a2)
		{
			// Priority ������ ��������
			return a1->GetComponentPriority() > a2->GetComponentPriority();
		});
}

void ComponentCollector::Remove(shared_ptr<ObjectComponent> inComponent)
{
	_components.erase(remove(_components.begin(), _components.end(), inComponent), _components.end());
}
