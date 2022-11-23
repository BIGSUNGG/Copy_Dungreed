#include "framework.h"
#include "UIManager.h"

UIManager* UIManager::_instance = nullptr;

void UIManager::Update()
{
	if (_blinkState != Blink_State::END)
	{
		switch (_blinkState)
		{
		case UIManager::DARK:
			_blinkColor.w += DELTA_TIME * _blinkSpeed;
			if (_blinkColor.w > 1)
			{
				_blinkColor.w = 1;
				_blinkState = Blink_State::STOP;
				if(_blinkEvent != nullptr)
					_blinkEvent();
			}
			break;
		case UIManager::STOP:
			_blinkStop -= DELTA_TIME;
			if (_blinkStop <= 0)
				_blinkState = BRIGHT;
			break;
		case UIManager::BRIGHT:
			_blinkColor.w -= DELTA_TIME * _blinkSpeed;
			if (_blinkColor.w < 0)
			{
				_blinkColor.w = 0;
				_blinkState = Blink_State::END;
			}
			break;
		default:
			break;
		}

		float color[4] = { _blinkColor.x,_blinkColor.y,_blinkColor.z,_blinkColor.w };
		_blinkRtv->SetColor(color);
	}

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

	_postProssessingQuad->Update();
	_blinkQuad->Update();
}

void UIManager::PreRender()
{
	_postProssessing->Set();
	_blinkRtv->Set();
	for (auto& ui : _ui)
		ui->PreRender();
}

void UIManager::PostRender()
{
	Camera::GetInstance()->SetUiCameraBuffer();

	_postProssessingQuad->Render();

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

	if (_blinkState != Blink_State::END)
		_blinkQuad->Render();
}

void UIManager::Refresh()
{
	for (auto& ui : _ui)
		ui->Refresh();
}

void UIManager::SetState(const UI_State& state)
{
	switch (_state)
	{
	case UIManager::UI_State::NOMAL:
		break;
	case UIManager::UI_State::INVEN:
		break;
	case UI_State::MAP:
		break;
	case UI_State::OPTION:
		GAME->GetPause() = false;
		break;
	case UI_State::SETTING:
		GAME->GetPause() = false;
		break;
	default:
		break;
	}

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
		GAME->GetPause() = true;
		break;
	case UI_State::SETTING:
		MOUSE_CURSUR->SetCursurImage(OBJ_MANAGER->GetCursurImage(0));
		GAME->GetPause() = true;
		break;
	default:
		break;
	}
}

void UIManager::SetPostProssesing(XMFLOAT4 color)
{
	float colors[4] = { color.x,color.y,color.z,color.w };
	_postProssessing->SetColor(colors);
}

bool UIManager::Blink(const float& speed, const float& stopTime, const XMFLOAT4& color, function<void()> func)
{
	if (_blinkState != Blink_State::END)
		return false;

	_blinkSpeed = speed;
	_blinkStop = stopTime;
	_blinkColor = color;
	_blinkEvent = func;
	_blinkState = Blink_State::DARK;
	return true;
}

UIManager::UIManager()
{
	_postProssessing = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
	float color[4] = { 0,0,0,0 };
	_postProssessing->SetColor(color);

	_postProssessingQuad = make_shared<Quad>(L"UI_Filter", Vector2(WIN_WIDTH, WIN_HEIGHT));
	shared_ptr<Texture> texture = Texture::Add(L"UI_Filter_Texture", _postProssessing->GetSRV());
	_postProssessingQuad->SetImage(texture);
	_postProssessingQuad->GetTransform()->GetPos() = CENTER;

	_blinkRtv = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);

	_blinkQuad = make_shared<Quad>(L"UI_Blink", Vector2(WIN_WIDTH, WIN_HEIGHT));
	texture = Texture::Add(L"UI_Blink_Texture", _blinkRtv->GetSRV());
	_blinkQuad->SetImage(texture);
	_blinkQuad->GetTransform()->GetPos() = CENTER;

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
