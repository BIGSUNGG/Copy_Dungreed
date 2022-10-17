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

	void ChangeAnimation(int state, bool force = false);
	void SetTexture(shared_ptr<Quad> texture) { _texture = texture; }
	void SetBeforeChangeFunc(function<void(shared_ptr<Quad>)> func) { _beforeChange = func; }
	void SetAfterChangeFunc(function<void(shared_ptr<Quad>)> func) { _afterChange = func; }

	bool& GetRefreshSize() { return _refreshSize; }
	bool& GetIsPlaying() { return _isPlaying; }
	const int& GetCurAnim() { return _index.first; }

	unordered_map<int, vector<wstring>> _animList;
	unordered_map<int, vector<float>>   _animSpeed;
	unordered_map<int, Anim_State>		_animState;

private:
	function<void(shared_ptr<Quad>)> _beforeChange;
	function<void(shared_ptr<Quad>)> _afterChange;

	shared_ptr<Quad> _texture;
	pair<int, int> _index = { 0,0 };

	float _animRunTime = 0.0f;
	int _curState = _index.second;

	bool _isPlaying = true;
	bool _refreshSize = false;
};
