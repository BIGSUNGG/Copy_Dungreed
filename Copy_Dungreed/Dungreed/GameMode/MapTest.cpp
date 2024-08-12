#include "framework.h"
#include "MapTest.h"

MapTest::MapTest()
	: MapTest(0, 0)
{
}

MapTest::MapTest(int level, int num)
{
	_modeType = GameModeType::MAP_TEST;
	_mapLevel = level;
	_mapNum = num;

	shared_ptr<Map> _map = MAP_MANAGER->LoadMap(level, num);
	Init(_map);
}

void MapTest::Update()
{
	GAME->Update();
}

void MapTest::PreRender()
{
	GAME->PreRender();
}

void MapTest::Render()
{
	GAME->Render();
}

void MapTest::PostRender()
{
	GAME->PostRender();
}

void MapTest::ImGuiRender()
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
			shared_ptr<Map> _map = MAP_MANAGER->LoadMap(_mapLevel, _mapNum);
			Init(_map);
		}
	}

	GAME->ImguiRender();
}

void MapTest::Init(shared_ptr<Map> testMap)
{
	_curMap = testMap;

	// 게임 초기화
	GAME->Reset();
	CAMERA->SetFreeMode(false);

	// 맵 설정
	MAP_MANAGER->SetCurMap(_curMap);

	// 플레이어 추가
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

	// 카메라 설정
	CAMERA->SetTarget(_player->GetObjectTexture()->GetTransform());
	CAMERA->SetLeftBottom(MAP_MANAGER->GetCurMap()->GetLeftBottom());
	CAMERA->SetRightTop(MAP_MANAGER->GetCurMap()->GetRightTop());
	CAMERA->Update();

	// 마우스 커서 설정
	MOUSE_CURSUR->CursurOff();
}
