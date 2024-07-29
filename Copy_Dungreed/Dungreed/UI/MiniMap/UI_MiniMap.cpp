#include "framework.h"
#include "UI_MiniMap.h"

UI_MiniMap::UI_MiniMap()
	: UI()
{
	{
		_mapRtv = make_shared<RenderTarget>(WIN_WIDTH,WIN_HEIGHT);
		float color[4] = { 1,1,1,1 };
		_mapRtv->SetColor(color);
	}

	{
		_tileRtv = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
		float color[4] = { 1,1,1,1 };
		_tileRtv->SetColor(color);
	}

	{
		_doorRtv = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
		float color[4] = { 0,1,0,1 };
		_doorRtv->SetColor(color);
	}

	_player = make_shared<Object>();
	auto quad = make_shared<Quad>(L"Resource/Ui/MiniMap/MiniPlayer.png");
	_player->SetTexture(quad);
}	


void UI_MiniMap::Update()
{
	// Player
	{
		Vector2 pos = (GAME->GetPlayer()->GetPos() - MAP_MANAGER->GetCurMap()->GetLeftBottom()) * _mapSizeRatio;
		pos.x += _mapBase->Left();
		pos.y += _mapBase->Bottom() + 5.0f;
		_player->SetPos(pos);
	}

	// Enemy
	{
		auto& creature = MAP_MANAGER->GetCurMap()->GetObjects()[Object::CREATURE];
		for (int i = 0; i < _enemy.size(); i++)
		{
			if (creature[i] == GAME->GetPlayer() || creature[i] == nullptr || creature[i]->IsRender() == false)
			{
				_enemy[i]->SetIsRender(false);
				continue;
			}
			_enemy[i]->SetIsRender(true);
			Vector2 pos = (creature[i]->GetPos() - MAP_MANAGER->GetCurMap()->GetLeftBottom()) * _mapSizeRatio;
			pos.x += _mapBase->Left();
			pos.y += _mapBase->Bottom() + 5.0f;
			_enemy[i]->SetPos(pos);
		}

	}

	_mapBase->Update();
	_tile->Update();
	_door->Update();
	_player->Update();

	for (auto& enemy : _enemy)
		enemy->Update();
}

void UI_MiniMap::PreRender()
{
	_mapRtv->Set();
	_tileRtv->Set();
	_doorRtv->Set();
}

void UI_MiniMap::Render()
{
	if (_mapBase != nullptr)
		_mapBase->Render();

	if (_door != nullptr)
		_door->Render();

	if (_tile != nullptr)
		_tile->Render();

	for (auto enemy : _enemy)
		enemy->Render();

	if (_player != nullptr)
		_player->Render();
}

void UI_MiniMap::Refresh()
{
	Vector2 rightTop = MAP_MANAGER->GetCurMap()->GetRightTop();
	Vector2 leftBottom = MAP_MANAGER->GetCurMap()->GetLeftBottom();


	Vector2 size = (rightTop - leftBottom) * _mapSizeRatio;

	// Map Base
	{
		_mapBase = make_shared<Quad>(L"MiniMap_Base", size);
		shared_ptr<Texture> texture = Texture::Add(L"MiniMap_Base_Texture", _mapRtv->GetSRV());
		_mapBase->SetImage(texture);
		_mapBase->SetTop(WIN_HEIGHT - 40);
		_mapBase->SetRight(WIN_WIDTH - 180);
	}

	// Tile
	{
		auto tiles = MAP_MANAGER->GetCurMap()->GetObjects()[Object::TILE];
		auto quad = make_shared<Quad>(L"MiniMap_Tile", _tileSize);

		shared_ptr<Texture> texture = Texture::Add(L"MiniMap_Tile_Texture", _tileRtv->GetSRV());
		quad->SetImage(texture);
		_tile = make_shared<InstanceQuad>(quad, tiles.size()); 
		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i] == nullptr || tiles[i]->IsStatic() == false)
			{
				_tile->GetTransforms()[i] = nullptr;
				continue;
			}

			Vector2 pos = (tiles[i]->GetPos() - leftBottom) * _mapSizeRatio;
			pos.x += _mapBase->Left();
			pos.y += _mapBase->Bottom();

			_tile->GetTransforms()[i]->GetPos() = pos;
		}

		_tile->ApplyChanges();
	}

	// Door
	{
		auto quad = make_shared<Quad>(L"MiniMap_Door", _doorSize);

		vector<Vector2> doorPos;
		doorPos.reserve(20);
		if (MAP_MANAGER->GetCurMap()->CanGoTop())
		{
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetTopDoor());
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetTopDoor() + Vector2(70, 0));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetTopDoor() - Vector2(70, 0));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetTopDoor() + Vector2(140, 0));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetTopDoor() - Vector2(140, 0));
		}
		if (MAP_MANAGER->GetCurMap()->CanGoBottom())
		{
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetBottomDoor());
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetBottomDoor() + Vector2(70, 0));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetBottomDoor() - Vector2(70, 0));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetBottomDoor() + Vector2(140, 0));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetBottomDoor() - Vector2(140, 0));
		}
		if (MAP_MANAGER->GetCurMap()->CanGoLeft())
		{
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetLeftDoor());
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetLeftDoor() + Vector2(0, 70));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetLeftDoor() - Vector2(0, 70));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetLeftDoor() + Vector2(0, 140));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetLeftDoor() - Vector2(0, 140));
		}
		if (MAP_MANAGER->GetCurMap()->CanGoRight())
		{
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetRightDoor());
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetRightDoor() + Vector2(0, 70));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetRightDoor() - Vector2(0, 70));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetRightDoor() + Vector2(0, 140));
			doorPos.push_back(MAP_MANAGER->GetCurMap()->GetRightDoor() - Vector2(0, 140));
		}

		shared_ptr<Texture> texture = Texture::Add(L"MiniMap_Door_Texture", _doorRtv->GetSRV());
		quad->SetImage(texture);
		_door = make_shared<InstanceQuad>(quad, doorPos.size());
		for (int i = 0; i < doorPos.size(); i++)
		{
			Vector2 pos = (doorPos[i] - leftBottom) * _mapSizeRatio;
			pos.x += _mapBase->Left();
			pos.y += _mapBase->Bottom();

			_door->GetTransforms()[i]->GetPos() = pos;
		}

		_door->ApplyChanges();
	}

	// Enemy
	{
		auto creature = MAP_MANAGER->GetCurMap()->GetObjects()[Object::CREATURE];
		_enemy.resize(creature.size());

		for (auto& enemy : _enemy)
		{
			enemy = make_shared<Object>();
			enemy->SetIsRender(false);
			auto quad = make_shared<Quad>(L"Resource/Ui/MiniMap/MiniEnemy.png");
			enemy->SetTexture(quad);
		}
	}
}
