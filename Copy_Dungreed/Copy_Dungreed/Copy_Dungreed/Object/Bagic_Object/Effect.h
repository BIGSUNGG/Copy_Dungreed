#pragma once
class Effect
{
public:
	Effect(wstring file, Vector2 maxFrame, float speed = 0.1f, Action::Type type = Action::Type::END);
	~Effect();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring file, Vector2 maxFrame, float speed = 0.1f, Action::Type type = Action::Type::END);

	void Play(Vector2 pos) 
	{
		_sprite->GetTransform()->GetPos() = pos;
		_action->Play();
		_isActive = true; 
	}
	void End();

	bool _isActive = false;

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};

