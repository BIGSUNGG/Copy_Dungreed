#include "framework.h"
#include "UIManager.h"

UIManager* UIManager::_instance = nullptr;

void UIManager::Update()
{
	switch (_state)
	{
	case UIManager::UI_State::NOMAL:
		_enemyHpBar->Update();
		_playerHpBar->Update();
		_weaponSlot->Update();
		_info->Update();
		_miniMap->Update();
		break;
	case UIManager::UI_State::INVEN:
		_playerHpBar->Update();
		_info->Update();
		_inventory->Update();
		break;
	case UI_State::MAP:
		_enemyHpBar->Update();
		_playerHpBar->Update();
		_weaponSlot->Update();
		_info->Update();
		_miniMap->Update();
		_map->Update();
		break;
	case UI_State::OPTION:
		_select->Update();
		break;
	case UI_State::SETTING:
		_setting->Update();
		break;
	default:
		break;
	}

	_filterQuad->Update();
}

void UIManager::PreRender()
{
	_filter->Set();
	for (auto& ui : _ui)
		ui->PreRender();
}

void UIManager::PostRender()
{
	Camera::GetInstance()->SetUiCameraBuffer();

	_filterQuad->Render();

	switch (_state)
	{
	case UIManager::UI_State::NOMAL:
		_enemyHpBar->Render();
		_playerHpBar->Render();
		_weaponSlot->Render();
		_info->Render();
		_miniMap->Render();
		break;
	case UIManager::UI_State::INVEN:
		_playerHpBar->Render();
		_info->Render();
		_inventory->Render();
		break;
	case UI_State::MAP:
		_weaponSlot->Render();
		_info->Render();
		_map->Render();
		break;
	case UI_State::OPTION:
		_select->Render();
		break;
	case UI_State::SETTING:
		_setting->Render();
		break;
	default:
		break;
	}
}

void UIManager::Refresh()
{
	for (auto& ui : _ui)
		ui->Refresh();
}

void UIManager::SetState(const UI_State& state)
{
	_state = state;

	switch (_state)
	{
	case UIManager::UI_State::NOMAL:
		MOUSE_CURSUR->SetCursurImage(OBJ_MANAGER->GetCursurImage(2));
		break;
	case UIManager::UI_State::INVEN:
		MOUSE_CURSUR->SetCursurImage(OBJ_MANAGER->GetCursurImage(0));
		break;
	case UI_State::MAP:
		MOUSE_CURSUR->SetCursurImage(OBJ_MANAGER->GetCursurImage(0));
		break;
	case UI_State::OPTION:
		MOUSE_CURSUR->SetCursurImage(OBJ_MANAGER->GetCursurImage(0));
		break;
	case UI_State::SETTING:
		MOUSE_CURSUR->SetCursurImage(OBJ_MANAGER->GetCursurImage(0));
		break;
	default:
		break;
	}
}

UIManager::UIManager()
{
	_filter = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
	float color[4] = { 0,0,0,0.15f };
	_filter->Color(color);

	_filterQuad = make_shared<Quad>(L"UI_Filter", Vector2(WIN_WIDTH, WIN_HEIGHT));
	shared_ptr<Texture> texture = Texture::Add(L"UI_Filter_Texture", _filter->GetSRV());
	_filterQuad->SetTexture(texture);
	_filterQuad->GetTransform()->GetPos() = CENTER;

	_playerHpBar = make_shared<UI_PlayerHpBar>();
	_enemyHpBar = make_shared<UI_EnemyHpBar>();
	_weaponSlot = make_shared<UI_WeaponSlot>();
	_info = make_shared<UI_Info>();
	_miniMap = make_shared<UI_MiniMap>();
	_inventory = make_shared<UI_Inventory>();
	_map = make_shared<UI_Map>();
	_select = make_shared<UI_Option>();
	_setting = make_shared<UI_Setting>();

	_ui.emplace_back(_playerHpBar);
	_ui.emplace_back(_enemyHpBar);
	_ui.emplace_back(_weaponSlot);
	_ui.emplace_back(_info);
	_ui.emplace_back(_miniMap);
	_ui.emplace_back(_inventory);
	_ui.emplace_back(_map);
	_ui.emplace_back(_select);
	_ui.emplace_back(_setting);

}

UIManager::~UIManager()
{
}
