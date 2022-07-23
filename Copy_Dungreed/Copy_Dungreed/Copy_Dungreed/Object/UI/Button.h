#pragma once
class Button
{
public:
	enum State
	{
		NONE,
		HOVER,
		CLICK
	};

	Button();
	~Button();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos);
	void SetScale(Vector2 scale);
	void SetText(string text);

	void SetEvent(CallBack callBack) { _callBack = callBack; }
	void SetEventParam(CallBackParam callBack)
	{
		_callBackInt = callBack;
	}

private:
	State _state;

	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _collider;
	string _text;

	Vector2 _buttonPos;
	shared_ptr<ButtonBuffer> _buttonBuffer;

	CallBack _callBack;
	CallBackParam _callBackInt;
};