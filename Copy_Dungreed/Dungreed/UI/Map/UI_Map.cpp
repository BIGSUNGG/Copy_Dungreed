#include "framework.h"
#include "UI_Map.h"

UI_Map::UI_Map()
{
	_filter = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
	float color[4] = { 0,0,0,0.5f };
	_filter->Color(color);

	_filterQuad = make_shared<Quad>(L"UI_Map_Filter", Vector2(WIN_WIDTH, WIN_HEIGHT));
	shared_ptr<Texture> texture = Texture::Add(L"UI_Map_Texture", _filter->GetSRV());
	_filterQuad->SetTexture(texture);
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
	_blinkRunTime += DELTA_TIME;
	if (_blinkRunTime >= _blinkDelay)
	{
		_blinkRunTime = 0.0f;
		SwitchBool(_blink);
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
	_mapBase->Render();
	_verticalLine->Render();
	_horizonLine->Render();
	_exitButton->Render();
}

void UI_Map::Refresh()
{
	_mapBlock->GetTransforms().clear();
	_verticalLine->GetTransforms().clear();
	_horizonLine->GetTransforms().clear();

	for (auto& maps : MAP_MANAGER->GetMaps())
	{
		for (auto& map : maps.second)
		{
			if (map.second.second)
			{
				Vector2 distance = MAP_MANAGER->GetMapIndex() - Vector2(maps.first, map.first);
				Vector2 blockPos = Vector2(960.f - (distance.x * 156.f), 457.f - (distance.y * 156.f));

				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos;
					_mapBlock->GetTransforms().emplace_back(transform);
				}

				if (map.second.first->CanGoRight())
				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos + Vector2(72, 0);
					_horizonLine->GetTransforms().emplace_back(transform);
				}
				if (map.second.first->CanGoLeft())
				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos - Vector2(72, 0);
					_horizonLine->GetTransforms().emplace_back(transform);
				}
				if (map.second.first->CanGoTop())
				{
					shared_ptr<Transform> transform = make_shared<Transform>();
					transform->GetPos() = blockPos + Vector2(0, 72);
					_verticalLine->GetTransforms().emplace_back(transform);
				}
				if (map.second.first->CanGoBottom())
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