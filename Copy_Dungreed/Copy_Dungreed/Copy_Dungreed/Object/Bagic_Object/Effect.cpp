#include "framework.h"
#include "Effect.h"

Effect::Effect(wstring file, Vector2 maxFrame, float speed, Action::Type type)
{
	_sprite = make_shared<Sprite>(file, maxFrame);
	_sprite->GetTransform()->GetPos() = CENTER;
	
	CreateAction(file, maxFrame, speed, type);

	_action->SetEndEvent(std::bind(&Effect::End, this));
}

Effect::~Effect()
{
}

void Effect::CreateAction(wstring file, Vector2 maxFrame, float speed, Action::Type type)
{
	// 클립들 만들기
	vector<Action::Clip> clips;

	float w = _sprite->GetSize().x / maxFrame.x;
	float h = _sprite->GetSize().y / maxFrame.y;

	for (int y = 0; y < maxFrame.y; y++)
	{
		for (int x = 0; x < maxFrame.x; x++)
		{
			clips.emplace_back(x * w, y * h, w, h, Texture::Add(file));
		}
	}
	
	string effectName = WstrToStr(file);
	size_t t = effectName.find("Effects/");
	effectName = effectName.substr(t + 8, effectName.length());
	effectName = effectName.substr(0, effectName.length() - 4);

	_action = make_shared<Action>(clips, effectName, type, speed);
}

void Effect::End()
{
	_isActive = false;
}

void Effect::Update()
{
	if (_isActive == false)
		return;

	_sprite->Update();
	_action->Update();
	_sprite->SetActionToActionBuffer(_action->GetCurClip());
}

void Effect::Render()
{
	if (_isActive == false)
		return;

	_sprite->Render();
}

void Effect::PostRender()
{
}
