#include "framework.h"
#include "DebugMode.h"

DebugMode::DebugMode()
	: DebugMode(0, 0)
{
}

DebugMode::DebugMode(int level, int num)
{
	_modeType = GameModeType::DEBUG;
	_mapLevel = level;
	_mapNum = num;

	shared_ptr<Map> _map = MAP_MANAGER->Load(level, num);
	Init(_map);
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
			shared_ptr<Map> _map = MAP_MANAGER->Load(_mapLevel, _mapNum);
			Init(_map);
		}
	}

	GAME->ImguiRender();
}

void DebugMode::Init(shared_ptr<Map> debugMap)
{
	_curMap = debugMap;

	GAME->Reset();
	CAMERA->SetFreeMode(false);

	MAP_MANAGER->SetCurMap(_curMap);

	_player.reset();

	_player = dynamic_pointer_cast<Player>(MAKE_PLAYER(2));
	_player->GetObjectTexture()->GetTransform()->GetPos().x = MAP_MANAGER->GetCurMap()->GetStartPos().x;
	_player->GetObjectTexture()->SetBottom(MAP_MANAGER->GetCurMap()->GetStartPos().y);
	_player->SetSpawnPos(_player->GetObjectTexture()->GetTransform()->GetPos());
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 2));
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 1));

	GAME->SetPlayer(_player);
	GAME->SetPlaying(true);
	GAME->SetEnableUI(true);

	CAMERA->SetTarget(_player->GetObjectTexture()->GetTransform());
	CAMERA->SetLeftBottom(MAP_MANAGER->GetCurMap()->GetLeftBottom());
	CAMERA->SetRightTop(MAP_MANAGER->GetCurMap()->GetRightTop());
	CAMERA->Update();

	MOUSE_CURSUR->CursurOff();
}
