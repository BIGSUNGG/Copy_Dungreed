#include "framework.h"
#include "MouseCursur.h"

MouseCursur* MouseCursur::_instance = nullptr;

void MouseCursur::Update()
{
	_mouseCursur->GetTransform()->GetPos() = MOUSE_POS;	
	_mouseCursur->Update();
}

void MouseCursur::Render()
{
	Camera::GetInstance()->SetUiCameraBuffer();

	if (!_showMouseCursur)
		_mouseCursur->Render();
}

void MouseCursur::CursurOn()
{
	int temp = ShowCursor(true);

	if (temp < 0)
	{
		for (int i = 0; i < -temp; i++)
		{
			ShowCursor(true);
		}
	}

	_showMouseCursur = true;
}

void MouseCursur::CursurOff()
{
	int temp = ShowCursor(false);

	if (temp > -1)
	{
		for (int i = 0; i < temp + 1; i++)
		{
			ShowCursor(false);
		}
	}

	_showMouseCursur = false;
}

MouseCursur::MouseCursur()
{
	_mouseCursur = make_shared<Quad>(L"Resource/Cursur/ShootingCursor2.png");
}

MouseCursur::~MouseCursur()
{
}
