#include "framework.h"
#include "DebugMode.h"

DebugMode::DebugMode()
{
	GAME->Reset();
	_modeType = DEBUG;

	CAMERA->SetFreeMode(false);
	auto _map = MAP_MANAGER->Load(_mapLevel, _mapNum);

	MAP_MANAGER->SetCurMap(_map);

	Init();

	MOUSE_CURSUR->CursurOff();
}

void DebugMode::Update()
{
	GAME->Update();
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
			Init();
			shared_ptr<Map> _map = MAP_MANAGER->Load(_mapLevel, _mapNum);
			MAP_MANAGER->SetCurMap(_map);
		}
	}

	GAME->ImguiRender();
}

void DebugMode::Init()
{
	_player.reset();

	_player = dynamic_pointer_cast<Player>(MAKE_PLAYER(2));
	_player->GetObjectTexture()->GetTransform()->GetPos().x = MAP_MANAGER->GetCurMap()->GetStartPos().x;
	_player->GetObjectTexture()->SetBottom(MAP_MANAGER->GetCurMap()->GetStartPos().y);
	_player->SetSpawnPos(_player->GetObjectTexture()->GetTransform()->GetPos());
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 2));
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 1));

	GAME->AddPlayer(_player);
	GAME->SetPlaying(true);
	GAME->SetEnableUI(true);

	CAMERA->SetTarget(_player->GetObjectTexture()->GetTransform());
	CAMERA->SetLeftBottom(MAP_MANAGER->GetCurMap()->GetLeftBottom());
	CAMERA->SetRightTop(MAP_MANAGER->GetCurMap()->GetRightTop());
	CAMERA->Update();
}
