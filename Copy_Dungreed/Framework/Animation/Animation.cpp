#include "framework.h"
#include "Animation.h"


void Animation::Update()
{
	if (_curState != _index.first)
	{
		_index.first = _curState;
		_index.second = 0;
		_texture->SetTexture(_animList[_index.first][_index.second]);
		_isPlaying = true;
	}

	if (_isPlaying == true)
	{
		_animRunTime += DELTA_TIME;
		if (_animRunTime >= _animSpeed[_index.first][_index.second] && _isPlaying == true)
		{
			_animRunTime = 0;
			_index.second++;
			if (_index.second < _animList[_index.first].size())
			{
				if (_beforeChange != nullptr)
					_beforeChange(_texture);
				_texture->SetTexture(_animList[_index.first][_index.second]);
				if (_refreshSize)
					_texture->Refresh();
				if (_afterChange != nullptr)
					_afterChange(_texture);
			}
			else
			{
				switch (_animState[_index.first])
				{
				case Animation::Anim_State::END:
					_isPlaying = false;
					break;
				case Animation::Anim_State::LOOP:
					_index.second = 0;
					if(_beforeChange != nullptr)
						_beforeChange(_texture);
					_texture->SetTexture(_animList[_index.first][_index.second]);
					if (_afterChange != nullptr)
						_afterChange(_texture);
					break;
				case Animation::Anim_State::PINGPONG:
					_index.second = 1;
					reverse(_animList[_index.first].begin(), _animList[_index.first].end());
					if (_beforeChange != nullptr)
						_beforeChange(_texture);
					_texture->SetTexture(_animList[_index.first][_index.second]);
					if (_afterChange != nullptr)
						_afterChange(_texture);
					break;
				}
			}
		}
	}
}

void Animation::ChangeAnimation(int state , bool force)
{
	if (force)
		_index.first = state;

	if(_animList[state].size() > 0)
		_curState = state;

}