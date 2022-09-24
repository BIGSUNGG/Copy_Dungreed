#include "framework.h"
#include "UI.h"

UI::UI()
{

}

void UI::Update()
{
	for (auto& object : _objects)
	{
		object->SetPos(CAMERA->GetPos() + object->GetSpawnPos());
		object->Update();
	}
}

void UI::PostRender()
{
	for (auto& object : _objects)
		object->Render();
}
