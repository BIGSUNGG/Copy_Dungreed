#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	_modeType = DUNGREED;

	CAMERA->GetFreeMode() = false;

	_map = MAP_MANAGER->Load(0, 0);
	GAME->SetMap(_map);

	_player = dynamic_pointer_cast<Player>(MAKE_PLAYER(0));
	_player->GetTexture()->GetTransform()->GetPos().x = _map->GetStartPos().x;
	_player->GetTexture()->SetBottom(_map->GetStartPos().y);
	_player->GetBeforeMove() = _player->GetTexture()->GetTransform()->GetPos();
	_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));
	_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));

	GAME->AddPlayer(_player);
	GAME->Update();
	GAME->GetObjectUpdate() = true;

	CAMERA->SetTarget(_player->GetTexture()-> GetTransform());
	CAMERA->SetLeftBottom(_map->GetLeftBottom());
	CAMERA->SetRightTop(_map->GetRightTop());
	CAMERA->Update();

	_cursur = OBJ_MANAGER->GetCursur(2);
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
	GAME->PostRender();

	_cursur->Render();
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
			_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::MELEE, 0));

		ImGui::SameLine();

		if(ImGui::Button("GUN"))
			_player->AddWeapon(MAKE_PLAYER_WEAPON(Weapon::Weapon_Type::GUN, 0));

		ImGui::Text("Pos : %0.1f , %0.1f", _player->GetTexture()->GetTransform()->GetPos().x, _player->GetTexture()->GetTransform()->GetPos().y);
		ImGui::Text("Velocity : %0.1f , %0.1f", _player->GetVelocity().x, _player->GetVelocity().y);
	}

	GAME->ImguiRender();
}
