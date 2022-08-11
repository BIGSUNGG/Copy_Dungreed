#pragma once

class Quad;

class Animation
{
public:
	enum Anim_State
	{
		END,
		LOOP,
		PINGPONG,
	};

public:
	void Update();

	void ChangeAnimation(int state);
	void SetTexture(shared_ptr<Quad> texture) { _texture = texture; }

	vector<vector<wstring>> _animList = vector<vector<wstring>>(6, vector<wstring>());
	vector<vector<float>>   _animSpeed = vector<vector<float>>(6, vector<float>(10, 0.15f));
	vector<Anim_State> _animState = vector<Anim_State>(6, LOOP);

private:
	shared_ptr<Quad> _texture;
	float _animRunTime = 0.0f;
	int _curState = _index.second;
	bool _isPlaying = true;
	pair<int, int> _index = { 0,0 };
};
