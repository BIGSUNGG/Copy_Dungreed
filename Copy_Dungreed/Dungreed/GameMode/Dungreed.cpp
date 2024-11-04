#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	_modeType = DUNGREED;

	Init();
}

void Dungreed::Update()
{
	_gameRunTime += DELTA_TIME;

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
	if (ImGui::CollapsingHeader("Dungreed"))
	{
		ImGui::Text("Run Time : %f", _gameRunTime);
	}

	if (ImGui::CollapsingHeader("Player"))
	{
		if(ImGui::Button("MELEE"))
			_player->GainItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));

		ImGui::SameLine();

		if(ImGui::Button("GUN"))
			_player->GainItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));

		ImGui::Text("Pos : %0.1f , %0.1f", _player->GetObjectTexture()->GetTransform()->GetPos().x, _player->GetObjectTexture()->GetTransform()->GetPos().y);
		ImGui::Text("Velocity : %0.1f , %0.1f", _player->GetMovementComponent()->GetVelocity().x, _player->GetMovementComponent()->GetVelocity().y);
	}

	GAME->ImguiRender();
}

void Dungreed::Init()
{
	// 게임 초기화
	GAME->Reset();
	CAMERA->SetFreeMode(false);

	// 플레이어 추가
	_player = dynamic_pointer_cast<Player>(MAKE_PLAYER(2));
	_player->SetSpawnPos(_player->GetObjectTexture()->GetTransform()->GetPos());
	_player->GainItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 2));
	_player->GainItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 1));
	_player->GainItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));
	_player->GainItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));
	_player->AddOnDeathEvent(bind(&Dungreed::Init, this));

	GAME->SetPlayer(_player);
	GAME->SetPlaying(true);
	GAME->SetEnableUI(true);

	// 맵 생성
	MAP_MANAGER->MakeRandomMap(1, 0);

	// 카메라 설정
	CAMERA->Update();

	// 마우스 커서 설정
	MOUSE_CURSUR->CursurOff();
}
