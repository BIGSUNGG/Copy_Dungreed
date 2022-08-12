#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	CAMERA->GetFreeMode() = false;

	_map = make_shared<Map>();
	_map->Load();

	shared_ptr<Object> player = MAKE_OBJECT(3, -1, 0);
	player->GetTexture()->GetTransform()->GetPos() = _map->GetStartPos();

	GAME->GetObjects()[Object::Object_Type::CREATURE].emplace_back(player);

	CAMERA->SetTarget(player->GetTexture()-> GetTransform());
	CAMERA->SetLeftBottom(_map->GetLeftBottom());
	CAMERA->SetRightTop(_map->GetRightTop());
}

void Dungreed::Update()
{
	GAME->Update();
}

void Dungreed::PreRender()
{
	GAME->PreRender();
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
	GAME->ImguiRender();
}
