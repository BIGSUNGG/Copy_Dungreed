#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	_modeType = DUNGREED;

	CAMERA->GetFreeMode() = false;

	_map = make_shared<Map>();
	_map->Load();

	_player = MAKE_CREATURE(-1, 0);
	_player->GetTexture()->GetTransform()->GetPos() = _map->GetStartPos();

	GAME->GetObjects()[Object::Object_Type::CREATURE].emplace_back(dynamic_pointer_cast<Object>(_player));
	GAME->GetBGUpdate() = true;

	CAMERA->SetTarget(_player->GetTexture()-> GetTransform());
	CAMERA->SetLeftBottom(_map->GetLeftBottom());
	CAMERA->SetRightTop(_map->GetRightTop());

	_cursur = OBJ_MANAGER->GetCursur(2);
	CAMERA->GetVelocity() = { 0,0 };

	CursurOff();
}

void Dungreed::Update()
{
	_gameRunTime += DELTA_TIME;
	_cursur->GetTransform()->GetPos() = MOUSE_WORLD_POS;

	_cursur->Update();

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
	_cursur->Render();
	GAME->PostRender();
}

void Dungreed::ImGuiRender()
{
	if (ImGui::CollapsingHeader("Dungreed"))
	{
		ImGui::Text("Run Time : %f", _gameRunTime);
	}
	if (ImGui::CollapsingHeader("Player"))
	{
		ImGui::Text("Pos : %0.1f , %0.1f", _player->GetTexture()->GetTransform()->GetPos().x, _player->GetTexture()->GetTransform()->GetPos().y);
		ImGui::Text("Velocity : %0.1f , %0.1f", _player->GetVelocity().x, _player->GetVelocity().y);
	}

	GAME->ImguiRender();
}
