#include "framework.h"
#include "UI_MiniMap.h"

UI_MiniMap::UI_MiniMap()
{
	_uiType = UI::MINIMAP;

	_rtv = make_shared<RenderTarget>(WIN_WIDTH,WIN_HEIGHT);
	float color[4] = { 1,1,1,0.1 };
	_rtv->SetColor(color);
}	


void UI_MiniMap::Update()
{
	if (_rtvQuad != nullptr)
		_rtvQuad->Update();
}

void UI_MiniMap::PreRender()
{
	_rtv->Set();
}

void UI_MiniMap::Render()
{
	if (_rtvQuad != nullptr)
		_rtvQuad->Render();

	if (_miniTile != nullptr)
		_miniTile->Render();

	if (_miniEnemy != nullptr)
		_miniEnemy->Render();

	if (_miniPlayer != nullptr)
		_miniPlayer->Render();
}

void UI_MiniMap::Refresh()
{
	Vector2 rightTop = MAP_MANAGER->GetCurMap()->GetRightTop();
	Vector2 leftBottom = MAP_MANAGER->GetCurMap()->GetLeftBottom();

	auto tiles = MAP_MANAGER->GetCurMap()->GetObjects()[Object::TILE];

	Vector2 size = (rightTop - leftBottom) / 10;

	_rtvQuad = make_shared<Quad>(L"MiniMap_Base", size);
	shared_ptr<Texture> texture = Texture::Add(L"MiniMap_Base_Texture", _rtv->GetSRV());
	_rtvQuad->SetTexture(texture);
	_rtvQuad->SetTop(WIN_HEIGHT - 25);
	_rtvQuad->SetRight(WIN_WIDTH - 25);
}
