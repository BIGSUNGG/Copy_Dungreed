#include "framework.h"
#include "DebugMode.h"

DebugMode::DebugMode()
{
	GAME->Reset();
	_modeType = DEBUG;

	auto _map = MAP_MANAGER->Load(_mapLevel, _mapNum);
	MAP_MANAGER->SetCurMap(_map);

	Init();

	_cursur = OBJ_MANAGER->GetCursur(2);
	CursurOn();
}

void DebugMode::Update()
{
	_cursur->GetTransform()->GetPos() = MOUSE_WORLD_POS;
	_cursur->Update();

	GAME->Update();
	MAP_MANAGER->Update();
}

void DebugMode::PreRender()
{
	GAME->PreRender();
}

void DebugMode::Render()
{
	GAME->Render();
}

void DebugMode::PostRender()
{
	GAME->PostRender();

	_cursur->Render();
}

void DebugMode::ImGuiRender()
{
	if (ImGui::CollapsingHeader("Player"))
	{
		ImGui::Text("Pos : %0.1f , %0.1f", _player->GetObjectTexture()->GetTransform()->GetPos().x, _player->GetObjectTexture()->GetTransform()->GetPos().y);
		ImGui::Text("Velocity : %0.1f , %0.1f", _player->GetVelocity().x, _player->GetVelocity().y);
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
	_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));
	_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));

	GAME->AddPlayer(_player);
	GAME->GetObjectUpdate() = true;

	CAMERA->SetTarget(_player->GetObjectTexture()->GetTransform());
	CAMERA->SetLeftBottom(MAP_MANAGER->GetCurMap()->GetLeftBottom());
	CAMERA->SetRightTop(MAP_MANAGER->GetCurMap()->GetRightTop());
	CAMERA->Update();
}
