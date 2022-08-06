#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	CAMERA->GetFreeMode() = true;

	_map = make_shared<Map>();
}

void Dungreed::Update()
{
	_map->Update();
}

void Dungreed::PreRender()
{

}

void Dungreed::Render()
{
	_map->Render();
}

void Dungreed::PostRender()
{
}

void Dungreed::ImGuiRender()
{

}
