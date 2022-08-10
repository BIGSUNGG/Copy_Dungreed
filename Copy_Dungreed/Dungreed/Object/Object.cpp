#include "framework.h"
#include "Object.h"

Object::Object(int level, int num)
	: _level(level)
	, _num(num)
{
}


void Object::Update()
{
	if (_anim != nullptr)
		_anim->Update();

	_texture->Update();
	_collider->Update();
}

void Object::Render()
{
	_texture->Render();
}

void Object::PostRender()
{
	_collider->Render();
}

void Object::MoveObject(Vector2 pos)
{
	_texture->GetTransform()->GetPos() += pos * DELTA_TIME;
}

void Object::SetCollider()
{
	_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	_collider->SetParent(_texture->GetTransform());
}

void Object::SetAnimation()
{
	_anim = make_shared<Animation>();
}

void Object::Animation::Update()
{

	if (_isPlaying == true)
	{
		_animRunTime += DELTA_TIME;
		if (_animRunTime >= _animSpeed[_index.first][_index.second])
		{
			_animRunTime = 0;
			_index.second++;
			if (_index.second < _animList[_index.first].size())
			{
				_texture->SetTexture(_animList[_index.first][_index.second]);
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
					_texture->SetTexture(_animList[_index.first][_index.second]);
					break;
				case Animation::Anim_State::PINGPONG:
					_index.second = 1;
					reverse(_animList[_index.first].begin(), _animList[_index.first].end());
					_texture->SetTexture(_animList[_index.first][_index.second]);
					break;
				}
			}
		}
	}
}

void Object::Animation::ChangeAnimation(Object::State state)
{
	_isPlaying = true;

	if (_index.first != state)
	{
		_index.first = state;
		_index.second = 0;
		_texture->SetTexture(_animList[_index.first][_index.second]);
	}
}
