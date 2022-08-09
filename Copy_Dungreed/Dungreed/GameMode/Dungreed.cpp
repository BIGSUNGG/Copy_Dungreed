#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	CAMERA->GetFreeMode() = false;

	_map = make_shared<Map>();
	_map->GetObjects()[Object::Object_Type::CREATURE].emplace_back(GET_OBJECT(3, -1, 0));
	_map->GetObjects()[Object::Object_Type::CREATURE].back()->GetTexture()->GetTransform()->GetPos() = CENTER;

	CAMERA->SetTarget(_map->GetObjects()[Object::Object_Type::CREATURE].back()->GetTexture()->GetTransform());
	CAMERA->SetLeftBottom(_map->GetLeftBottom());
	CAMERA->SetRightTop(_map->GetRightTop());
}

void Dungreed::Update()
{
	GAME->Update();
}

void Dungreed::PreRender()
{

}

void Dungreed::Render()
{
	GAME->Render();
}

void Dungreed::PostRender()
{
	GAME->PostRender();
}

void Dungreed::ImGuiRender()
{

}
