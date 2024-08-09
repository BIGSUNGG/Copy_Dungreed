#include "framework.h"
#include "UI_Map.h"

UI_Map::UI_Map()
{
	_filter = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
	float color[4] = { 0,0,0,0.5f };
	_filter->SetColor(color);

	_filterQuad = make_shared<Quad>(L"UI_Map_Filter", Vector2(WIN_WIDTH, WIN_HEIGHT));
	shared_ptr<Texture> texture = Texture::Add(L"UI_Map_Texture", _filter->GetSRV());
	_filterQuad->SetImage(texture);
	_filterQuad->GetTransform()->GetPos() = CENTER;

	_mapBase = make_shared<Quad>(L"Resource/Ui/Map/Map_Base.png");
	_mapBase->SetBottom(0);
	_mapBase->GetTransform()->GetPos().x = CENTER.x;

	_mapBlock = make_shared<InstanceQuad>(L"Resource/Ui/Map/Map_Block.png", 0);
	_verticalLine = make_shared<InstanceQuad>(L"Resource/Ui/Map/Map_Bar_Vertical.png", 0);
	_horizonLine = make_shared<InstanceQuad>(L"Resource/Ui/Map/Map_Bar_Horizon.png", 0);

	_blinkBlock = make_shared<Quad>(L"Resource/Ui/Map/Blink_Block.png");
	_blinkBlock->GetTransform()->GetPos() = Vector2(960.f, 457.f);
	_blinkBlock->Update();

	{
		_exitButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Button/Exit.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Button/Exit_Hover.png");
		quad->SetRight(WIN_WIDTH - 36);
		quad->SetTop(WIN_HEIGHT - 45);
		_exitButton->SetTexture(quad);
		_exitButton->SetHoverTexture(hoverQuad);
		function<void()> func = []() { UI_MANAGER->SetState(UIManager::UI_State::NOMAL); };
		_exitButton->SetKeyUpEvent(func);
	}

}

void UI_Map::PreRender()
{
	_filter->Set();
}

void UI_Map::Update()
{
	// _blinkBlock 깜박이기
	_blinkRunTime += DELTA_TIME;
	if (_blinkRunTime >= _blinkDelay)
	{
		_blinkRunTime = 0.0f;
		SWITCH_BOOL(_blink);
	}

	_filterQuad->Update();
	_mapBase->Update();

	_mapBlock->Update();
	_verticalLine->Update();
	_horizonLine->Update();
	_exitButton->Update();
}

void UI_Map::Render()
{
	_filterQuad->Render();

	if(_blink)
		_blinkBlock->Render();

	_mapBlock->Render();
	_verticalLine->Render();
	_horizonLine->Render();
	_mapBase->Render();
	_exitButton->Render();
}

void UI_Map::Refresh()
{
	// 방문한 맵 등록
	_visited[MAP_MANAGER->GetCurMap()] = true;

	// 맵 초기화
	_mapBlock->GetTransforms().clear();
	_verticalLine->GetTransforms().clear();
	_horizonLine->GetTransforms().clear();

	for (auto& maps : MAP_MANAGER->GetMaps())
	{
		for (auto& map : maps.second)
		{
			if(map.second == nullptr)
				continue;

			// 방문한 맵이라면 지도맵에 표시
			if (_showAllMap || _visited[map.second] == true)
			{
				// 맵 위치 설정
				Vector2 distance = MAP_MANAGER->GetMapPos() - Vector2(maps.first, map.first);
				Vector2 blockPos = Vector2(960.f - (distance.x * 156.f), 457.f - (distance.y * 156.f));

				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos;
					_mapBlock->GetTransforms().emplace_back(transform);
				}

				// 다른 맵과 연결 여부 설정
				if (map.second->CanGoRight())
				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos + Vector2(72, 0);
					_horizonLine->GetTransforms().emplace_back(transform);
				}
				if (map.second->CanGoLeft())
				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos - Vector2(72, 0);
					_horizonLine->GetTransforms().emplace_back(transform);
				}
				if (map.second->CanGoTop())
				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos + Vector2(0, 72);
					_verticalLine->GetTransforms().emplace_back(transform);
				}
				if (map.second->CanGoBottom())
				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos - Vector2(0, 72);
					_verticalLine->GetTransforms().emplace_back(transform);
				}
			}
		}
	}

	_mapBlock->ApplyChanges();
	_verticalLine->ApplyChanges();
	_horizonLine->ApplyChanges();
}