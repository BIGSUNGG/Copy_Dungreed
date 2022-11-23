#include "framework.h"
#include "DebugMode.h"

DebugMode::DebugMode()
{
	GAME->Reset();
	_modeType = DEBUG;

	CAMERA->GetFreeMode() = false;
	auto _map = MAP_MANAGER->Load(_mapLevel, _mapNum);

	MAP_MANAGER->SetCurMap(_map);

	Init();

	MOUSE_CURSUR->CursurOff();
}

void DebugMode::Update()
{
	GAME->Update();
	MAP_MANAGER->Update();
	UI_MANAGER->Update();
}

void DebugMode::PreRender()
{
	GAME->PreRender();
	UI_MANAGER->PreRender();
}

void DebugMode::Render()
{
	GAME->Render();
}

void DebugMode::PostRender()
{
	GAME->PostRender();
	UI_MANAGER->PostRender();
}

void DebugMode::ImGuiRender()
{
	if (ImGui::CollapsingHeader("Player"))
	{
		ImGui::Text("Pos : %0.1f , %0.1f", _player->GetObjectTexture()->GetTransform()->GetPos().x, _player->GetObjectTexture()->GetTransform()->GetPos().y);
		ImGui::Text("Velocity : %0.1f , %0.1f", _player->GetMovementComponent()->GetVelocity().x, 
			_player->GetMovementComponent()->GetVelocity().y);
	}
	if (ImGui::CollapsingHeader("Map"))
	{
		ImGui::SliderInt("Level", &_mapLevel, 0, 8);
		ImGui::SliderInt("Num", &_mapNum, 0, 30);

		if (ImGui::Button("Load"))
		{
			auto _map = MAP_MANAGER->Load(_mapLevel, _mapNum);
			MAP_MANAGER->SetCurMap(_map);
			Init();
		}
	}

	GAME->ImguiRender();
}

void DebugMode::Init()
{
	_player = dynamic_pointer_cast<Player>(MAKE_PLAYER(0));
	_player->GetObjectTexture()->GetTransform()->GetPos().x = MAP_MANAGER->GetCurMap()->GetStartPos().x;
	_player->GetObjectTexture()->SetBottom(MAP_MANAGER->GetCurMap()->GetStartPos().y);
	_player->SetSpawnPos(_player->GetObjectTexture()->GetTransform()->GetPos());
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 2));
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 1));

	GAME->AddPlayer(_player);
	GAME->GetPlaying() = true;

	CAMERA->SetTarget(_player->GetObjectTexture()->GetTransform());
	CAMERA->SetLeftBottom(MAP_MANAGER->GetCurMap()->GetLeftBottom());
	CAMERA->SetRightTop(MAP_MANAGER->GetCurMap()->GetRightTop());
	CAMERA->Update();
}
