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

	bool& GetRefreshSize() { return _refreshSize; }
	const bool& GetIsPlaying() { return _isPlaying; }
	const int& GetCurAnim() { return _index.first; }

	unordered_map<int, vector<wstring>> _animList;
	unordered_map<int, vector<float>>   _animSpeed;
	unordered_map<int, Anim_State>		_animState;

private:
	shared_ptr<Quad> _texture;
	float _animRunTime = 0.0f;
	int _curState = _index.second;
	bool _isPlaying = true;
	bool _refreshSize = false;
	pair<int, int> _index = { 0,0 };
};
