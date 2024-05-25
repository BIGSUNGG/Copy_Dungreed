#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	GAME->Reset();
	_modeType = DUNGREED;

	CAMERA->SetFreeMode(false);

	Init();

	MOUSE_CURSUR->CursurOff();
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
			_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));

		ImGui::SameLine();

		if(ImGui::Button("GUN"))
			_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));

		ImGui::Text("Pos : %0.1f , %0.1f", _player->GetObjectTexture()->GetTransform()->GetPos().x, _player->GetObjectTexture()->GetTransform()->GetPos().y);
		ImGui::Text("Velocity : %0.1f , %0.1f", _player->GetMovementComponent()->GetVelocity().x, _player->GetMovementComponent()->GetVelocity().y);
	}

	GAME->ImguiRender();
}

void Dungreed::Init()
{
	_player = dynamic_pointer_cast<Player>(MAKE_PLAYER(2));
	_player->SetSpawnPos(_player->GetObjectTexture()->GetTransform()->GetPos());
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 2));
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 1));
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));
	_player->AddItem(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));
	_player->AddOnDeathEvent(bind(&Dungreed::Init, this));

	GAME->AddPlayer(_player);
	GAME->SetPlaying(true);
	GAME->SetEnableUI(true);

	MAP_MANAGER->MakeRandomMap(1, 0);
	CAMERA->Update();
}
