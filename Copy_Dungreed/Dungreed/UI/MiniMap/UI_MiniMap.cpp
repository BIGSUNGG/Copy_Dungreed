#include "framework.h"
#include "UI_MiniMap.h"

UI_MiniMap::UI_MiniMap()
	: UI()
{
	_uiType = UI::MINIMAP;


	_miniMapRtv = make_shared<RenderTarget>(WIN_WIDTH,WIN_HEIGHT);
	float color[4] = { 1,1,1,0 };
	_miniMapRtv->Color(color);

	_miniTileRtv = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);

	_miniPlayer = make_shared<Object>();
	auto quad = make_shared<Quad>(L"Resource/Ui/MiniMap/MiniPlayer.png");
	_miniPlayer->SetTexture(quad);
}	


void UI_MiniMap::Update()
{
	_miniMapBase->Update();

	{
		Vector2 pos = (GAME->GetPlayer()->GetPos() - MAP_MANAGER->GetCurMap()->GetLeftBottom()) * _miniMapSizeRatio;
		pos.x += _miniMapBase->Left();
		pos.y += _miniMapBase->Bottom() + 5.0f;
		_miniPlayer->SetPos(pos);
	}
	_miniPlayer->Update();

	_miniTile->Update();
	
	{
		auto& creature = MAP_MANAGER->GetCurMap()->GetObjects()[Object::CREATURE];
		for (int i = 0; i < _miniEnemy.size(); i++)
		{
			if (creature[i] == GAME->GetPlayer() || creature[i] == nullptr || creature[i]->GetRender() == false)
			{
				_miniEnemy[i]->GetRender() = false;
				continue;
			}
			_miniEnemy[i]->GetRender() = true;
			Vector2 pos = (creature[i]->GetPos() - MAP_MANAGER->GetCurMap()->GetLeftBottom()) * _miniMapSizeRatio;
			pos.x += _miniMapBase->Left();
			pos.y += _miniMapBase->Bottom() + 5.0f;
			_miniEnemy[i]->SetPos(pos);
		}
	}

	for (auto& enemy : _miniEnemy)
		enemy->Update();
}

void UI_MiniMap::PreRender()
{
	_miniMapRtv->Set();
	_miniTileRtv->Set();
}

void UI_MiniMap::Render()
{
	if (_miniMapBase != nullptr)
		_miniMapBase->Render();

	if (_miniTile != nullptr)
		_miniTile->Render();

	for (auto enemy : _miniEnemy)
		enemy->Render();

	if (_miniPlayer != nullptr)
		_miniPlayer->Render();
}

void UI_MiniMap::Refresh()
{
	Vector2 rightTop = MAP_MANAGER->GetCurMap()->GetRightTop();
	Vector2 leftBottom = MAP_MANAGER->GetCurMap()->GetLeftBottom();


	Vector2 size = (rightTop - leftBottom) * _miniMapSizeRatio;

	{
		_miniMapBase = make_shared<Quad>(L"MiniMap_Base", size);
		shared_ptr<Texture> texture = Texture::Add(L"MiniMap_Base_Texture", _miniMapRtv->GetSRV());
		_miniMapBase->SetTexture(texture);
		_miniMapBase->SetTop(WIN_HEIGHT - 40);
		_miniMapBase->SetRight(WIN_WIDTH - 180);
	}

	{
		auto tiles = MAP_MANAGER->GetCurMap()->GetObjects()[Object::TILE];
		auto quad = make_shared<Quad>(L"MiniMap_Tile", _miniTileSize);

		shared_ptr<Texture> texture = Texture::Add(L"MiniMap_Tile_Texture", _miniTileRtv->GetSRV());
		quad->SetTexture(texture);
		_miniTile = make_shared<InstanceQuad>(quad, tiles.size());
		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i] == nullptr || tiles[i]->GetStatic() == false)
			{
				_miniTile->GetTransforms()[i] = nullptr;
				continue;
			}

			Vector2 pos = (tiles[i]->GetPos() - leftBottom) * _miniMapSizeRatio;
			pos.x += _miniMapBase->Left();
			pos.y += _miniMapBase->Bottom();

			_miniTile->GetTransforms()[i]->GetPos() = pos;
		}

		_miniTile->ApplyChanges();
	}

	{
		auto creature = MAP_MANAGER->GetCurMap()->GetObjects()[Object::CREATURE];
		_miniEnemy.resize(creature.size());

		for (auto& enemy : _miniEnemy)
		{
			enemy = make_shared<Object>();
			enemy->GetRender() = false;
			auto quad = make_shared<Quad>(L"Resource/Ui/MiniMap/MiniEnemy.png");
			enemy->SetTexture(quad);
		}
	}
}
